#ifndef NEURON
#define NEURON

#include <includes.h>

class neuron {

	public:

<<<<<<< HEAD
		long double run ( vector < long double > input );
		long double runNoPhi ( vector < long double > input );

		vector < long double > getWeights ( );
		
		vector < long double > weights;
=======
		neuron ( );

		long double run ( vector < long double > input );

		vector < long double > weights;

		long double bias;
>>>>>>> ecc80213894a6e9499cb1d319b2d7d71f197b65a

	protected:

	private:

};

ostream & operator<< ( ostream &, const neuron & );
istream & operator>> ( istream &, neuron & );

#endif // NEURON
