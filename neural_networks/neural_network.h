#pragma once

#include <includes.h>

#include <layer.h>

#include <fstream>

class neural_network {

	public:

		neural_network ( string );

		neural_network ( istream & );

		bool init ( string );

		//neural_network ( string filename );

		vector < double > run ( vector < double > input );

		vector < layer >  layers;

		void learn ( vector < pair < vector < double >, vector < double > > > datasets, double maxError, double learningSpeed, long long reportFrequency );

	protected:

	private:
	
		void addToWeights ( vector < vector < vector < double > > > delta );

};

ostream & operator<< ( ostream &, const neural_network & );
istream & operator>> ( istream &, neural_network & );
