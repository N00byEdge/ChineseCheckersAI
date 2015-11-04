#include "agent_scoring.h"

board_turn agent_scoring::doTurn ( board b, int player ) {

	/* 

		This will be called when the agents needs to make a move.

		You are provided with
			-the board b: This is the current board state.
			-the int player: This is the player number of this agent on the board b.

		All your tiles on the board will have the contents of the int player.

		for all your tiles t, t.getContents ( ) = player.

		You cannot add on more arguments for this function.

	*/

	board_turn t;

	while ( 5 ) {

		board_move m;

		// Do your logic here

		t.moves.push_back ( m );

	}

	return t;

}
