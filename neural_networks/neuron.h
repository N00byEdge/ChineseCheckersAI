#pragma once

#include <includes.h>

class neuron {

	public:

		double run ( vector < double > input );
		double runNoPhi ( vector < double > input );

		vector < double > getWeights ( );

		vector < double > weights;

	protected:

	private:

};

ostream & operator<< ( ostream &, const neuron & );
istream & operator>> ( istream &, neuron & );
