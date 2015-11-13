#include "agent_human.h"

	/* Turn member function */
board_turn agent_human::doTurn ( board b, int player ) {

	board originalBoard = b;

	#ifdef DEBUGGING
	cout << "agent_human: doTurn called.\n";
	#endif // DEBUGGING

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

	#ifdef DEBUGGING
	cout << "Turn constructed.\n";
	#endif // DEBUGGING

	board_move m;

	#ifdef DEBUGGING
	cout << "Move constructed.\n";
	#endif // DEBUGGING

	pair < int, int > coords;

	#ifdef DEBUGGING
	cout << "Coordinates constructed.\n";
	#endif // DEBUGGING

	coords.first = -1;
	coords.second = -1;

	#ifdef DEBUGGING
	cout << "Set initial coordinates.\n";
	#endif // DEBUGGING

	int boardRotations = b.rotateForPerspective ( player );

	#ifdef DEBUGGING
	cout << "Rotated board " << boardRotations << " steps.\n";
	#endif // DEBUGGING

	b.print ( );

	#ifdef DEBUGGING
	cout << "Printed board.\n";
	#endif // DEBUGGING

	vector < tile * > playerTiles = b.getPlayerTiles ( player );

	cout << "Your tiles: ";
	for ( int i = 0; i < playerTiles.size ( ); ++ i )
		cout << "[" << playerTiles [ i ] -> getCoordinates ( ).first  << ", " << playerTiles [ i ] -> getCoordinates ( ).second << "] ";
	cout << endl;

	cout << "Player #" << player << "s turn. Choose a tile:\n";

	choosetile:

	cout << "x = ";
	cin >> coords.first;
	cout << "y = ";
	cin >> coords.second;

	if ( !b.isValidTile ( coords ) ) {

		cout << "Invalid tile.\n";
		goto choosetile;

	} else if ( b.getTile ( coords ) -> getContents ( ) != player ) {

		cout << "That is not your tile.\n";
		goto choosetile;

	} else {

		vector < board_move > v = b.getPossibleMoves ( b.getTile ( coords ) );

		cout << "Possible moves for ["
			<< coords.first
			<< ", "
			<< coords.second
			<< "]: ";

		for ( int i = 0; i < v.size ( ); ++ i )
			cout << v [ i ].getRawData ( ) << " ";

		cout << endl;

		if ( !v.size ( ) ) {

			cout << "No possible moves. Please choose another tile.\n";

			goto choosetile;

		} else {

			cout << "Make a move: ";

			string in;

			cin >> in;

			if ( in == "resetturn" ) {

				goto choosetile;

			} else {

				m.setRawData( atoi ( in.c_str ( ) ) );

			}
		}
	}

	m.setTileStartCoords ( coords );
	board dummyBoard = b;

	vector < pair < int, int > > visitedCoordinates;
	visitedCoordinates.push_back ( coords );

	if ( dummyBoard.canMove ( m ) ) {

		pair < int, int > moveFinishCoords = dummyBoard.getMoveCoords ( m );
		tile * moveFinishTile = dummyBoard.getTile ( moveFinishCoords );

		if ( !dummyBoard.move ( m ) ) {

			vector < int > possibleJumps;

			for ( int i = 1; i <= 6; ++ i ) {
				if ( m.getRawData ( ) != 1 && i != 4 && dummyBoard.canJump ( moveFinishTile, i ) )
					possibleJumps.push_back ( i );

				if ( m.getRawData ( ) != 2 && i != 5 && dummyBoard.canJump ( moveFinishTile, i ) )
					possibleJumps.push_back ( i );

				if ( m.getRawData ( ) != 3 && i != 6 && dummyBoard.canJump ( moveFinishTile, i ) )
					possibleJumps.push_back ( i );

				if ( m.getRawData ( ) != 4 && i != 1 && dummyBoard.canJump ( moveFinishTile, i ) )
					possibleJumps.push_back ( i );

				if ( m.getRawData ( ) != 5 && i != 2 && dummyBoard.canJump ( moveFinishTile, i ) )
					possibleJumps.push_back ( i );

				if ( m.getRawData ( ) != 6 && i != 3 && dummyBoard.canJump ( moveFinishTile, i ) )
					possibleJumps.push_back ( i );
			}

			if ( possibleJumps.size ( ) ) {
				cout << "You can jump again. Possible jump directions: ";
				for ( int i = 0; i < possibleJumps.size ( ); ++ i )
					cout << possibleJumps [ i ] << " ";
				cout << endl;
			}
		}

	}



	board_turn rotatedTurn = t;
	rotatedTurn.rotate ( ( 6 - boardRotations ) % 6 );

	if ( !originalBoard.canMakeTurn ( rotatedTurn ) ) {

		cout << "That is not a valid move.\n";
		goto choosetile;

	} else {

	    t.moves.push_back ( m );

        if ( 7 <= m.getRawData ( ) && m.getRawData ( ) <= 12 ) {

        }

	}

	t.rotate ( ( 6 - boardRotations ) % 6 );

	return t;

}
