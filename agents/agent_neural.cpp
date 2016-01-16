#include "agent_neural.h"

board_turn agent_neural::doTurn ( board b, int player ) {

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

	vector < long double > indata ( 121, 0 );
	for ( size_t i = 0; i < indata.size ( ); ++ i ) indata [ i ] = b.intToTile ( i ) -> getContents ( );

    auto outdata = nn.run ( indata );

	return t;

}

agent_neural::agent_neural ( istream is ): nn ( is ) { }
