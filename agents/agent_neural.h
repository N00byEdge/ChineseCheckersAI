#ifndef AGENT_NEURAL
#define AGENT_NEURAL

#include <includes.h>

#include <neural_network.h>

#include <iostream>

#include <agent.h>

class agent_neural : public agent {

	public:

		agent_neural ( istream );

		board_turn doTurn ( board, int );

	protected:

	private:

		neural_network nn;

};

#endif // AGENT_NEURAL
