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

void neural_network::setThreadVectors ( ) {

	workerQueue.resize ( N_THREADS );
	workerThreads.resize ( N_THREADS );

	backpropDeltaU.resize ( N_THREADS );
	backpropA.resize ( N_THREADS );
	backpropDivergenceOutdata.resize ( N_THREADS );

	for ( unsigned i = 0; i < N_THREADS; ++ i ) {

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

vector < vector < vector < double > > > * neural_network::workerFunc ( int worker ) {

    if ( !workerQueue [ worker ].size ( ) ) return nullptr;

	pair < vector < double >, vector < double > > * currentDataset = workerQueue [ worker ].back ( );
	workerQueue [ worker ].pop_back ( );

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

void neural_network::learn ( vector < pair < vector < double >, vector < double > > > datasetsArg, double maxError = 1e-7, double learningSpeed = 0.5, long long reportFrequency = 0 ) {

	if ( !datasetsArg.size ( ) ) return;
	
	this -> learningSpeed = learningSpeed;
	this -> nDatasets = datasetsArg.size ( );

	/* Adding a 1 to each datasetsArg input */
	for ( size_t ds = 0; ds < datasetsArg.size ( ); ++ ds )
		datasetsArg [ ds ].first.push_back ( 1 );

	/* Variables */
	vector < double > divergenceOutdata = * new vector < double > ( datasetsArg [ 0 ].second.size ( ), 0 );
	vector < vector < double > > a ( layers.size ( ) );
	vector < vector < double > > z ( layers.size ( ) );
	vector < vector < double > > sigmaPrim ( layers.size ( ) );
	vector < vector < double > > delta = * new vector < vector < double > > ( layers.size ( ) );
	vector < vector < vector < double > > > deltaU;

	for ( size_t i = 0; i < layers.size ( ); ++ i ) {

		deltaU.push_back ( * new vector < vector < double > > );
		sigmaPrim.push_back ( * new vector < double > );

		for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j ) {

			deltaU [ i ].push_back ( * new vector < double > );
			sigmaPrim [ i ].push_back ( 0 );

			for ( size_t k = 0; k < layers [ i ].neurons [ j ].weights.size ( ); ++ k ) deltaU [ i ] [ j ].push_back ( 0 );

		}
		
	}

	vector < pair < vector < double >, vector < double > > > datasets ( ceil ( ( float ) sqrt ( datasetsArg.size ( ) ) ) );
	cerr << "Training with " << datasets.size ( ) << " datasets.\n";

	/* Learning loop */
	for ( long long nLearns = 0;; ++ nLearns ) {

		/* Choose ceil ( sqrt ( datasetsArg.size ( ) ) ) random datasets */
		for ( size_t i = 0; i < ceil ( ( float ) sqrt ( datasetsArg.size ( ) ) ); ++ i )
            datasets [ i ] = ( datasetsArg [ lib::randInt ( datasets.size ( ) ) ] );

		double error = 0;

        /* Loop through datasets*/
		for ( size_t ds = 0; ds < datasets.size ( ); ++ ds ) {

            /* Clear our so far saved data. We need to clear these vectors we create too (can't be bothered at this moment), they are causing memory leaks */

            /* Calculate a and z for each layer */
			for ( size_t i = 0; i < layers.size ( ); ++ i ) {

				vector < vector < double > > layerWeights = layers [ i ].getWeights ( );

				if ( i != 0 ) z [ i ] = ( lib::matrixVectorMultiplication ( layerWeights, a [ i - 1 ] ) );
				else          z [ i ] = ( lib::matrixVectorMultiplication ( layerWeights, datasets [ ds ].first ) );

				for ( size_t j = 0; j < a [ i ].size ( ); ++ j )
					a [ i ] [ j ] = lib::phi ( z [ i ] [ j ] );

				if ( i != layers.size ( ) - 1 ) a [ i ].push_back ( 1 );

			}

            /* Calculate phi(z) - y */
			for ( size_t i = 0; i < datasets [ ds ].second.size ( ); ++ i ) {

				divergenceOutdata [ i ] = a [ layers.size ( ) - 1 ] [ i ] - datasets [ ds ].second [ i ];

			}

            /* Calculate sigmaPrim ( phi(z)(1-phi(z)) ) */
			for ( size_t i = 0; i < layers.size ( ); ++ i ) {

				for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j )
					sigmaPrim [ i ] [ j ] = lib::phi ( z [ i ] [ j ] ) * ( 1 - lib::phi ( z [ i ] [ j ] ) );

			}

            /* Add a 1 to each sigmaPrim (the bias) */
			for ( size_t i = 0; i < sigmaPrim.size ( ); ++ i ) {

				sigmaPrim [ i ].push_back ( 1.0L );

			}

            /* Calculate delta for output layer */
			delta [ layers.size ( ) - 1 ] = lib::vectorPairMul ( divergenceOutdata, sigmaPrim [ layers.size ( ) - 1 ] );

            /* If we have less than 2 layers (3 if we count the input layer), we skip the next loop */
			if ( layers.size ( ) < 2 ) goto tooFewLayers;

		    /* Calculate delta for the rest of the layers */
            for ( int i = layers.size ( ) - 2; 0 <= i; -- i ) {

				vector < vector < double > > nextLayerWeights = layers [ i + 1 ].getWeights ( );
				nextLayerWeights = lib::transpose ( nextLayerWeights );
				vector < double > part1 = lib::matrixVectorMultiplication ( nextLayerWeights, delta [ i + 1 ] );
				delta [ i ] = lib::vectorPairMul ( part1, sigmaPrim [ i ] );

			}

			tooFewLayers:;

            /* Add weight changes to deltaU */
			for ( size_t i = 0; i < layers.size ( ); ++ i ) {

				double learningCoefficient = ( double ) ( - learningSpeed / datasets.size ( ) );
				vector < double > v;
				if ( i != 0 ) v = a [ i - 1 ];
				else          v = datasets [ ds ].first;
				vector < vector < double > > datasetWeightChange = lib::vectorsToMatrix ( delta [ i ], v );
				datasetWeightChange = lib::matrixMulCoefficient ( learningCoefficient, datasetWeightChange );
				deltaU [ i ] = lib::matrixAdd ( deltaU [ i ], datasetWeightChange );

            }

		}

		/* Update weights, add deltaU to them */
		for ( size_t i = 0; i < layers.size ( ); ++ i ) {

			addToWeights ( deltaU );

			/*vector < vector < double > > weights = layers [ i ].getWeights ( );

			weights = lib::matrixAdd ( weights, deltaU [ i ] );

			layers [ i ].setWeights ( weights );*/

		}

		/* Calculate error */
		for ( size_t i = 0; i < datasets.size ( ); ++ i ) {

			vector < double > outdata = datasets [ i ].first;

			for ( size_t j = 0; j < layers.size ( ); ++ j ) {

				outdata.push_back ( 1.0L );

				auto layerWeights = layers [ j ].getWeights ( );

				outdata = lib::matrixVectorMultiplication ( layerWeights, outdata );

				for ( size_t od = 0; od < outdata.size ( ); ++ od ) outdata [ od ] = lib::phi ( outdata [ od ] );

			}

			for ( size_t j = 0; j < datasets [ i ].second.size ( ); ++ j )
				error += ( datasets [ i ].second [ j ] - outdata [ j ] ) * ( datasets [ i ].second [ j ] - outdata [ j ] );

		}

        /* Error should be divided by 2 times the number of datasets that we have */
		error /= 2 * datasets.size ( );

        /* If we have reached our error target, we break and tell the user */
		if ( error < maxError ) {

			if ( reportFrequency != -1 ) cout << nLearns << " iterations; error = " << error << endl;
			break;

		}

        /* If we should report progress at this time, we do so. */
		if ( ! ( reportFrequency == 0 || reportFrequency == -1 ) )
			if ( nLearns % reportFrequency == 0 ) cout << nLearns << " iterations; " << deb ( error ) << endl;

	}

}

void neural_network::addToWeights ( vector < vector < vector < double > > > delta ) {

	for ( size_t i = 0; i < layers.size ( ); ++ i ) {

		for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j ) {

			for ( size_t k = 0; k < layers [ i ].neurons [ j ].weights.size ( ); ++ k ) {

				layers [ i ].neurons [ j ].weights [ k ] += delta [ i ] [ j ] [ k ];

			}

		}

	}

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
