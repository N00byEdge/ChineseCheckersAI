#include "game.h"

#include <fstream>

void game::startGame ( int numPlayers ) {

	if ( numPlayers == 2 || numPlayers == 4 || numPlayers == 6 ) {

		this -> numPlayers = numPlayers;

	} else

		this -> numPlayers = 2;

	/* Reset the board with the number of players for the game. */
	this -> masterBoard.resetBoard ( this -> numPlayers );

	if ( numPlayers <= players.size ( ) ) goto skipagents;

	cout << "Available agents:\n"
		<< "\t1: Human interface agent\n"
		<< "\t2: Scoring agent\n"
		<< "\t3: Randomizing agent\n"
		<< "\t4: Neural agent\n"
		<< "\t5: Statistical agent\n"
		<< "\t6: Polynomial agent\n";

	while ( players.size ( ) < this -> numPlayers ) {

		cout << "Enter the agent number for agent #" << players.size ( ) + 1 << ": ";

		agentinput:

		int agentNum;
		cin >> agentNum;

		cin.ignore ( );

		switch ( agentNum ) {

			case 1:
				this -> players.push_back ( new agent_human );
				break;

			case 2:
				this -> players.push_back ( new agent_scoring );
				break;

			case 3:
				this -> players.push_back ( new agent_random );
				break;

			case 4:
				this -> players.push_back ( new agent_neural );
				break;

            case 5:
                this -> players.push_back ( new agent_statistical );
                break;
			
			case 6:
				this -> players.push_back ( new agent_polynomial );
				break;

			default:
				cout << "Invalid agent number. Try again: ";
				goto agentinput;

		}

	}

	skipagents:;

	std::ofstream gamedata;
	gamedata.open ( "gamedata.txt" );
	gamedata << numPlayers << endl;

	vector < bool > hasWon ( numPlayers + 1, false );

	int turn = 0;

	int firstWinner = - 1;
	vector < vector < string > > playerBoardStrings ( players.size ( ) );

	for ( int i = 0;  5; ++ i ) {

		if ( this -> numPlayers <= i ) { i = 0; ++ turn; }

		board_turn t;

		board printBoard = masterBoard;

		if ( masterBoard.hasFilledOpposingNest ( i + 1 ) ) goto skipturn;

		for ( size_t j = 0; j < players.size ( ); ++ j ) {
			auto playerTiles = masterBoard.getPlayerTiles ( j + 1 );
			gamedata << j << " ";
			for ( size_t k = 0; k < playerTiles.size ( ); ++ k )
				gamedata << masterBoard.tileToInt ( playerTiles [ k ] ) << " ";
			gamedata << "\n";
		}

		t = players [ i ] -> doTurn ( this -> masterBoard, i + 1 );

		if ( this -> masterBoard.canMakeTurn ( t ) ) {

			this -> masterBoard.makeTurn ( t );

		} else {
			cout << "Agent #" << i + 1 << " returned an invalid turn. Skipping turn.\n";

			cout << t.moves.size ( ) << " moves:\n";
			for ( size_t j = 0; j < t.moves.size ( ); ++ j )
				cout << t.moves [ j ].getTileStartCoords ( ) << ", " << t.moves [ j ].getRawData ( ) << endl;

			cout << "Press enter to continue... ";
			cin.ignore ( );

			goto skipturn;

		}

		printBoard.rotateForPerspective ( i + 1 );
		playerBoardStrings [ i ].push_back ( printBoard.toString ( i + 1 ) );

		if ( this -> masterBoard.hasFilledOpposingNest ( i + 1 ) ) {
				hasWon [ i + 1 ] = true;
				gamedata << "WIN " << turn << " " << i << endl;
				if ( firstWinner == - 1 ) firstWinner = i;
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

	}

}

void game::startGame ( vector < agent * > agents ) {

	players = agents;

	startGame ( ( int ) agents.size ( ) );

}

board * game::getBoard ( ) {
	return & ( this -> masterBoard ) ;
}

game::game ( ): db ( * new database ) { }

game::game ( database & argDB ): db ( argDB ) { }
