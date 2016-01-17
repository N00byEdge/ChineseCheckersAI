#include "agent_neural.h"

long double intToIndata ( int i, int player ) {

    switch ( i ) {

        case 0:
            return 0.0L;

        default:

            if ( i == player ) return 2.0L;
            return 1.0L;

    }

}

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
	for ( size_t i = 0; i < indata.size ( ); ++ i ) indata [ i ] = intToIndata( b.intToTile ( i ) -> getContents ( ), player );

    auto outdata = nn.run ( indata );

    cout << outdata << endl;

	return t;

}

agent_neural::agent_neural ( ): nn ( "ask" ) { }
agent_neural::agent_neural ( istream & is ): nn ( is ) { }
agent_neural::agent_neural ( ifstream & ifs ): nn ( ifs ) { }
