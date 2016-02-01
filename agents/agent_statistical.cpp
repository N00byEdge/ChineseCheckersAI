#include "agent_statistical.h"

board_turn agent_statistical::doTurn ( board b, int player ) {

	/*

		This will be called when the agents needs to make a move.

		You are provided with
			-the board b: This is the current board state.
			-the int player: This is the player number of this agent on the board b.

		All your tiles on the board will have the contents of the int player.

		for all your tiles t, t.getContents ( ) = player.

		You cannot add on more arguments for this function.

	*/

    auto allPossibleTurns = b.findAllPossibleTurns ( player );

    string currentBoardState = b.toString ( player );
    for ( size_t i = 0; i < allPossibleTurns.size ( ); ++ i ) if ( !b.canMakeTurn ( allPossibleTurns [ i ] ) ) allPossibleTurns.erase ( allPossibleTurns.begin ( ) + i -- );

    size_t bestTurn;
    double bestTurnWinChance = -1.0l;

    for ( size_t i = 0; i < allPossibleTurns.size ( ); ++ i ) {

        board dummyBoard = b;

        dummyBoard.makeTurn ( allPossibleTurns [ i ] );

        dummyBoard.rotateForPerspective ( player );

        double chanceToWin = extDB.chanceToWin ( dummyBoard.toString ( player ) );

        if ( bestTurnWinChance < chanceToWin ) {

            bestTurn = i;
            bestTurnWinChance = chanceToWin;

        }

    }

    cout << bestTurnWinChance << endl;

    return allPossibleTurns [ bestTurn ];

}

agent_statistical::agent_statistical ( ): localDB ( * new database ), extDB ( localDB ) {

    string dbpath;

    dblocinput:;

    cout << "This statistical agent has no linked database. Please enter a path for a database to load: ";
    getline ( cin, dbpath );

    ifstream dbin;
    dbin.open ( dbpath );

    if ( dbin.is_open ( ) ) dbin >> localDB;

    else {

        cout << "Database load failed. Please try again.\n";
        goto dblocinput;

    }

    extDB = localDB;

}

agent_statistical::agent_statistical ( database db ): extDB ( db ) { }

agent_statistical::~agent_statistical ( ) { }
