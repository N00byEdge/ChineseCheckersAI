#pragma once

#include <includes.h>
#include <include_agents.h>

#include <board.h>
#include <database.h>

/* AutomatedGame class */
class automatedGame {

	public:

		board * getBoard();

		automatedGame ( );
		automatedGame ( database & );

		void startGame ( );
		void startGame ( vector < agent * > agents );

        /* Database to save the data to */
		database & db;

		/* A vector containing all of the agents ( players or AI ) */
		vector < agent * > players;

		vector < int > turnsToWin;

	protected:

	private:

		/* The main game board */
		board masterBoard;

		/* The number of agents in the game */
		int numPlayers = 2;

		/* Whose turn it is */
		int turn = 0;

};

