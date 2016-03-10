#pragma once

#include <includes.h>

class genetics {

	public:

		genetics ( );

    	void nextGeneration ( size_t );

		vector < vector < double > > genepool;
		vector < double > fitnessPolynomialAgents ( );

		void randomizeGenepool ( size_t, size_t, size_t, size_t );

		void natrualSelection ( unsigned, string );

	protected:

	private:

		random_device rd;
		mt19937_64 eng;
		double randomDouble ( double, double );

};
