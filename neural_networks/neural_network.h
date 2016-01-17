#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include <includes.h>

#include <layer.h>

class neural_network {

	public:

<<<<<<< HEAD
		neural_network ( );
=======
        vector < long double > run ( vector < long double > input );

        vector < layer >  layers;

    protected:
>>>>>>> ecc80213894a6e9499cb1d319b2d7d71f197b65a

		neural_network ( istream & is );

<<<<<<< HEAD
		//neural_network ( string filename );

		vector < long double > run ( vector < long double > input );

		vector < layer >  layers;

		void learn ( vector < pair < vector < long double >, vector < long double > > > datasets, long double maxError, long double learningSpeed, long long reportFrequency );

	protected:

	private:

=======
>>>>>>> ecc80213894a6e9499cb1d319b2d7d71f197b65a
};

ostream & operator<< ( ostream &, const neural_network & );
istream & operator>> ( istream &, neural_network & );

#endif // NEURAL_NETWORK
