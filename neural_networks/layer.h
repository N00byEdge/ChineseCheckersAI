#ifndef LAYER
#define LAYER

#include <includes.h>

#include <neuron.h>

class layer {

    public:

        vector < long double > run ( vector < long double > input );
        vector < long double > runNoPhi ( vector < long double > input );

        vector < neuron > neurons;
		
		vector < vector < long double > > getWeights ( );
		void setWeights ( vector < vector < long double > > & );
		
    protected:

    private:

};

ostream & operator<< ( ostream &, const layer & );
istream & operator>> ( istream &, layer & );

#endif // LAYER
