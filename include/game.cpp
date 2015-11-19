#include "game.h"

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
		<< "\t3: Randomizing agent\n";

	while ( players.size ( ) < this -> numPlayers ) {

		cout << "Enter the agent number for agent #" << players.size ( ) + 1 << ": ";

		agentinput:

		int agentNum;
		cin >> agentNum;


		if ( agentNum == 1 ) {

			this -> players.push_back ( new agent_human );

		} else if ( agentNum == 2 ) {

			this -> players.push_back ( new agent_scoring );

		} else if ( agentNum == 3 ) {

		    this -> players.push_back ( new agent_random );

		} else {

			cout << "Invalid agent number. Try again: ";
			goto agentinput;

		}

	}

	for ( int i = 0;  5; ++ i ) {

		if ( i == this -> numPlayers ) i = 0;
		board_turn t = players [ i ] -> doTurn ( this -> masterBoard, i + 1 );

		if ( this -> masterBoard.canMakeTurn ( t ) ) {

			this -> masterBoard.makeTurn ( t );

		} else {
			cout << "Agent #" << i + 1 << " returned an invalid turn. Skipping turn.\n";
		}
	}
}

board * game::getBoard ( ) {
	return & ( this -> masterBoard ) ;
}
