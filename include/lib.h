#pragma once

#include <includes.h>
#include <random>

using namespace std;

namespace lib {

	map < pair < int, int >, pair < int, int > > getCoordTranslationTable ( );

	int charToInt ( char );

	int randInt ( );
	int randInt ( int mod );

	double phi ( double v );

	vector < double > matrixMul ( vector < vector < double > > &, vector < double > & );

	vector < vector < double > > transpose ( vector < vector < double > > & );
	vector < double > vectorPairMul ( vector < double > &, vector < double > & );
	template < typename T > vector < T > swapSign ( vector < T > & );
	double scalarProduct ( vector < double > &, vector < double > & );
	vector < vector < double > > vectorsToMatrix ( vector < double > &, vector < double > & );
	vector < vector < double > > matrixMultiplication ( vector < vector < double > > &, vector < vector < double > > & );
	vector < vector < double > > matrixAdd ( vector < vector < double > > &, vector < vector < double > > & );
	vector < vector < double > > matrixMulCoefficient ( double, vector < vector < double > > & );
	vector < double > matrixVectorMultiplication ( vector < vector < double > > &, vector < double > & );
	vector < vector < vector < double > > > tensorAdd ( vector < vector < vector < double > > > &, vector < vector < vector < double > > > & );
	vector < pair < vector < double >, vector < double > > > getDatasets ( istream & is );
	void printDatasets ( ostream & os, vector < pair < vector < double >, vector < double > > > datasets );
	double intToIndata ( int i, int player );

}

template < typename T > std::ostream & operator<< ( std::ostream & os, const std::vector < T > & v ) { os << "{ "; for ( size_t i = 0; i < v.size ( ); ++ i ) { os << v [ i ]; if ( i != v.size ( ) - 1 ) os << ", "; } os << " }"; return os; }
template < typename T1, typename T2 > std::ostream & operator<< ( ostream & os, const pair < T1, T2 > p ) { os << "{ " << p.first << ", " << p.second << " }"; return os; }
