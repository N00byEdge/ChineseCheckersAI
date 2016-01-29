#include "agent_scoring.h"

vector < board_turn > findAllPossibleTurns ( board b, int player ) {

	vector < board_turn > allPossibleTurns;

	vector < tile * > playerTiles = b.getPlayerTiles ( player );

	for ( int i = 0; i < playerTiles.size ( ); ++ i ) {

		vector < bool > visited ( 121, false );

		auto v = b.findAllPossibleTurns( playerTiles [ i ], * new vector < board_move >, visited );

		for ( int j = 0; j < v.size ( ); ++ j )
			allPossibleTurns.push_back ( v [ j ] );

	}

	return allPossibleTurns;

}

board_turn agent_scoring::doTurn ( board b, int player ) {

	board originalBoard = b;

	//cout << "Player #" << player << "s turn, scoring agent.\n\tBoard:\n\n";
	//b.print ( );
	//cout << endl;

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

	for ( int i = 0; i < v.size ( ); ++ i  ) {

		if ( !b.canMakeTurn ( v [ i ] ) ) {

			v.erase ( v.begin ( ) + i );
			-- i;

		}

	}
	
	/* Are we feeling lucky? */
	int unlucky = lib::randInt ( 20 );
	if ( !unlucky ) {
		
		int randomMove = lib::randInt ( v.size ( ) );
		
		//cout << "I'm feeling lucky! Let's see what we get!\n";
		v [ randomMove ].rotate ( 6 - boardRotations );
		return v [ randomMove ];
		
	}

	vector < float > boardScores;
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



	for ( size_t i = 0; i < v.size ( ); ++ i  ) {

		v [ i ].rotate ( 6 - boardRotations );

		if ( !originalBoard.canMakeTurn ( v [ i ] ) ) {

			v.erase ( v.begin ( ) + i );
			boardScores.erase ( boardScores.begin ( ) + i );
			-- i;

		}

	}

	float bestScore = -5e35f;
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

	//cout << "We have " << bestTurns.size ( ) << " best turns, and " << v.size ( ) << " total turns.\n";

	t = bestTurns [ lib::randInt( bestTurns.size ( ) ) ];

	//if ( !originalBoard.canMakeTurn ( t ) ) cout << "This turn doesn't look valid any more.\n";

	return t;

}
