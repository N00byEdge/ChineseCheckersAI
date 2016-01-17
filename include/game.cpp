#include "game.h"

#include <fstream>

void game::startGame ( int numPlayers ) {

    if ( numPlayers == 2 || numPlayers == 4 || numPlayers == 6 ) {

        this -> numPlayers = numPlayers;

    } else

        this -> numPlayers = 2;

    /* Reset the board with the number of players for the game. */
	this -> masterBoard.resetBoard ( this -> numPlayers );

	cout << "Available agents:\n"
		<< "\t1: Human interface agent\n"
		<< "\t2: Scoring agent\n"
		<< "\t3: Randomizing agent\n"
		<< "\t4: Neural agent\n";

	while ( players.size ( ) < this -> numPlayers ) {

		cout << "Enter the agent number for agent #" << players.size ( ) + 1 << ": ";

		agentinput:

		int agentNum;
		cin >> agentNum;

        switch ( agentNum ) {

            case 1:
                this -> players.push_back ( new agent_human );

            case 2:
                this -> players.push_back ( new agent_scoring );

            case 3:
                this -> players.push_back ( new agent_random );

            case 4:
                this -> players.push_back ( new agent_neural );

            default:
                cout << "Invalid agent number. Try again: ";
                goto agentinput;

        }

	}

	std::ofstream gamedata;
	gamedata.open ( "gamedata.txt" );
	gamedata << numPlayers << endl;

	vector < bool > hasWon ( numPlayers, false );

	int turn = 0;

	for ( int i = 0;  5; ++ i ) {

		//cout << hasWon << endl;

		//cout << deb ( masterBoard.hasFilledOpposingNest ( 0 ) ) << ", " << deb ( masterBoard.hasFilledOpposingNest ( 1 ) );

		if ( this -> numPlayers <= i ) { i = 0; ++ turn; }

		board_turn t;

		if ( masterBoard.hasFilledOpposingNest ( i ) ) goto skipturn;

		t = players [ i ] -> doTurn ( this -> masterBoard, i + 1 );

		if ( this -> masterBoard.canMakeTurn ( t ) ) {

			this -> masterBoard.makeTurn ( t );

		} else {
			cout << "Agent #" << i + 1 << " returned an invalid turn. Skipping turn.\n";
		}

		gamedata << i << " " << turn << " " << masterBoard.tileToInt( masterBoard.getTile ( t.moves [ 0 ].getTileStartCoords ( ) ) ) << " " << masterBoard.tileToInt ( masterBoard.getTile ( masterBoard.getTurnCoords ( t ) ) )<< endl;

		if ( this -> masterBoard.hasFilledOpposingNest ( i ) ) {
                hasWon [ i ] = true;
                gamedata << "WIN " << turn << " " << i << endl;
        }

		skipturn:;

        for ( int i = 0; i < numPlayers; ++ i ) {

            if ( not hasWon [ i ] ) goto stillplaying;

		}

		break;

		stillplaying:;
	}

	gamedata.close ( );
}

board * game::getBoard ( ) {
	return & ( this -> masterBoard ) ;
}
