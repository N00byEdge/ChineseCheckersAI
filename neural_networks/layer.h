#pragma once

#include <includes.h>

#include <neuron.h>

class layer {

	public:

		vector < double > run ( vector < double > input );
		vector < double > runNoPhi ( vector < double > input );

		vector < neuron > neurons;

		vector < vector < double > > getWeights ( );
		void setWeights ( vector < vector < double > > & );

	protected:

	private:

};

ostream & operator<< ( ostream &, const layer & );
istream & operator>> ( istream &, layer & );
