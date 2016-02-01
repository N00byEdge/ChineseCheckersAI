#pragma once

#include <includes.h>

#include <agent.h>
#include <database.h>
#include <fstream>

class agent_statistical : public agent {

	public:

        agent_statistical ( );
        agent_statistical ( database );
        ~agent_statistical ( );

		board_turn doTurn ( board, int );

	protected:

	private:

		database & extDB;
        database localDB;

};
