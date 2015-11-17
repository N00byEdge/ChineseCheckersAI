#include "agent_scoring.h"

float scoreBoard ( board b, int player ) {
	float score = 0;

	for ( int i = 0; i < b.getPlayerTiles ( player ).size ( ); ++ i ) {

		tile * t = b.getPlayerTiles ( player ) [ i ];
		int x = t -> getCoordinates ( ).first;
		int y = t -> getCoordinates ( ).second;

		int h = 17 - y;
		float d = abs ( ( float ) x - b.getMiddleXCoord ( y ) );

		score -= h * h;
		score -= d * d;

	}

	return score;
}

vector < board_turn > findAllPossibleTurns ( board b, tile * t, vector < board_move > moves, vector < pair < int, int > > visitedCoords ) {

    vector < board_turn > allPossibleTurns;

	auto possibleMoves = b.getPossibleMoves ( t );

	for ( int i = 0; i < possibleMoves.size ( ); ++ i ) {

		if ( 1 < moves.size ( ) && possibleMoves [ i ].getRawData ( ) <= 6 )
			goto nomove;

		if ( b.canMove ( possibleMoves [ i ] ) ) {

			for ( int j = 0; j < visitedCoords.size ( ); ++ j ) {

				if ( b.getMoveCoords ( possibleMoves [ i ] ) == visitedCoords [ j ] )
					goto nomove;

			}

			board_turn trn;
			trn.moves = moves;
			allPossibleTurns.push_back ( trn );

			board_move mv;
			mv = possibleMoves [ i ];
			moves.push_back ( mv );
			visitedCoords.push_back ( b.getMoveCoords ( possibleMoves [ i ] ) );
			tile * originalTile = t;
			t = b.getTile ( b.getMoveCoords ( mv ) );
			board originalBoard = b;
			b.move ( mv );
			auto w = findAllPossibleTurns ( b, t, moves, visitedCoords );
			b = originalBoard;
			t = originalTile;

			for ( int k = 0; k < w.size ( ); ++ k )
                allPossibleTurns.push_back ( w [ k ] );

			moves.erase ( moves.end ( ) - 1 );
			visitedCoords.erase ( visitedCoords.end ( ) - 1 );

		}

		nomove:
		if ( 5 ) { }

	}

	return allPossibleTurns;

}

vector < board_turn > findAllPossibleTurns ( board b, int player ) {

	vector < board_turn > allPossibleTurns;

	vector < tile * > playerTiles = b.getPlayerTiles ( player );

	for ( int i = 0; i < playerTiles.size ( ); ++ i ) {

		vector < board_move > emptyMoveVector;
		vector < pair < int, int > > emptyPiiVector;
		vector < board_turn > emptyTurnVector;

		auto v = findAllPossibleTurns( b, playerTiles [ i ], emptyMoveVector, emptyPiiVector );

		for ( int j = 0; j < v.size ( ); ++ j )
			allPossibleTurns.push_back ( v [ j ] );

	}

	return allPossibleTurns;

}

board_turn agent_scoring::doTurn ( board b, int player ) {

	board originalBoard = b;

	int boardRotations = b.rotateForPerspective( player );

	cout << "Player #" << player << "s turn, scoring agent.\n\tBoard:\n\n";
	b.print ( );
	cout << endl;

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
		boardScores.push_back ( scoreBoard ( b2, player ));
	}

	#ifdef DEBUGGING
	cout << "All possible turns:\n";
	for ( int i = 0; i < v.size ( ); ++ i ) {
		cout << i << ": [" << v [ i ].moves [ 0 ].getTileStartCoords ( ).first << ", " << v [ i ].moves [ 0 ].getTileStartCoords ( ).second << "]: ";
		for ( int j = 0; j < v [ i ].moves.size ( ); ++ j ) {
			cout << v [ i ].moves [ j ].getRawData ( );
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

	#ifdef DEBUGGING
	cout << "We have " << bestTurns.size ( ) << " best turns, and " << v.size ( ) << " total turns.\n";
	#endif // DEBUGGING

	t = bestTurns [ lib::randInt( bestTurns.size ( ) ) ];

	t.rotate ( 6 - boardRotations );

	return t;

}
