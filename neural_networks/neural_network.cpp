#include "neural_network.h"

#include <cassert>

ostream & operator<< ( ostream & os, const neural_network & n ) {

	os << n.weights.size ( ) << "\n";

	for ( size_t i = 0; i < n.weights.size ( ); ++ i ) {

		os << "\t" << n.weights [ i ].size ( ) << "\n";

		for ( size_t j = 0; j < n.weights [ i ].size ( ); ++ j ) {

			os << "\t\t" << n.weights [ i ] [ j ].size ( ) << " ";

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

	for ( size_t i = 0; i < weights.size ( ); ++ i ) {

        output.resize ( weights [ weights.size ( ) - 1 ].size ( ) );

		output = lib::matrixVectorMultiplication ( weights [ i ], input );

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
		backpropA [ i ].resize ( weights.size ( ) + 1 );
		backpropZ [ i ].resize ( weights.size ( ) );
		backpropA [ i ] [ 0 ].resize ( weights [ 0 ] [ 0 ].size ( ) );

		for ( size_t j = 0; j < weights.size ( ); ++ j ) {

			if ( j == weights.size ( ) - 1 ) backpropDivergenceOutdata [ i ].resize ( weights [ j ].size ( ) );

			backpropA [ i ] [ j + 1 ].resize ( weights [ j ].size ( ) + 1 );
			backpropZ [ i ] [ j ].resize ( weights [ j ].size ( ) );
			backpropA [ i ] [ j ] [ backpropA [ i ] [ j ].size ( ) - 1 ] = 1;

		}

	}

	threadDeltaUStash = backpropDeltaU;
	backpropSigmaPrim = backpropZ;
	backpropDelta = backpropZ;
	backpropPart1 = backpropA;

}

vector < vector < vector < double > > > * neural_network::workerFunc ( int worker, pair < vector < double >, vector < double > > * currentDataset ) {

	/* Calculate a and z */
	for ( int i = 0; i < currentDataset -> first.size ( ); ++ i )
		backpropA [ worker ] [ 0 ] [ i ] = currentDataset -> first [ i ];

	for ( size_t i = 0; i < weights.size ( ); ++ i ) {

		lib::matrixVectorMultiplication ( weights [ i ], backpropA [ worker ] [ i ], backpropZ [ worker ] [ i ] );

		for ( size_t j = 0; j < backpropZ [ worker ] [ i ].size ( ); ++ j )
			backpropA [ worker ] [ i + 1 ] [ j ] = lib::phi ( backpropZ [ worker ] [ i ] [ j ] );

	}

	/* Calculate the outdata divergence, a - y */
	for ( size_t i = 0; i < currentDataset -> second.size ( ); ++ i )
		backpropDivergenceOutdata [ worker ] [ i ] = backpropA [ worker ] [ weights.size ( ) ] [ i ] - currentDataset -> second [ i ];

	/* Calculate sigmaPrim = phi(z)-(1-phi(z)) */
	for ( size_t i = 0; i < weights.size ( ); ++ i ) {

		for ( size_t j = 0; j < weights [ i ].size ( ); ++ j )
			backpropSigmaPrim [ worker ] [ i ] [ j ] = lib::phi ( backpropZ [ worker ] [ i ] [ j ] ) * ( 1 - lib::phi ( backpropZ [ worker ] [ i ] [ j ] ) );

	}

	/* Delta for output layer */
	lib::vectorPairMul ( backpropDivergenceOutdata [ worker ], backpropSigmaPrim [ worker ] [ weights.size ( ) - 1 ], backpropDelta [ worker ] [ weights.size ( ) - 1 ] );

	/* Delta for all other layers */
	for ( size_t currentLayer = weights.size ( ) - 2;; -- currentLayer ) {
        if ( weights.size ( ) < 2 ) break;
		lib::matrixTransposeVectorMultiplication ( weights [ currentLayer + 1 ], backpropDelta [ worker ] [ currentLayer + 1 ], backpropPart1 [ worker ] [ currentLayer ] );
		lib::vectorPairMul ( backpropPart1 [ worker ] [ currentLayer + 1 ], backpropSigmaPrim [ worker ] [ currentLayer ], backpropDelta [ worker ] [ currentLayer ] );
		if ( currentLayer == 0 ) break;
	}

	/* Calculate deltaU */
	for ( size_t currentLayer = 0; currentLayer < weights.size ( ); ++ currentLayer ) {

		if ( currentLayer != 0 ) lib::vectorsToMatrix ( backpropDelta [ worker ] [ currentLayer ], backpropA [ worker ] [ currentLayer ], backpropDeltaU [ worker ] [ currentLayer ] );
		else                     lib::vectorsToMatrix ( backpropDelta [ worker ] [ currentLayer ], currentDataset -> first,               backpropDeltaU [ worker ] [ currentLayer ] );

	}

	for ( auto & layer: backpropDeltaU [ worker ] ) layer *= learningSpeed;

	threadDeltaUStash [ worker ] += backpropDeltaU [ worker ];

	return & backpropDeltaU [ worker ];

}

void neural_network::learn ( const vector < pair < vector < double >, vector < double > > > & _datasetsArg, double _learningSpeed, double maxError = 1e-7, long long reportFrequency = 0 ) {

	random_device localRD;
	mt19937 mersenneTwister ( localRD ( ) );
	//mt19937_64 mersenneTwister ( localRD ( ) );

	if ( !_datasetsArg.size ( ) ) return;

	this -> learningSpeed = - _learningSpeed / N_THREADS / N_RUNS;
	this -> nDatasets = _datasetsArg.size ( );

    auto datasetsArg = _datasetsArg;

	/* Adding a 1 to each datasetsArg input */
	for ( size_t ds = 0; ds < datasetsArg.size ( ); ++ ds )
		datasetsArg [ ds ].first.push_back ( 1 );

	double error;

	long long nIterations = 0;

	size_t t = 0;
	vector < pair < vector < double >, vector < double > > * > datasetsQueue;

	setThreadVectors ( );

	clearDeltaU ( );

	goto skipbp;

	clearDeltaU ( );

	redoBP:;

	++ nIterations;

	/* Choose ceil ( sqrt ( datasetsArg.size ( ) ) ) random datasets */

	datasetsQueue.clear ( );

	/*for ( size_t i = 0; i < ceil ( ( float ) sqrt ( datasetsArg.size ( ) ) ); ++ i )
		datasetsQueue.push_back ( & datasetsArg [ lib::randInt ( datasetsArg.size ( ) ) ] );*/

	for ( size_t i = 0; i < datasetsArg.size ( ); ++ i )
		datasetsQueue.push_back ( & datasetsArg [ i ] );

	shuffle ( datasetsQueue.begin ( ), datasetsQueue.end ( ), mersenneTwister );

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

	if ( nIterations % N_RUNS == 0 ) {

		for ( size_t thread = 0; thread < threadDeltaUStash.size ( ); ++ thread )
		weights += threadDeltaUStash [ thread ];

		clearDeltaU ( );

	}

	if ( datasetsQueue.size ( ) ) goto finishit;

	skipbp:;

	if ( nIterations % reportFrequency != 0 ) goto redoBP;
	else printf("%lld iterations\n", nIterations);

	error = 0;

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

void neural_network::learnDatabase ( const database & db, double learningSpeed, double maxError = 1e-7, long long reportFrequency = 0 ) {

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

	learn ( datasets, learningSpeed, maxError, reportFrequency );

}
