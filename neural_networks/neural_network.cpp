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

vector < long double > neural_network::run ( vector < long double > input ) {

    vector < long double > output;

    for ( int i = 0; i < layers.size ( ); ++ i ) {

		input.push_back ( 1.0L );

        output = layers [ i ].run ( input );

        input = output;

    }

    return output;

}

neural_network::neural_network ( ) { }

neural_network::neural_network ( istream & is ) {

	is >> * this;

}

void neural_network::learn ( vector < pair < vector < long double >, vector < long double > > > datasets, long double maxError = 1e-7, long double learningSpeed = 0.5, long long reportFrequency = 0 ) {

    /* Adding a 1 to each datasets input */
    for ( size_t ds = 0; ds < datasets.size ( ); ++ ds )
        datasets [ ds ].first.push_back ( 1 );

    /* Variables */
    vector < long double > divergenceOutdata;
    vector < vector < long double > > a;
    vector < vector < long double > > z;
    vector < vector < long double > > sigmaPrim;
    vector < vector < long double > > delta;
    vector < vector < vector < long double > > > deltaU;

	/* Learning loop */
	for ( long long nLearns = 0;; ++ nLearns ) {

        long double error = 0;

		/* Comments pending */

        deltaU.clear ( );

		for ( size_t i = 0; i < layers.size ( ); ++ i ) {

            deltaU.push_back ( * new vector < vector < long double > > );

			for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j ) {

                deltaU [ i ].push_back ( * new vector < long double > );

                for ( size_t k = 0; k < layers [ i ].neurons [ j ].weights.size ( ); ++ k ) deltaU [ i ] [ j ].push_back ( 0 );

			}
		}

		for ( size_t ds = 0; ds < datasets.size ( ); ++ ds ) {

            a.clear ( );
            z.clear ( );
            divergenceOutdata = * new vector < long double > ( datasets [ ds ].second.size ( ), 0 );
            sigmaPrim = * new vector < vector < long double > > ( layers.size ( ) );
            delta = * new vector < vector < long double > > ( layers.size ( ) );


			for ( size_t i = 0; i < layers.size ( ); ++ i ) {

				vector < vector < long double > > layerWeights = layers [ i ].getWeights ( );

				//cout << deb ( layerWeights ) << endl;

				if ( i != 0 ) z.push_back ( lib::matrixVectorMultiplication ( layerWeights, a [ i - 1 ] ) );
				else 		  z.push_back ( lib::matrixVectorMultiplication ( layerWeights, datasets [ ds ].first ) );
				a.push_back ( z [ z.size ( ) - 1 ] );

				for ( size_t j = 0; j < a [ a.size ( ) - 1 ].size ( ); ++ j )
					a [ a.size ( ) - 1 ] [ j ] = lib::phi ( a [ a.size ( ) - 1 ] [ j ] );

				if ( not ( i == layers.size ( ) - 1 ) ) a [ a.size ( ) - 1 ].push_back ( 1 );

			}

			for ( size_t i = 0; i < datasets [ ds ].second.size ( ); ++ i ) {

				divergenceOutdata [ i ] = a [ a.size ( ) - 1 ] [ i ] - datasets [ ds ].second [ i ];

			}

			for ( size_t i = 0; i < layers.size ( ); ++ i ) {

				for ( size_t j = 0; j < layers [ i ].neurons.size ( ); ++ j ) {

					sigmaPrim [ i ].push_back ( lib::phi ( z [ i ] [ j ] ) * ( 1 - lib::phi ( z [ i ] [ j ] ) ) );

				}

			}

			for ( size_t i = 0; i < sigmaPrim.size ( ); ++ i ) sigmaPrim [ i ].push_back ( 1.0L );

			delta [ layers.size ( ) - 1 ] = lib::vectorPairMul ( divergenceOutdata, sigmaPrim [ layers.size ( ) - 1 ] );

			if ( layers.size ( ) < 2 ) goto tooFewLayers;

			for ( size_t i = layers.size ( ) - 2;; ++ i ) {

				vector < vector < long double > > nextLayerWeights = layers [ i + 1 ].getWeights ( );
				nextLayerWeights = lib::transpose ( nextLayerWeights );
				vector < long double > part1 = lib::matrixVectorMultiplication ( nextLayerWeights, delta [ i + 1 ] );
				delta [ i ] = lib::vectorPairMul ( part1, sigmaPrim [ i ] );

				if ( i == 0 ) break;

			}

			tooFewLayers:;

			for ( size_t i = 0; i < layers.size ( ); ++ i ) {

				long double coeff = ( long double ) ( - learningSpeed / datasets [ ds ].second.size ( ) );
				vector < long double > v;
				if ( i != 0 ) v = a [ i - 1 ];
				else		  v = datasets [ ds ].first;
				vector < vector < long double > > datasetWeightChange = lib::vectorsToMatrix ( delta [ i ], v );
				datasetWeightChange = lib::matrixMulCoefficient ( coeff, datasetWeightChange );
				deltaU [ i ] = lib::matrixAdd ( deltaU [ i ], datasetWeightChange );

			}



		}

		/* Update weights */
		for ( size_t i = 0; i < layers.size ( ); ++ i ) {

			vector < vector < long double > > weights = layers [ i ].getWeights ( );

			weights = lib::matrixAdd ( weights, deltaU [ i ] );

			layers [ i ].setWeights ( weights );

		}

		/* Calculate error */

		for ( size_t i = 0; i < datasets.size ( ); ++ i ) {

			vector < long double > outdata = datasets [ i ].first;

			for ( size_t j = 0; j < layers.size ( ); ++ j ) {

                outdata.push_back ( 1.0L );

                auto layerWeights = layers [ j ].getWeights ( );

                outdata = lib::matrixVectorMultiplication ( layerWeights, outdata );

                for ( size_t od = 0; od < outdata.size ( ); ++ od ) outdata [ od ] = lib::phi ( outdata [ od ] );

			}

			for ( size_t j = 0; j < datasets [ i ].second.size ( ); ++ j ) {

				error += ( datasets [ i ].second [ j ] - outdata [ j ] ) * ( datasets [ i ].second [ j ] - outdata [ j ] );

			}


		}

		//error /= 2 * datasets.size ( );

        if ( error < maxError ) {

            if ( reportFrequency != -1 ) cout << nLearns << " iterations; error = " << error << endl;
            break;

        }

		if ( ! ( reportFrequency == 0 || reportFrequency == -1 ) ) {
            if ( nLearns % reportFrequency == 0 ) cout << nLearns << " iterations; " << deb ( error ) << endl;
		}

	}

}
