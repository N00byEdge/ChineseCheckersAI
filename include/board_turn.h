#pragma once

#include <includes.h>

#include <board_move.h>

/* Board Turn class */
class board_turn {

	public:

		/* A vector of moves for the turn */
		vector < board_move > moves;

		void rotate ( );
		void rotate ( int steps );

	protected:

	private:

};

