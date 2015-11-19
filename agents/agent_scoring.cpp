#include "agent_scoring.h"

vector < board_turn > findAllPossibleTurns ( board b, int player ) {

	vector < board_turn > allPossibleTurns;

	vector < tile * > playerTiles = b.getPlayerTiles ( player );

	for ( int i = 0; i < playerTiles.size ( ); ++ i ) {

		vector < board_move > emptyMoveVector;
		vector < pair < int, int > > emptyPiiVector;
		vector < board_turn > emptyTurnVector;

		auto v = b.findAllPossibleTurns( playerTiles [ i ], emptyMoveVector, emptyPiiVector );

		for ( int j = 0; j < v.size ( ); ++ j )
			allPossibleTurns.push_back ( v [ j ] );

	}

	return allPossibleTurns;

}

board_turn agent_scoring::doTurn ( board b, int player ) {

	board originalBoard = b;

	cout << "Player #" << player << "s turn, scoring agent.\n\tBoard:\n\n";
	b.print ( );
	cout << endl;

	int boardRotations = b.rotateForPerspective( player );

	/*

		This will be called when the agents needs to make a move.

		You are provided with
			-the board b: This is the current board state.
			-the int player: This is the player number of this agent on the board b.

		All your tiles on the board will have the contents of the int player.

		for all your tiles t, t.getContents ( ) = player.

		You cannot add on more arguments for this function.

	*/

	#ifdef DEBUGGING
	cout << "agent_scoring: doTurn called.\n";
	#endif // DEBUGGING

	board_turn t;

	vector < board_turn > v = findAllPossibleTurns ( b, player );

	vector < int > boardScores;
	for ( int i = 0; i < v.size ( ); ++ i ) {
		board b2 = b;
		b2.makeTurn ( v [ i ] );
		boardScores.push_back ( b2.score ( player ) );
	}

	#ifdef DEBUGGING
	cout << "All possible turns:\n";
	for ( int i = 0; i < v.size ( ); ++ i ) {
		cout << i << ": [" << v [ i ].moves [ 0 ].getTileStartCoords ( ).first << ", " << v [ i ].moves [ 0 ].getTileStartCoords ( ).second << "]: ";
		for ( int j = 0; j < v [ i ].moves.size ( ); ++ j ) {
			cout << v [ i ].moves [ j ].getRawData ( ) << " ";
		}
		cout << ", score: " << boardScores [ i ] << endl;
	}
	#endif // DEBUGGING

	int bestScore = std::numeric_limits < int >::min ( );
	vector < board_turn > bestTurns;

	for ( int i = 0; i < v.size ( ); ++ i ) {
		if ( bestScore < boardScores [ i ] ) {
			bestTurns.clear ( );
		}

		if ( bestScore <= boardScores [ i ] ) {
			bestTurns.push_back ( v [ i ] );
			bestScore = boardScores [ i ];
		}

	}

	cout << "We have " << bestTurns.size ( ) << " best turns, and " << v.size ( ) << " total turns.\n";

	t = bestTurns [ lib::randInt( bestTurns.size ( ) ) ];

	t.rotate ( 6 - boardRotations );

	return t;

}
