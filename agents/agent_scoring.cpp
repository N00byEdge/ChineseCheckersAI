#include "agent_scoring.h"

int scoreBoard ( board b, int player ) {
    int score = 0;
    for ( int i = 0; i < b.getPlayerTiles ( player ).size ( ); ++ i )
        score += ( b.getPlayerTiles ( player ) [ i ] -> getCoordinates ( ).second );
    return score;
}

vector < board_turn > findAllPossibleTurns ( board b, int player ) {
	vector < board_turn > allPossibleTurns;
	vector < board_move > currentMoves;

	vector < tile * > playerTiles = b.getPlayerTiles ( player );

	for ( int i = 0; i < playerTiles.size ( ); ++ i ) {

        /*auto tileMoves = b.getPossibleMoves ( playerTiles [ i ] );

        for ( int j = 0; j <= tileMoves.size ( ); ++ j ) {

            if ( tileMoves [ j ].getRawData ( ) <= 6 ) {

                board_turn trn;
                trn.moves.push_back ( tileMoves [ j ] );
                allPossibleTurns.push_back ( trn );

            }

        }*/

		for ( int j = 1; j <= 12; ++ j ) {

			if ( b.canMove ( playerTiles [ i ], j ) ) {

                #ifdef DEBUGGING
                cout << "agentScoring canMove " << playerTiles [ i ] << " " << j << endl;
                #endif // DEBUGGING

				if ( j <= 6 ) {

                    board_turn trn;
                    board_move mv;
                    mv.setTileStartCoords( playerTiles [ i ] -> getCoordinates ( ) );
                    mv.setRawData ( j );
                    trn.moves.push_back ( mv );
                    allPossibleTurns.push_back ( trn );

				} else {

                    board_turn trn;
                    board_move mv;
                    mv.setTileStartCoords( playerTiles [ i ] -> getCoordinates ( ) );
                    mv.setRawData ( j );
                    trn.moves.push_back ( mv );
                    allPossibleTurns.push_back ( trn );

                    /*for ( int k = 1; k <= 6; ++ k ) {
                        if ( b.canJump ( playerTiles [ i ], k ) ) {

                        }
                    }*/

				}

			}

		}

	}

    return allPossibleTurns;

}

board_turn agent_scoring::doTurn ( board b, int player ) {

    board originalBoard = b;

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

    int bestScore = 0;
	vector < board_turn > bestTurns;

    for ( int i = 0; i < v.size ( ); ++ i ) {
        if ( bestScore < boardScores [ i ] ) {
            bestTurns.clear ( );
        }

        if ( bestScore <= boardScores [ i ] ) {
            bestTurns.push_back ( v [ i ] );
        }

    }

    t = v [ lib::randInt ( v.size ( ) ) ];

    t.rotate ( ( 6 - boardRotations ) % 6 );

	return t;

}
