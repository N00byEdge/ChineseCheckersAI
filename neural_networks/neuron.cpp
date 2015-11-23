#include "neuron.h"

ostream & operator<< ( ostream & os, const neuron & n ) {

	vector < pair < long double, long double > > rawInputs = n.getRawInputs ( );

	os << "\t\t" << rawInputs.size ( ) << "\n";

	if ( 0 < rawInputs.size ( ) )
		os << "\t\t\t";

	for ( int i = 0; i < rawInputs.size ( ); ++ i ) {
		os << rawInputs [ i ].first << " " << rawInputs [ i ].second << " ";
	}

	if ( 0 < rawInputs.size ( ) )
		os << "\n";

	os << "\t\t" << n.getBias ( ) << " ";

    vector < pair < neuron * , long double > > neuronInputs = n.getInputNeurons ( );

	for ( int i = 0; i < neuronInputs.size ( ); ++ i ) {
		os << neuronInputs [ i ].first << " ";
	}

	os << "\n";

	return os;

}

long double randWeight ( ) {

	return
		( long double )
			( lib::randInt ( ) )

		/

		( long double )
			( std::numeric_limits < int >::max ( ) );

}

neuron::neuron ( vector < neuron * > lastLayer, istream & is ) {

	int n = 0;

	is >> n;

	for ( int i = 0; i < n; ++ i ) {

		long double input, weight;

		is >> input >> weight;

		this -> addRawInputWithWeight ( input, weight );

	}

	long double bias;
	is >> bias;

	this -> bias = bias;

	for ( int i = 0; i < lastLayer.size ( ); ++ i ) {

		long double weight;

		is >> weight;

		this -> addNeuronWithWeight ( lastLayer [ i ], weight );

	}

}

neuron::neuron ( ) {

    this -> setBias ( 1 );

}

long double neuron::value ( ) {

	long double ld = 0;

	for ( int i = 0; i < neuronInputs.size ( ); ++ i )

		ld += this -> neuronInputs [ i ].second * this -> neuronInputs [ i ].first -> value ( );

	for ( int i = 0; i < rawInputs.size ( ); ++ i )

		ld += this -> rawInputs [ i ].second * this -> rawInputs [ i ].first;

	ld += this -> bias;

	return ld;

}

void neuron::addRawInput ( long double ld ) {

	return this -> addRawInputWithWeight ( ld, 1 );

}

void neuron::addRawInputWithWeight ( long double input, long double weight ) {

	pair < long double, long double > pldld = { input, weight };

 	this -> rawInputs.push_back ( pldld );

}

vector < pair < long double, long double > > neuron::getRawInputs ( ) const {

	return this -> rawInputs;

}

void neuron::setRawInputs ( vector < pair < long double, long double > > vpldld ) {

	this -> rawInputs = vpldld;

}

void neuron::addNeuron ( neuron * n ) {

	return this -> addNeuronWithWeight ( n, 1 );

}

void neuron::addNeuronWithWeight ( neuron * n, long double weight ) {

	pair < neuron *, long double > pnld = { n, weight };

	this -> neuronInputs.push_back ( pnld );

}

vector < pair < neuron *, long double > > neuron::getInputNeurons ( ) const {

	return this -> neuronInputs;

}

void neuron::setInputNeurons ( vector < pair < neuron *, long double > > vpnld ) {

	this -> neuronInputs = vpnld;

}

long double neuron::getBias ( ) const {

	return this -> bias;

}

void neuron::setBias ( long double bias ) {

	this -> bias = bias;

}
