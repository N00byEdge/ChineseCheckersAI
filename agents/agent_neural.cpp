#include "agent_neural.h"

long double intToIndata ( int i, int player ) {

    switch ( i ) {

        case 0:
            return 0.0L;

        default:

            if ( i == player ) return 2.0L;
            return 1.0L;

    }

}

board_turn agent_neural::doTurn ( board b, int player ) {

	/*

		This will be called when the agents needs to make a move.

		You are provided with
			-the board b: This is the current board state.
			-the int player: This is the player number of this agent on the board b.

		All your tiles on the board will have the contents of the int player.

		for all your tiles t, t.getContents ( ) = player.

		You cannot add on more arguments for this function.

	*/

	cout << "Player #" << player << "s turn, neural agent.\n";

	auto originalBoard = b;
	int nRotations = b.rotateForPerspective ( player );

	board_turn t;

	vector < long double > indata ( 121, 0 );
	for ( size_t i = 0; i < indata.size ( ); ++ i ) indata [ i ] = intToIndata ( b.intToTile ( i ) -> getContents ( ), player );

    auto outdata = nn.run ( indata );

    vector < pair < long double, int > > sortedOutdata;

    for ( size_t i = 0; i < outdata.size ( ); ++ i )
        sortedOutdata.push_back ( { outdata [ i ], i } );

    sort ( sortedOutdata.begin ( ), sortedOutdata.end ( ), std::greater < pair < long double, int > > ( ) );

	board_turn bestTurn;
	long double bestScore = 0;

	for ( size_t i = 0; i < sortedOutdata.size ( ); ++ i ) {

		if ( b.intToTile ( sortedOutdata [ i ].second ) -> getContents ( ) != player ) continue;

		vector < board_turn > possibleTurns = b.findAllPossibleTurns ( b.intToTile ( sortedOutdata [ i ].second ), * new vector < board_move >, * new vector < bool > ( 121, false ) );

		for ( size_t j = 0; j < sortedOutdata.size ( ); ++ j ) {

            if ( b.intToTile ( sortedOutdata [ j ].second ) -> getContents ( ) != 0 ) continue;

			for ( size_t k = 0; k < possibleTurns.size ( ); ++ k ) {

				if ( b.tileToInt ( b.getTile ( b.getTurnCoords ( possibleTurns [ k ] ) ) ) == j && bestScore < sortedOutdata [ i ].first + sortedOutdata [ j ].first ) {

                    bestTurn = possibleTurns [ k ];
                    bestScore = sortedOutdata [ i ].first + sortedOutdata [ j ].first;

				}

			}

		}

	}

    bestTurn.rotate ( 6 - nRotations );

	return bestTurn;

}

agent_neural::agent_neural ( ): nn ( "ask" ) { }
agent_neural::agent_neural ( string str ): nn ( str ) { }
agent_neural::agent_neural ( istream & is ): nn ( is ) { }
agent_neural::agent_neural ( ifstream & ifs ): nn ( ifs ) { }
