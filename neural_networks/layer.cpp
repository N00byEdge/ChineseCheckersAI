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

    for ( int i = 0; i < this -> neurons.size ( ); ++ i ) {

        output.push_back ( this -> neurons [ i ].run ( input ) );

    }

    return output;

}
