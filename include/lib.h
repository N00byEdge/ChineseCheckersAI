#pragma once

#include <includes.h>

using namespace std;

namespace lib {

	map < pair < int, int >, pair < int, int > > getCoordTranslationTable ( );

    int charToInt ( char );

    int randInt ( );
    int randInt ( int mod );

    long double phi ( long double v );

	vector < long double > matrixMul ( vector < vector < long double > > &, vector < long double > & );

	vector < vector < long double > > transpose ( vector < vector < long double > > & );
	vector < long double > vectorPairMul ( vector < long double > &, vector < long double > & );
	template < typename T > vector < T > swapSign ( vector < T > & );
	long double scalarProduct ( vector < long double > &, vector < long double > & );
	vector < vector < long double > > vectorsToMatrix ( vector < long double > &, vector < long double > & );
	vector < vector < long double > > matrixMultiplication ( vector < vector < long double > > &, vector < vector < long double > > & );
	vector < vector < long double > > matrixAdd ( vector < vector < long double > > &, vector < vector < long double > > & );
	vector < vector < long double > > matrixMulCoefficient ( long double, vector < vector < long double > > & );
	vector < long double > matrixVectorMultiplication ( vector < vector < long double > > &, vector < long double > & );
	vector < vector < vector < long double > > > tensorAdd ( vector < vector < vector < long double > > > &, vector < vector < vector < long double > > > & );

}

template < typename T > std::ostream & operator<< ( std::ostream & os, const std::vector < T > & v ) { os << "{ "; for ( size_t i = 0; i < v.size ( ); ++ i ) { os << v [ i ]; if ( i != v.size ( ) - 1 ) os << ", "; } os << " }"; return os; }
template < typename T1, typename T2 > std::ostream & operator<< ( ostream & os, const pair < T1, T2 > p ) { os << "{ " << p.first << ", " << p.second << " }"; return os; }
