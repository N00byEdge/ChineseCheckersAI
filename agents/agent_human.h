#pragma once

#include <includes.h>

#include <agent.h>

#include <fstream>

class agent_human : public agent {

	public:

		agent_human ( );
		~agent_human ( );

		board_turn doTurn ( board, int );

	protected:

	private:

		bool shouldWriteData = false;
		string datafile = "";

		vector < pair < vector < double >, vector < double > > > datasets;

};
