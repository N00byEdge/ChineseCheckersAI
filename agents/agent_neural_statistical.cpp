#include "agent_neural_statistical.h"

board_turn agent_neural_statistical::doTurn ( board b, int player ) {

	/*

		This will be called when the agents needs to make a move.

		You are provided with
			-the board b: This is the current board state.
			-the int player: This is the player number of this agent on the board b.

		All your tiles on the board will have the contents of the int player.

		for all your tiles t, t.getContents ( ) = player.

		You cannot add on more arguments for this function.

	*/

	cout << "Player #" << player << "s turn, neural statistical agent.\n";

	b.print ( );

	auto originalBoard = b;
	int nRotations = b.rotateForPerspective ( player );

	board_turn t;

	vector < board_turn > possibleTurns = b.findAllPossibleTurns ( player );

	board_turn bestTurn = possibleTurns [ 0 ];
	double bestScore = 0;

	for ( size_t i = 0; i < possibleTurns.size ( ); ++ i ) {

		board b2 = b;
		b2.makeTurn ( possibleTurns [ i ] );

		vector < double > indata ( 121, 0 );
		for ( size_t i = 0; i < indata.size ( ); ++ i ) indata [ i ] = lib::intToIndata ( b.intToTile ( i ) -> getContents ( ), player );

		double score = nn.run ( indata ) [ 0 ];

		if ( bestScore < score ) {

			bestTurn = possibleTurns [ i ];
			bestScore = score;

		}

	}

	bestTurn.rotate ( 6 - nRotations );

	return bestTurn;

}

agent_neural_statistical::agent_neural_statistical ( ): nn ( "ask" ) { }
agent_neural_statistical::agent_neural_statistical ( string str ): nn ( str ) { }
agent_neural_statistical::agent_neural_statistical ( istream & is ): nn ( is ) { }
agent_neural_statistical::agent_neural_statistical ( ifstream & ifs ): nn ( ifs ) { }
