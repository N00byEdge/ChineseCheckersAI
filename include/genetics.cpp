#include <genetics.h>

bool operator< ( pair < double, vector < double > > & l, pair < double, vector < double > > & r ) {

	/* FIXME: make this faster by only having the payload be an index */
	return l.first < r.first;

}

genetics::genetics ( ): eng ( rd ( ) )  { }

float genetics::randomFloat ( float r1, float r2 ) {

	uniform_real_distribution < float > dist ( r1, r2 );

	return dist ( rd );

}

void genetics::nextGeneration ( ) {

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

	for ( size_t i = 0; i < defaultOffspring.size ( ); ++ i ) {

		offspring.push_back ( defaultOffspring );
		offspring [ offspring.size ( ) - 1 ] [ i ] *= randomFloat ( -1.5f, 1.5f );
		offspring [ offspring.size ( ) - 1 ] [ i ] += randomFloat ( -0.3f, 0.3f );

	}

	genepool = offspring;

}

void genetics::natrualSelection ( unsigned u, vector < double > ( * fitnessFunc ) ( vector < vector < double > > ) ) {

	vector < double > fitnesses = fitnessFunc ( genepool );
	vector < pair < double, vector < double > > > fitnessesPaired;

	for ( size_t i = 0; i < genepool.size ( ); ++ i ) fitnessesPaired.push_back ( { fitnesses [ i ], genepool [ i ] } );

	sort ( fitnessesPaired.begin ( ), fitnessesPaired.end ( ), less < pair < double, vector < double > > > ( ) );

	fitnessesPaired.resize ( genepool.size ( ) );

	for ( size_t i = 0; i < genepool.size ( ); ++ i ) genepool [ i ] = fitnessesPaired [ i ].second;

}
