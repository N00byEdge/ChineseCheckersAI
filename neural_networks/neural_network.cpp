#include "neural_network.h"

ostream & operator<< ( ostream & os, const neural_network & n ) {

	os << n.layers.size ( ) << "\n";

	for ( int i = 0; i < n.layers.size ( ); ++ i )
		os << n.layers [ i ];

	return os;

}

istream & operator>> ( istream & is, neural_network & n ) {

	n.layers.clear ( );

	int nLayers;

	is >> nLayers;

	for ( int i = 0; i < nLayers; ++ i ) {

		n.layers.push_back ( layer ( ) );
		is >> n.layers [ n.layers.size ( ) - 1 ];

	}

	return is;

}

vector < double > neural_network::run ( vector < double > input ) {

	vector < double > output;

	for ( int i = 0; i < layers.size ( ); ++ i ) {

		input.push_back ( 1.0L );

		vector < vector < double > > layerWeights = layers [ i ].getWeights ( );

		output = ( lib::matrixVectorMultiplication ( layerWeights, input ) );

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

	setThreadVectors ( );

	is >> * this;

}

void neural_network::clearDeltaU ( ) {
	
	for ( auto i: deltaU )
		for ( auto j: i )
			for ( auto k: j )
				k = 0;
	
}

void neural_network::setThreadVectors ( ) {
	
	deltaU.resize ( layers.size ( ) );
	
	for ( size_t i = 0; i < layers.size ( ); ++ i ) {
		
		deltaU [ i ].resize ( layers [ i ].neurons.size ( ) );
		
		for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j ) {
			
			deltaU [ i ] [ j ].resize ( layers [ i ].neurons [ j ].weights.size ( ) );
			
			for ( auto v: deltaU [ i ] [ j ] ) v = 0;
			
		}
		
	}

	workerQueue.resize ( N_THREADS );
	workerThreads.resize ( N_THREADS );

	backpropDeltaU.resize ( N_THREADS );
	backpropA.resize ( N_THREADS );
	backpropDivergenceOutdata.resize ( N_THREADS );

	for ( size_t i = 0; i < N_THREADS; ++ i ) {

		backpropDeltaU    [ i ].resize ( layers.size ( ) );
		backpropA         [ i ].resize ( layers.size ( ) );

		for ( size_t j = 0; j < layers.size ( ); ++ j ) {

			if ( j == layers.size ( ) - 1 ) backpropDivergenceOutdata.resize ( layers [ j ].neurons.size ( ) );

			backpropDeltaU    [ i ] [ j ].resize ( layers [ j ].neurons.size ( ) );
			backpropA         [ i ] [ j ].resize ( layers [ j ].neurons.size ( ) );

			for ( size_t k = 0; k < layers [ i ].neurons.size ( ); ++ k )
				backpropDeltaU [ i ] [ j ] [ k ].resize ( layers [ j ].neurons [ k ].weights.size ( ) );

		}

	}

	backpropZ = backpropA;
	backpropSigmaPrim = backpropA;
	backpropDelta = backpropA;

}

vector < vector < vector < double > > > * neural_network::workerFunc ( int worker, pair < vector < double >, vector < double > > * currentDataset ) {

	/* Calculate a and z */
	for ( size_t i = 0; i < layers.size ( ); ++ i ) {

		if ( i == 0 ) backpropZ [ worker ] [ i ] = lib::matrixVectorMultiplication ( weights ( ) [ i ], backpropA [ worker ] [ i - 1 ] );
		else          backpropZ [ worker ] [ i ] = lib::matrixVectorMultiplication ( weights ( ) [ i ], backpropA [ worker ] [ i - 1 ] );

		for ( size_t j = 0; j < backpropA [ worker ] [ i ].size ( ); ++ j )
			backpropA [ worker ] [ i ] [ j ] = lib::phi ( backpropZ [ worker ] [ i ] [ j ] );

		if ( i != layers.size ( ) - 1 ) backpropA [ worker ] [ i ].push_back ( 1 );

	}

	/* Calculate the outdata divergence, phi(z) - y = a - y */
	for ( size_t i = 0; i < currentDataset -> second.size ( ); ++ i )
		backpropDivergenceOutdata [ worker ] [ i ] = backpropA [ worker ] [ layers.size ( ) - 1 ] [ i ] - currentDataset -> second [ i ];

	/* Calculate sigmaPrim = a-(1-a) */
	for ( size_t i = 0; i < layers.size ( ); ++ i ) {

		for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j )
			backpropSigmaPrim [ worker ] [ i ] [ j ] = backpropA [ worker ] [ i ] [ j ] * ( 1 - backpropA [ worker ] [ i ] [ j ] );

	}

	/* Add bias to each sigmaPrim */
	for ( size_t i = 0; i < backpropSigmaPrim [ worker ].size ( ); ++ i )
		backpropSigmaPrim [ worker ] [ i ].push_back ( 1 );

	/* Delta for output layer */
	backpropDelta [ worker ] [ layers.size ( ) - 1 ] = lib::vectorPairMul ( backpropDivergenceOutdata [ worker ], backpropSigmaPrim [ worker ] [ layers.size ( ) - 1 ] );

	/* Delta for all other layers */
	size_t currentLayer = layers.size ( ) - 2;
	for ( ; currentLayer >= 0; -- currentLayer ) {
		vector < double > part1 = lib::matrixTransposeVectorMultiplication ( weights ( ) [ currentLayer + 1 ], backpropDelta [ worker ] [ currentLayer + 1 ] );
		backpropDelta [ worker ] [ currentLayer ] = lib::vectorPairMul (
			part1,
			backpropSigmaPrim [ worker] [ currentLayer ]
		);
	}

	/* Calculate deltaU */
	for ( size_t i = 0; i < layers.size ( ); ++ i ) {

		double learningCoefficient = ( double ) ( - learningSpeed / nDatasets );
		if ( i != 0 ) backpropDeltaU [ worker ] [ i ] = lib::vectorsToMatrix ( backpropDelta [ worker ] [ i ], backpropA [ worker ] [ i - 1 ] );
		else          backpropDeltaU [ worker ] [ i ] = lib::vectorsToMatrix ( backpropDelta [ worker ] [ i ], currentDataset -> first );
		backpropDeltaU [ worker ] [ i ] = lib::matrixMulCoefficient ( learningCoefficient, backpropDeltaU [ worker ] [ i ] );

	}

	return & backpropDeltaU [ worker ];

}

void neural_network::learn ( vector < pair < vector < double >, vector < double > > > & datasetsArg, double maxError = 1e-7, double learningSpeed = 0.5, long long reportFrequency = 0 ) {

	if ( !datasetsArg.size ( ) ) return;

	this -> learningSpeed = learningSpeed;
	this -> nDatasets = datasetsArg.size ( );

	/* Adding a 1 to each datasetsArg input */
	for ( size_t ds = 0; ds < datasetsArg.size ( ); ++ ds )
		datasetsArg [ ds ].first.push_back ( 1 );

	double error = 0;

	size_t t = 0;
	vector < pair < vector < double >, vector < double > > * > datasetsQueue;

	goto skipbp;

	redoBP:;

	/* Choose ceil ( sqrt ( datasetsArg.size ( ) ) ) random datasets */

	datasetsQueue.clear ( );
	clearDeltaU ( );

	cout << "Picking random datasets.\n" << flush;

	for ( size_t i = 0; i < ceil ( ( float ) sqrt ( datasetsArg.size ( ) ) ); ++ i )
		datasetsQueue.push_back ( & datasetsArg [ lib::randInt ( datasetsArg.size ( ) ) ] );
		
	/* Reset deltaU */

	finishit:;

	t = 0;

	while ( datasetsQueue.size ( ) && t < N_THREADS ) {

		cout << "Spawning thread " << t << endl;

		workerThreads [ t ] = move ( thread ( &neural_network::workerFunc, this, t, datasetsQueue.back ( ) ) );
		datasetsQueue.pop_back ( );

		++ t;

	}

	for ( size_t i = 0; i < t; ++ i ) {

		cout << "Waiting for thread " << i << endl;

		workerThreads [ i ].join ( );
		deltaU = lib::tensorAdd ( backpropDeltaU [ i ], deltaU );

	}

	if ( datasetsQueue.size ( ) ) goto finishit;

	skipbp:;

	/* Calculate error */
	for ( size_t i = 0; i < datasetsArg.size ( ); ++ i ) {

		vector < double > outdata = datasetsArg [ i ].first;

		for ( size_t j = 0; j < layers.size ( ); ++ j ) {

			outdata.push_back ( 1.0L );

			auto layerWeights = layers [ j ].getWeights ( );

			outdata = lib::matrixVectorMultiplication ( layerWeights, outdata );

			for ( size_t od = 0; od < outdata.size ( ); ++ od ) outdata [ od ] = lib::phi ( outdata [ od ] );

		}

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

void neural_network::addToWeights ( vector < vector < vector < double > > > delta ) {

	for ( size_t i = 0; i < layers.size ( ); ++ i ) {

		for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j ) {

			for ( size_t k = 0; k < layers [ i ].neurons [ j ].weights.size ( ); ++ k ) {

				layers [ i ].neurons [ j ].weights [ k ] += delta [ i ] [ j ] [ k ];

			}

		}

	}
	
	weightCacheIsOutdated = true;

}

void neural_network::remakeWeightCache ( ) {

	weightCache.resize ( layers.size ( ) );

	for ( size_t i = 0; i < layers.size ( ); ++ i ) {

		weightCache [ i ].resize ( layers [ i ].neurons.size ( ) );

		for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j ) {

			weightCache [ i ] [ j ].resize ( layers [ i ].neurons [ j ].weights.size ( ) );

			for ( size_t k = 0; k < layers [ i ].neurons [ j ].weights.size ( ); ++ k )
				weightCache [ i ] [ j ] [ k ] = layers [ i ].neurons [ j ].weights [ k ];

		}

	}

}

vector < vector < vector < double > > > & neural_network::weights ( ) {

	if ( weightCacheIsOutdated ) remakeWeightCache ( );
	return weightCache;

}
