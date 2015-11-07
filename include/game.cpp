#include "game.h"

void game::startGame ( int numPlayers ) {

    /* Sets the number of players in the game */
    this -> numPlayers = numPlayers;

    /* Reset the board with the number of players for the game. */
    this -> masterBoard.resetBoard( this -> numPlayers );

    cout << "Available agents:\n"
        << "\t1: Human interface agent\n";

    while ( players.size ( ) < numPlayers ) {

        cout << "Enter the agent number for agent #" << players.size ( ) + 1 << ": ";

        int agentNum;
        cin >> agentNum;

        bool failed = true;

        while ( failed ) {

            if ( agentNum == 1 ) {

                this -> players.push_back ( new agent_human ( ) );
                failed = false;

            } else {

                cout << "Invalid agent number. Try again: ";
                cin >> agentNum;

            }

        }

    }

    for ( int i = 0;  5; ++ i ) {
        if ( i == numPlayers ) i = 0;
        players [ i ] -> doTurn ( this -> masterBoard, i + 1 );
    }
}

board * game::getBoard ( ) {
    return & ( this -> masterBoard ) ;
}
