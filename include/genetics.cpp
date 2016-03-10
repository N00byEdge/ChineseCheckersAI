#include <genetics.h>

#include <automatedGame.h>

#include <algorithm>

#include <iostream>

vector < double > genetics::fitnessPolynomialAgents ( ) {

	std::cout << "kör den här koden ens?\n" << std::flush;

    vector < double > totalTurnsToWin ( genepool.size ( ), 0 );

    std::random_shuffle ( genepool.begin ( ), genepool.end ( ) );

    std::cout << "dags att börja loooopa\n" << std::flush;

    for ( size_t firstAgentN = 0; firstAgentN < genepool.size ( ); ++ firstAgentN ) {

        for ( size_t secondAgentN = firstAgentN + 1; secondAgentN < firstAgentN + min ( ( size_t ) 7, genepool.size ( ) ); ++ secondAgentN ) {

        	size_t secondAgentN2 = secondAgentN % genepool.size ( );

        	std::cout << "initiating game " << firstAgentN << " vs " << secondAgentN2 << "\n" << std::flush;

            agent_polynomial firstAgent ( genepool [ firstAgentN ] );
            agent_polynomial secondAgent ( genepool [ secondAgentN2 ] );

            automatedGame game;
            game.players = { & firstAgent, & secondAgent };
            game.startGame ( );

            std::cout << "game " << firstAgentN << " vs " << secondAgentN2 << " finished\n" << std::flush;

            totalTurnsToWin [ firstAgentN ] += game.turnsToWin [ 0 ];
            totalTurnsToWin [ secondAgentN2 ] += game.turnsToWin [ 1 ];

        }

    }

    std::cout << totalTurnsToWin << "\n" << std::flush;

    /* We also multiply by -1, since a lower number of turns means higher fitness. */
    for ( auto & entry: totalTurnsToWin ) entry /= - (genepool.size ( ) -1);

    return totalTurnsToWin;

}

bool operator< ( pair < double, vector < double > > & l, pair < double, vector < double > > & r ) {

	/* FIXME: make this faster by only having the payload be an index */
	return l.first < r.first;

}

void genetics::randomizeGenepool ( size_t nSets, size_t nGenomesPerSet, size_t minRand, size_t maxRand ) {

    normal_distribution < double > dist ( 0, 0.5 );

    genepool.resize ( nSets );
    for ( auto & g: genepool ) g.resize ( nGenomesPerSet );

    for ( size_t n = 0; n < nSets; ++ n )
        for ( size_t g = 0; g < nGenomesPerSet; ++ g )
            genepool [ n ] [ g ] = dist ( rd );

    cerr << genepool << endl;

}

genetics::genetics ( ): eng ( rd ( ) )  { }

    double genetics::randomDouble ( double r1, double r2 ) {

	uniform_real_distribution < double > dist ( r1, r2 );

	return dist ( rd );

}

void genetics::nextGeneration ( size_t u ) {

    uniform_int_distribution < int > dist ( 0, genepool.size ( ) );

	if ( !genepool.size ( ) || !genepool [ 0 ].size ( ) ) {

		cerr << "CreateOffspring must be run with valid parents.\n";
		return;

	}

	vector < vector < double > > offspring;

	vector < double > defaultOffspring;

	for ( size_t i = 0; i < genepool [ 0 ].size ( ); ++ i ) {

		long double avgGenome = 0;

		for ( size_t j = 0; j < genepool.size ( ); ++ j ) {

			avgGenome += genepool [ j ] [ i ];

		}

		defaultOffspring.push_back ( avgGenome / genepool.size ( ) );

	}

	for ( size_t i = 0; i < u; ++ i ) {

		offspring.push_back ( defaultOffspring );
		size_t randGenome = dist ( eng );
		offspring [ offspring.size ( ) - 1 ] [ randGenome ] *= randomDouble ( -1.5f, 1.5f );
		offspring [ offspring.size ( ) - 1 ] [ randGenome ] += randomDouble ( -0.3f, 0.3f );

	}

	genepool = offspring;

}

void genetics::naturalSelection ( unsigned u, string algo ) {

    size_t genepoolTargetSize = genepool.size ( );

    nextGeneration ( u );

    vector < double > fitnesses ( genepool.size ( ), 0 );

    if ( algo == "agent_polynomial" ) fitnesses = fitnessPolynomialAgents ( );

	vector < pair < double, vector < double > > > fitnessesPaired;

	for ( size_t i = 0; i < genepool.size ( ); ++ i ) fitnessesPaired.push_back ( { fitnesses [ i ], genepool [ i ] } );

	sort ( fitnessesPaired.begin ( ), fitnessesPaired.end ( ), greater < pair < double, vector < double > > > ( ) );

	fitnessesPaired.resize ( genepoolTargetSize );

	for ( size_t i = 0; i < genepool.size ( ); ++ i ) genepool [ i ] = fitnessesPaired [ i ].second;

	cerr << genepool << endl;

}
