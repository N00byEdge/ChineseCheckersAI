#ifndef GAME
#define GAME

#include <includes.h>
#include <include_agents.h>

#include <board.h>

/* Game class */
class game {

    public:

        board * getBoard();

        void startGame ( int numPlayers );

    protected:

    private:

        /* The main game board */
        board masterBoard;

        /* A vector containing all of the agents ( players or AI ) */
        vector < agent * > players;

        /* The number of agents in the game */
        int numPlayers = 2;

        /* Whose turn it is */
        int turn = 0;

};

#endif // GAME
