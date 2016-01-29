#include "neuron.h"

ostream & operator<< ( ostream & os, const neuron & n ) {

	os << "\t\t" << n.weights.size ( ) << "\n";

	os << "\t\t";

	for ( int i = 0; i < n.weights.size ( ); ++ i ) {

		os << n.weights [ i ] << " ";

	} os << "\n";

	return os;

}

istream & operator>> ( istream & is , neuron & n ) {

	int nWeights;

	is >> nWeights;

	n.weights.clear ( );

	for ( int i = 0; i < nWeights; ++ i ) {

		double weight;

		is >> weight;

		n.weights.push_back ( weight );

	}

	return is;

}

double neuron::run ( vector < double > input ) {

	if ( input.size ( ) == weights.size ( ) ) {

		double ld = 0;

		for ( int i = 0; i < input.size ( ); ++ i ) {

			ld += input [ i ] * weights [ i ];

		}

		cout << ld << endl;

		return lib::phi ( ld );

	} return 0.0l;

}

double neuron::runNoPhi ( vector < double > input ) {

	if ( input.size ( ) == weights.size ( ) ) {

		double ld = 0;

		for ( int i = 0; i < input.size ( ); ++ i ) {

			ld += input [ i ] * weights [ i ];

		}

		return ld;

	} return 0.0l;

}

vector < double > neuron::getWeights ( ) {

	return weights;

}
