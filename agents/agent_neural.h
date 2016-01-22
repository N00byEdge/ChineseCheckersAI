#pragma once

#include <includes.h>

#include <neural_network.h>

#include <iostream>
#include <fstream>

#include <agent.h>

class agent_neural : public agent {

	public:

		agent_neural ( );
		agent_neural ( string );
		agent_neural ( istream & );
		agent_neural ( ifstream & );

		board_turn doTurn ( board, int );

	protected:

	private:

		neural_network nn;

};
