#pragma once

#include <includes.h>

class genetics {

	public:

		genetics ( );

    	void nextGeneration ( );
		
		vector < vector < double > > genepool;
		
		void natrualSelection ( unsigned, vector < double > ( * fitnessFunc ) ( vector < vector < double > > ) );

	protected:

	private:
	
		random_device rd;
		mt19937_64 eng;
		double randomDouble ( double, double );

};
