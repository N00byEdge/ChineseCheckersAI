#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include <includes.h>

#include <layer.h>

class neural_network {

	public:

		neural_network ( );

		neural_network ( istream & is );

		//neural_network ( string filename );

		vector < long double > run ( vector < long double > input );

		vector < layer >  layers;

	protected:

	private:

};

ostream & operator<< ( ostream &, const neural_network & );
istream & operator>> ( istream &, neural_network & );

#endif // NEURAL_NETWORK
