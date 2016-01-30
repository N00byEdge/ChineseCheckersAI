#pragma once

#include <includes.h>
#include <include_agents.h>

#include <board.h>
#include <database.h>

/* Game class */
class game {

	public:

		board * getBoard();

		game ( );
		game ( database & );

		void startGame ( int numPlayers );
		void startGame ( vector < agent * > agents );

        /* Database to save the data to */
		database & db;

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

