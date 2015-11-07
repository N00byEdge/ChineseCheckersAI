#include "game.h"

/* Game constructor */
game::game ( int numPlayers ) {
    /* Calling the constructor also creates all members without initial values, like board. */

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

                this -> human_agents.push_back ( agent_human ( ) );
                this -> players.push_back ( & ( this -> human_agents [ this -> human_agents.size ( ) - 1 ] ) );
                failed = false;

            } else {

                cout << "Invalid agent number. Try again: ";
                cin >> agentNum;

            }

        }

    }

    for ( int i = 0;  5; ++ i ) {
        if ( i == numPlayers ) i = 0;
        human_agents [ i ] . doTurn ( this -> masterBoard, i + 1 );
    }

}

/* Game destructor */
game::~game() { }

board * game::getBoard ( ) {
    return & ( this -> masterBoard ) ;
}
