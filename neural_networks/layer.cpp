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

vector < long double > layer::run ( vector < long double > input, int nLayer ) {

    vector < long double > output;

    for ( int i = 0; i < this -> neurons.size ( ); ++ i ) {

        if ( nLayer == 0 ) {

            vector < long double > in = { input [ i ] };

            output.push_back ( this -> neurons [ i ].run ( in ) );

        } else output.push_back ( this -> neurons [ i ].run ( input ) );

    }

    return output;

}
