#pragma once

#include <includes.h>

#include <agent.h>

class agent_polynomial : public agent {

	public:

		agent_polynomial ( );
		agent_polynomial ( vector < double > );

		board_turn doTurn ( board, int );

		double scoreBoard ( board & b, int player );

		vector < float > p;

	protected:

	private:

	    double scoreTurn ( board_turn &, board &, int );

};

