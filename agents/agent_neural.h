#ifndef AGENT_NEURAL
#define AGENT_NEURAL

#include <includes.h>

#include <neural_network.h>

#include <iostream>
#include <fstream>

#include <agent.h>

class agent_neural : public agent {

	public:

        agent_neural ( );
		agent_neural ( istream & );
		agent_neural ( ifstream & );

		board_turn doTurn ( board, int );

	protected:

	private:

		neural_network nn;

};

#endif // AGENT_NEURAL
