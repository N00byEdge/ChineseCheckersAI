#include "layer.h"

ostream & operator<< ( ostream & os, const layer & l ) {

	os << "\t" << l.neurons.size ( ) << "\n";

	for ( int i = 0; i < l.neurons.size ( ); ++ i  )
		os << l.neurons [ i ];

	return os;

}

istream & operator>> ( istream & is, layer & l ) {

	int nNeurons;

	is >> nNeurons;

	l.neurons.clear ( );

	for ( int i = 0; i < nNeurons; ++ i ) {

		l.neurons.push_back ( neuron ( ) );
		is >> l.neurons [ l.neurons.size ( ) - 1 ];

	}

	return is;

}

vector < long double > layer::run ( vector < long double > input ) {

	vector < long double > output;

	input.push_back ( 1.0L );

	for ( int i = 0; i < neurons.size ( ); ++ i ) output.push_back ( neurons [ i ].run ( input ) );

	return output;

}

vector < long double > layer::runNoPhi ( vector < long double > input ) {

	vector < long double > output;

	input.push_back ( 1.0L );

	for ( int i = 0; i < neurons.size ( ); ++ i ) output.push_back ( neurons [ i ].runNoPhi ( input ) );

	return output;

}

vector < vector < long double > > layer::getWeights ( ) {

	vector < vector < long double > > result;

	for ( size_t i = 0; i < neurons.size ( ); ++ i ) {

		result.push_back ( neurons [ i ].getWeights ( ) );

	}

	return result;

}

void layer::setWeights ( vector < vector < long double > > & v ) {

	for ( size_t i = 0; i < neurons.size ( ); ++ i ) neurons [ i ].weights = v [ i ];

}
