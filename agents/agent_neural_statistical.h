#pragma once

#include <includes.h>

#include <neural_network.h>

#include <iostream>
#include <fstream>

#include <agent.h>

class agent_neural_statistical : public agent {

	public:

		agent_neural_statistical ( );
		agent_neural_statistical ( string );
		agent_neural_statistical ( istream & );
		agent_neural_statistical ( ifstream & );

		board_turn doTurn ( board, int );

	protected:

	private:

		neural_network nn;

};
