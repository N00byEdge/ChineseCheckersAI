#pragma once

#include <includes.h>
#include <random>

using namespace std;

namespace lib {

    /* Good things */
	map < pair < int, int >, pair < int, int > > getCoordTranslationTable ( );

	int charToInt ( char );

	int randInt ( );
	int randInt ( int mod );

	double phi ( double v );

	void vectorsToMatrix ( vector < double > &, vector < double > &, vector < vector < double > > & );
	double intToIndata ( int i, int player );

    vector < double > matrixMul ( vector < vector < double > > &, vector < double > & );
	vector < vector < double > > matrixMultiplication ( const vector < vector < double > > &, const vector < vector < double > > & );

	vector < double > matrixVectorMultiplication ( const vector < vector < double > > &, const vector < double > & );
	vector < double > matrixTransposeVectorMultiplication ( const vector < vector < double > > &, const vector < double > & );

    vector < double > vectorPairMul ( const vector < double > &, const vector < double > & );

	/* Please only use datasets if you need to. While they work, they don't do much for AI (read our paper) */
	vector < pair < vector < double >, vector < double > > > getDatasets ( istream & is );
	void printDatasets ( ostream & os, vector < pair < vector < double >, vector < double > > > datasets );

}

/* Good things */
template < typename T > std::ostream & operator<< ( std::ostream & os, const std::vector < T > & v ) { os << "{ "; for ( size_t i = 0; i < v.size ( ); ++ i ) { os << v [ i ]; if ( i != v.size ( ) - 1 ) os << ", "; } os << " }"; return os; }
template < typename T1, typename T2 > std::ostream & operator<< ( ostream & os, const pair < T1, T2 > p ) { os << "{ " << p.first << ", " << p.second << " }"; return os; }
void operator += ( vector < vector < vector < double > > > &, const vector < vector < vector < double > > > & );
void operator *= ( vector < vector < double > > &, double );
