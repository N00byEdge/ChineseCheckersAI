#include "agent_random.h"

board_turn agent_random::doTurn ( board b, int player ) {

    cout << "Random agent turn. Board:\n";
    b.print ( );
    cout << endl;


    auto v = b.getPlayerTiles ( player );

    vector < board_turn > allPossibleTurns;

    for ( int i = 0; i < v.size ( ); ++ i ) {
        auto w = b.findAllPossibleTurns ( v [ i ], *new vector < board_move >, *new vector < pair < int, int > > );

        for ( int j = 0; j < w.size ( ); ++ j )
            allPossibleTurns.push_back ( w [ j ] );
    }

    cout << "Random agent found " << allPossibleTurns.size ( ) << " different moves. Choosing one randomly.\n";

	return allPossibleTurns [ lib::randInt ( allPossibleTurns.size ( ) ) ];

}
