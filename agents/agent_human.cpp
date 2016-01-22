#include "agent_human.h"

	/* Turn member function */
	board_turn agent_human::doTurn ( board b, int player ) {

	board originalBoard = b;

	/*

		This will be called when the agents needs to make a move.

		You are provided with
			-the board b: This is the current board state.
			-the int player: This is the player number of this agent on the board b.

		All your tiles on the board will have the contents of the int player.

		for all your tiles t, t.getContents ( ) = player.

		You cannot add on more arguments for this function.

	*/

	int nRotations = b.rotateForPerspective ( player );

	board_turn trn;

	board_move mv;

	b.print ( );

	tile * chosenTile;

	vector < tile * > playerTiles = b.getPlayerTiles ( player );

	vector < board_move > madeMoves;

	int input;

	getTile:;

	cout << "Player #" << player << "s turn. Choose a tile:\n";
	for ( int i = 0; i < playerTiles.size ( ); ++ i )
		cout << i + 1 << ": " << playerTiles [ i ] -> getCoordinates ( ) << endl;

	cin >> input;

	if ( 1 <= input && input <= playerTiles.size ( ) ) {

		chosenTile = playerTiles [ input - 1 ];

	} else {

		cout << "Invalid output. Try again.\n";
		goto getTile;

	}

	vector < board_turn > possibleTurns = b.findAllPossibleTurns ( chosenTile, * new vector < board_move >, * new vector < bool > ( 121, false ) );

	if ( !possibleTurns.size ( ) ) {
		
		cout << "No moves for this tile.\n";
		goto getTile;
		
	}

	for ( int i = 0; i < possibleTurns.size ( ); ++ i ) {

		if ( !b.canMakeTurn ( possibleTurns [ i ] ) ) {

			possibleTurns.erase ( possibleTurns.begin ( ) + i );
			-- i;

		}

	}

	getTurn:;

	cout << "Reachable locations:\n";

	for ( int i = 0; i < possibleTurns.size ( ); ++ i )
		cout << i + 1 << ": " << b.getTurnCoords ( possibleTurns [ i ] ) << endl;

	cin >> input;

	if ( 1 <= input && input <= possibleTurns.size ( ) ) {

		trn = possibleTurns [ input - 1 ];

		if ( shouldWriteData ) {

			datasets.push_back ( { { }, { } } );

			for ( int i = 0; i < 121; ++ i ) {

				datasets [ datasets.size ( ) - 1 ].first.push_back  ( lib::intToIndata ( b.intToTile ( i ) -> getContents ( ), player ) );
				datasets [ datasets.size ( ) - 1 ].second.push_back ( 0.0L );

			}

			datasets [ datasets.size ( ) - 1 ].second [ b.tileToInt ( chosenTile ) ] = 1;
			datasets [ datasets.size ( ) - 1 ].second [ b.tileToInt ( b.getTile ( b.getTurnCoords ( trn ) ) ) ] = 1;

			ofstream datasetsStream;

			datasetsStream.open ( datafile );

			lib::printDatasets ( datasetsStream, datasets );

			datasetsStream.close ( );

		}

		trn.rotate ( 6 - nRotations );
		return trn;

	} else {

		cout << "Invalid output. Try again.\n";
		goto getTurn;

	}

}

agent_human::agent_human ( ) {

	string askWriteDataInput;

	cout << "Enter a path to write a data file for neural network learning (leave empty to skip): ";
	getline ( cin, askWriteDataInput );

	for ( size_t i = 0; i < askWriteDataInput.size ( ); ++ i ) askWriteDataInput [ i ] = tolower ( askWriteDataInput [ i ] );

	if ( askWriteDataInput.size ( ) ) {

		shouldWriteData = true;
		datafile = askWriteDataInput;

		ifstream datasetsfile;

		datasetsfile.open ( datafile );

		if ( datasetsfile.is_open ( ) ) datasets = lib::getDatasets ( datasetsfile );

		datasetsfile.close ( );

	}

}

agent_human::~agent_human ( ) {

	ofstream datasetsfile;

	datasetsfile.open ( datafile );

	if ( datasetsfile.is_open ( ) ) lib::printDatasets ( datasetsfile, datasets );

	datasetsfile.close ( );

}
