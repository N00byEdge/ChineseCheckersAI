#ifndef LAYER
#define LAYER

#include <includes.h>

#include <neuron.h>

class layer {

    public:

        vector < long double > run ( vector < long double > input );
<<<<<<< HEAD
        vector < long double > runNoPhi ( vector < long double > input );

        vector < neuron > neurons;
		
		vector < vector < long double > > getWeights ( );
		void setWeights ( vector < vector < long double > > & );
		
=======

        vector < neuron > neurons;

>>>>>>> ecc80213894a6e9499cb1d319b2d7d71f197b65a
    protected:

    private:

};

ostream & operator<< ( ostream &, const layer & );
istream & operator>> ( istream &, layer & );

#endif // LAYER
