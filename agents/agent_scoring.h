#pragma once

#include <includes.h>

#include <agent.h>

long long boardScore ( board, int );

class agent_scoring : public agent {

	public:

		board_turn doTurn ( board, int );

	protected:

	private:

};

