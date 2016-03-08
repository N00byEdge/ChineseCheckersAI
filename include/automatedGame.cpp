#include "automatedGame.h"

void automatedGame::startGame (  ) {

	vector < bool > hasWon ( players.size( ) + 1, false );
	turnsToWin.resize ( players.size( ) );
	for ( auto e: turnsToWin ) e = -1;

	int turn = 0;

	int firstWinner = - 1;
	vector < vector < string > > playerBoardStrings ( players.size ( ) );

	for ( int i = 0;  5; ++ i ) {

		if ( this -> numPlayers <= i ) { i = 0; ++ turn; }

		board_turn t;

		board printBoard = masterBoard;

		if ( masterBoard.hasFilledOpposingNest ( i + 1 ) ) goto skipturn;

		t = players [ i ] -> doTurn ( this -> masterBoard, i + 1 );

		if ( this -> masterBoard.canMakeTurn ( t ) ) {

			this -> masterBoard.makeTurn ( t );

		} else {
			cout << "Agent #" << i + 1 << " returned an invalid turn. Skipping turn.\n";

			cout << t.moves.size ( ) << " moves:\n";
			for ( size_t j = 0; j < t.moves.size ( ); ++ j )
				cout << t.moves [ j ].getTileStartCoords ( ) << ", " << t.moves [ j ].getRawData ( ) << endl;

			goto skipturn;

		}

		printBoard.rotateForPerspective ( i + 1 );
		playerBoardStrings [ i ].push_back ( printBoard.toString ( i + 1 ) );

		if ( this -> masterBoard.hasFilledOpposingNest ( i + 1 ) ) {
				hasWon [ i + 1 ] = true;
				if ( firstWinner == - 1 ) firstWinner = i;
				turnsToWin [ i ] = turn;
		}

		skipturn:;

		for ( int i = 0; i < numPlayers; ++ i ) {

			if ( not hasWon [ i + 1 ] ) goto stillplaying;

		}

		break;

		stillplaying:;
	}

	for ( size_t i = 0; i < playerBoardStrings.size ( ); ++ i ) {

        bool won = ( i == firstWinner );

        for ( size_t j = 0; j < playerBoardStrings [ i ].size ( ); ++ j ) {

            db.addToDB ( playerBoardStrings [ i ] [ j ], won );

        }

		if ( 10000 < turn ) break;

	}

}

void automatedGame::startGame ( vector < agent * > agents ) {

	players = agents;

	startGame ( );

}

board * automatedGame::getBoard ( ) {
	return & ( this -> masterBoard ) ;
}

automatedGame::automatedGame ( ): db ( * new database ) { }

automatedGame::automatedGame ( database & argDB ): db ( argDB ) { }
