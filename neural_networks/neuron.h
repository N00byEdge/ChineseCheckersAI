#ifndef NEURON
#define NEURON

#include <includes.h>

class neuron {

	public:

		long double run ( vector < long double > input );
		long double runNoPhi ( vector < long double > input );

		vector < long double > getWeights ( );

		vector < long double > weights;

	protected:

	private:

};

ostream & operator<< ( ostream &, const neuron & );
istream & operator>> ( istream &, neuron & );

#endif // NEURON
