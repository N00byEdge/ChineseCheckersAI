#pragma once

#include <includes.h>
#include <database.h>

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

		vector < vector < vector < double > > > weights;

		void learn ( const vector < pair < vector < double >, vector < double > > > & datasets, double learningSpeed, double maxError, long long reportFrequency );
		void learnDatabase ( const database & db, double learningSpeed, double maxError, long long reportFrequency );

		string filename = "Neural Networks/temp.nn";

	protected:

	private:

		vector < vector < vector < double > > > * workerFunc ( int, pair < vector < double >, vector < double > > * );

		void clearDeltaU ( );

		void setThreadVectors ( );

		vector < thread > workerThreads;

		double learningSpeed;
		int nDatasets;

		vector < vector < vector < vector < double > > > > backpropDeltaU;
		vector < vector < vector < vector < double > > > > threadDeltaUStash;
		vector < vector < vector < double > > > backpropSigmaPrim;
		vector < vector < vector < double > > > backpropPart1;
		vector < vector < vector < double > > > backpropDelta;
		vector < vector < vector < double > > > backpropA;
		vector < vector < vector < double > > > backpropZ;
		vector < vector < double > > backpropDivergenceOutdata;

		vector < vector < vector < double > > > deltaU;

};

ostream & operator<< ( ostream &, const neural_network & );
istream & operator>> ( istream &, neural_network & );
