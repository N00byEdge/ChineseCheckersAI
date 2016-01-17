#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include <includes.h>

#include <layer.h>

#include <fstream>

class neural_network {

	public:

		neural_network ( string );

		neural_network ( istream & );

		bool init ( string );

		//neural_network ( string filename );

		vector < long double > run ( vector < long double > input );

		vector < layer >  layers;

		void learn ( vector < pair < vector < long double >, vector < long double > > > datasets, long double maxError, long double learningSpeed, long long reportFrequency );

	protected:

	private:

};

ostream & operator<< ( ostream &, const neural_network & );
istream & operator>> ( istream &, neural_network & );

#endif // NEURAL_NETWORK
