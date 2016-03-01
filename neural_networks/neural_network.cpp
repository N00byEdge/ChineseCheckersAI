#include "neural_network.h"

#include <cassert>

ostream & operator<< ( ostream & os, const neural_network & n ) {

	os << n.weights.size ( ) << "\n";

	for ( size_t i = 0; i < n.weights.size ( ); ++ i ) {

		os << "\t" << n.weights [ i ].size ( ) << "\n";

		for ( size_t j = 0; j < n.weights [ i ].size ( ); ++ j ) {

			os << "\t\t" << n.weights [ i ] [ j ].size ( ) - 1 << " ";

			for ( size_t k = 0; k < n.weights [ i ] [ j ].size ( ); ++ k )
				os << n.weights [ i ] [ j ] [ k ] << " ";

			os << "\n";

		}

	}

	return os;

}

istream & operator>> ( istream & is, neural_network & n ) {

	n.weights.clear ( );

	size_t nLayers;
	is >> nLayers;

	for ( size_t i = 0; i < nLayers; ++ i ) {

		n.weights.push_back ( { } );

		size_t nNeurons;
		is >> nNeurons;

		for ( size_t j = 0; j < nNeurons; ++ j ) {

			n.weights [ i ].push_back ( { } );

			size_t nWeights;
			is >> nWeights;

			for ( size_t k = 0; k < nWeights; ++ k ) {

				double w;
				is >> w;
				n.weights [ i ] [ j ].push_back ( w );

			}

		}

	}

	return is;

}

vector < double > neural_network::run ( vector < double > input ) {

	vector < double > output;

	for ( auto & layer: weights ) {

		output = ( lib::matrixVectorMultiplication ( layer, input ) );

		for ( size_t o = 0; o < output.size ( ); ++ o )
			output [ o ] = lib::phi ( output [ o ] );

		input = output;

	}

	return output;

}

bool neural_network::init ( string source ) {

	if ( source == "cin" ) {

		cin >> * this;
		return true;

	} else if ( source == "none" ) {

		return true;

	} else {

		ifstream inputFile;
		inputFile.open ( source );
		if ( inputFile.is_open ( ) ) {

			inputFile >> * this;

		} else return false;

		inputFile.close ( );

		return true;

	}

}

neural_network::neural_network ( string source ) {

	setThreadVectors ( );

	if ( source.size ( ) && init ( source ) ) return;

	string input;

	cout << "This neural network has not been initialized. Please enter a neural network source: ";

	while ( true ) {

		getline ( cin, input );
		if ( init ( input ) ) break;

		cout << "Invalid input; please try again: ";

	}

}

neural_network::neural_network ( istream & is ) {

	is >> * this;

}

void neural_network::clearDeltaU ( ) {

	for ( auto & i: deltaU )
		for ( auto & j: i )
			for ( auto & k: j )
				k = 0;

	for ( auto & thread: threadDeltaUStash )
		for ( auto & i: thread )
			for ( auto & j: i )
				for ( auto & k: j )
					k = 0;

}

void neural_network::setThreadVectors ( ) {

	deltaU = weights;

	backpropDeltaU.resize ( N_THREADS );
	backpropDivergenceOutdata.resize ( N_THREADS );
	backpropSigmaPrim.resize ( N_THREADS );
	backpropA.resize ( N_THREADS );
	backpropZ.resize ( N_THREADS );

	for ( size_t i = 0; i < N_THREADS; ++ i ) {

		backpropDeltaU [ i ] = deltaU;
		backpropA [ i ].resize ( weights.size ( ) );
		backpropZ [ i ].resize ( weights.size ( ) );

		for ( size_t j = 0; j < weights.size ( ); ++ j ) {

			if ( j == weights.size ( ) - 1 ) backpropDivergenceOutdata [ i ].resize ( weights [ j ].size ( ) );

			backpropA [ i ] [ j ].resize ( weights [ j ].size ( ) + 1 );
			backpropZ [ i ] [ j ].resize ( weights [ j ].size ( ) );
			backpropA [ i ] [ j ] [ backpropA [ i ] [ j ].size ( ) - 1 ] = 1;

		}

	}

	threadDeltaUStash = backpropDeltaU;
	backpropSigmaPrim = backpropA;
	backpropDelta = backpropA;

}

vector < vector < vector < double > > > * neural_network::workerFunc ( int worker, pair < vector < double >, vector < double > > * currentDataset ) {

	/* Calculate a and z */
	for ( int i = 0; i < backpropA [ worker ] [ 0 ].size ( ); ++ i )
		backpropA [ worker ] [ 0 ] [ i ] = currentDataset -> first [ i ];
	backpropA [ worker ] [ 0 ] [ backpropA [ worker ] [ 0 ].size ( ) - 1 ] = 1;

	for ( size_t i = 1; i < weights.size ( ); ++ i ) {

		backpropZ [ worker ] [ i ] = lib::matrixVectorMultiplication ( weights [ i ], backpropA [ worker ] [ i - 1 ] );

		for ( size_t j = 0; j < backpropZ [ worker ] [ i ].size ( ); ++ j )
			backpropA [ worker ] [ i ] [ j ] = lib::phi ( backpropZ [ worker ] [ i ] [ j ] );
		backpropA [ worker ] [ i ] [ backpropA [ worker ] [ i ].size ( ) - 1 ] = 1;

	}

	/* Calculate the outdata divergence, phi(z) - y = a - y */
	for ( size_t i = 0; i < currentDataset -> second.size ( ); ++ i )
		backpropDivergenceOutdata [ worker ] [ i ] = backpropA [ worker ] [ weights.size ( ) - 1 ] [ i ] - currentDataset -> second [ i ];

	/* Calculate sigmaPrim = a-(1-a) */
	for ( size_t i = 0; i < weights.size ( ); ++ i ) {

		for ( size_t j = 0; j < weights [ i ].size ( ); ++ j )
			backpropSigmaPrim [ worker ] [ i ] [ j ] = lib::phi ( backpropZ [ worker ] [ i ] [ j ] ) * ( 1 - lib::phi ( backpropZ [ worker ] [ i ] [ j ] ) );

	}

	/* Add bias to each sigmaPrim */
	//for ( size_t i = 0; i < backpropSigmaPrim [ worker ].size ( ); ++ i )
	//	backpropSigmaPrim [ worker ] [ i ].push_back ( 1 );

	/* Delta for output layer */
	backpropDelta [ worker ] [ weights.size ( ) - 1 ] = lib::vectorPairMul ( backpropDivergenceOutdata [ worker ], backpropSigmaPrim [ worker ] [ weights.size ( ) - 1 ] );

	/* Delta for all other layers */
	int currentLayer = weights.size ( ) - 2;
	for ( ; currentLayer >= 0; -- currentLayer ) {
		vector < double > part1 = lib::matrixTransposeVectorMultiplication ( weights [ currentLayer + 1 ], backpropDelta [ worker ] [ currentLayer + 1 ] );
		backpropDelta [ worker ] [ currentLayer ] = lib::vectorPairMul (
			part1,
			backpropSigmaPrim [ worker] [ currentLayer ]
		);
	}

	/* Calculate deltaU */
	for ( size_t currentLayer = 0; currentLayer < weights.size ( ); ++ currentLayer ) {

		if ( currentLayer != 0 ) lib::vectorsToMatrix ( backpropDelta [ worker ] [ currentLayer ], backpropA [ worker ] [ currentLayer - 1 ], backpropDeltaU [ worker ] [ currentLayer ] );
		else                     lib::vectorsToMatrix ( backpropDelta [ worker ] [ currentLayer ], currentDataset -> first,                   backpropDeltaU [ worker ] [ currentLayer ] );

	}

	for ( auto & layer: backpropDeltaU [ worker ]) layer *= learningSpeed;

	threadDeltaUStash [ worker ] += backpropDeltaU [ worker ];

	return & backpropDeltaU [ worker ];

}

void neural_network::learn ( vector < pair < vector < double >, vector < double > > > & datasetsArg, double maxError = 1e-7, double learningSpeed = 0.5, long long reportFrequency = 0 ) {

	if ( !datasetsArg.size ( ) ) return;

	this -> learningSpeed = - learningSpeed / ceil ( ( float ) sqrt ( datasetsArg.size ( ) ) );
	this -> nDatasets = datasetsArg.size ( );

	/* Adding a 1 to each datasetsArg input */
	for ( size_t ds = 0; ds < datasetsArg.size ( ); ++ ds )
		datasetsArg [ ds ].first.push_back ( 1 );

	double error = 0;
	long long nIterations = 0;

	size_t t = 0;
	vector < pair < vector < double >, vector < double > > * > datasetsQueue;

	setThreadVectors ( );

	goto skipbp;

	clearDeltaU ( );

	redoBP:;

	++ nIterations;

	/* Choose ceil ( sqrt ( datasetsArg.size ( ) ) ) random datasets */

	datasetsQueue.clear ( );

	for ( size_t i = 0; i < ceil ( ( float ) sqrt ( datasetsArg.size ( ) ) ); ++ i )
		datasetsQueue.push_back ( & datasetsArg [ lib::randInt ( datasetsArg.size ( ) ) ] );

	/* Reset deltaU */

	finishit:;

	t = 0;

	workerThreads.clear ( );

	while ( datasetsQueue.size ( ) && t < N_THREADS ) {

		workerThreads.push_back ( thread ( &neural_network::workerFunc, this, t, datasetsQueue.back ( ) ) );
		datasetsQueue.pop_back ( );

		++ t;

	}

	for ( size_t i = 0; i < t; ++ i ) {

		assert ( workerThreads [ i ].joinable ( ) );

		workerThreads [ i ].join ( );

	}

	if ( datasetsQueue.size ( ) ) goto finishit;

	skipbp:;

	if ( nIterations % reportFrequency != 0 ) goto redoBP;
	else printf("%lld iterations\n", nIterations);

	for ( size_t thread = 0; thread < threadDeltaUStash.size ( ); ++ thread )
		weights += threadDeltaUStash [ thread ];

	/* Calculate error */
	for ( size_t i = 0; i < datasetsArg.size ( ); ++ i ) {

		vector < double > outdata = run ( datasetsArg [ i ].first );

		for ( size_t j = 0; j < datasetsArg [ i ].second.size ( ); ++ j )
			error += ( datasetsArg [ i ].second [ j ] - outdata [ j ] ) * ( datasetsArg [ i ].second [ j ] - outdata [ j ] );

	}

	/* Error should be divided by 2 times the number of datasets that we have */
	error /= 2 * datasetsArg.size ( );

	cout << "Error: " << error << endl << flush;

	if ( error > maxError ) goto redoBP;

}

void neural_network::learnDatabase ( database & db, double maxError = 1e-7, double learningSpeed = 0.5, long long reportFrequency = 0 ) {

	vector < pair < vector < double >, vector < double > > > datasets;

	size_t ind = 0;
	for ( auto entry: db.m ) {

		datasets.push_back ( { } );

		for ( auto c: entry.first ) {

			switch ( c ) {

				case '.':
					datasets [ ind ].first.push_back ( 0 );
					break;

				case 'O':
					datasets [ ind ].first.push_back ( 0.5 );
					break;

				case 'P':
					datasets [ ind ].first.push_back ( 1 );
					break;

			}

		}

		datasets [ ind ].second = { entry.second.first };

		++ ind;

	}

	learn ( datasets, maxError, learningSpeed, reportFrequency );

}
