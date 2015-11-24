#include "neuron.h"

ostream & operator<< ( ostream & os, const neuron & n ) {

	os << "\t\t" << n.weights.size ( ) << "\n";

	os << "\t\t" << n.bias << " ";

	for ( int i = 0; i < n.weights.size ( ); ++ i ) {

		os << n.weights [ i ] << " ";

	} os << "\n";

}

istream & operator>> ( istream & is , neuron & n ) {

	int nWeights;

	is >> nWeights;

	is >> n.bias;

	n.weights.clear ( );

	for ( int i = 0; i < nWeights; ++ i ) {

		long long weight;

		is >> weight;

		n.weights.push_back ( weight );

	}

}

neuron::neuron ( ) {

    this -> bias = 0;

}

long double neuron::run ( vector < long double > input ) {

	if ( input.size ( ) == weights.size ( ) ) {

		long long ll = 0;

		for ( int i = 0; i < input.size ( ); ++ i )
			ll += input [ i ] * weights [ i ];

		ll += bias;

		return ll;

	} return 0.0l;

}
