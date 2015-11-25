#include "neural_network.h"

ostream & operator<< ( ostream & os, const neural_network & n ) {

    os << n.layers.size ( ) << "\n";

    for ( int i = 0; i < n.layers.size ( ); ++ i )
        os << n.layers [ i ];

    return os;

}

istream & operator>> ( istream & is, neural_network & n ) {

    n.layers.clear ( );

    int nLayers;

    is >> nLayers;

    for ( int i = 0; i < nLayers; ++ i ) {

        n.layers.push_back ( layer ( ) );
        is >> n.layers [ n.layers.size ( ) - 1 ];

    }

    return is;

}

vector < long double > neural_network::run ( vector < long double > input ) {

    vector < long double > output;

    for ( int i = 0; i < layers.size ( ); ++ i ) {

        output = this -> layers [ i ].run ( input, i );

        input = output;

    }

    return output;

}

neural_network::neural_network ( ) { }

neural_network::neural_network ( istream & is ) {

	is >> *this;

}

/*neural_network::neural_network ( string filename ) {

	ifstream inFile;
	inFile.open ( filename );
	if ( inFile.is_open ( ) )
		inFile >> *this;
	inFile.close ( );

}*/
