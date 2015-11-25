#ifndef NEURON
#define NEURON

#include <includes.h>

class neuron {

	public:

		neuron ( );

		long double run ( vector < long double > input );

		vector < long double > weights;

		long double bias;

	protected:

	private:

};

ostream & operator<< ( ostream &, const neuron & );
istream & operator>> ( istream &, neuron & );

#endif // NEURON
