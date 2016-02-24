#pragma once

#include <includes.h>

#include <layer.h>

#include <thread>
#include <fstream>

class neural_network {

	public:

		neural_network ( string );

		neural_network ( istream & );

		bool init ( string );

		//neural_network ( string filename );

		vector < double > run ( vector < double > input );

		vector < layer > layers;

		void learn ( vector < pair < vector < double >, vector < double > > > datasets, double maxError, double learningSpeed, long long reportFrequency );

	protected:

	private:

		void addToWeights ( vector < vector < vector < double > > > delta );
		vector < vector < vector < double > > > * workerFunc ( int );

		void remakeWeightCache ( );
		vector < vector < vector < double > > > weightCache;
		bool weightCacheIsOutdated = true;
		vector < vector < vector < double > > > & weights ( );

		void setThreadVectors ( );

		vector < vector < pair < vector < double >, vector < double > > * > > workerQueue;
		vector < thread > workerThreads;
		
		double learningSpeed;
		int nDatasets;
		
		vector < vector < vector < vector < double > > > > backpropDeltaU;
		vector < vector < vector < double > > > backpropSigmaPrim;
		vector < vector < vector < double > > > backpropDelta;
		vector < vector < vector < double > > > backpropA;
		vector < vector < vector < double > > > backpropZ;
		vector < vector < double > > backpropDivergenceOutdata;

};

ostream & operator<< ( ostream &, const neural_network & );
istream & operator>> ( istream &, neural_network & );
