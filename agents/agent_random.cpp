#include "agent_random.h"

board_turn agent_random::doTurn ( board b, int player ) {

	//cout << "Random agent turn. Board:\n";
	//b.print ( );
	//cout << endl;

	auto v = b.findAllPossibleTurns ( player );
	
	for ( int i = 0; i < v.size ( ); ++ i  ) {

		if ( !b.canMakeTurn ( v [ i ] ) ) {

			v.erase ( v.begin ( ) + i );
			-- i;

		}

	}

	//cout << "Random agent found " << v.size ( ) << " different moves. Choosing one randomly.\n";

	return v [ lib::randInt ( v.size ( ) ) ];

}
