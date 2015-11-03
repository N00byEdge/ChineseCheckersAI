#include "agent_human.h"

    /* Turn member function */
board_turn agent_human::doTurn ( board b, int player ) {

    #ifdef DEBUGGING
	cout << "doTurn called.\n";
	#endif // DEBUGGING

	/*

		This will be called when the agents needs to make a move.

		You are provided with
			-the board b: This is the current board state.
			-the int player: This is the player number of this agent on the board b.

		All your tiles on the board will have the contents of the int player.

		for all your tiles t, t.getContents ( ) = player.

		You cannot add on more arguments for this function.

	*/

	board_turn t;

	#ifdef DEBUGGING
	cout << "Turn constructed.\n";
	#endif // DEBUGGING

	board_move m;

	#ifdef DEBUGGING
	cout << "Move constructed.\n";
	#endif // DEBUGGING

	pair < int, int > coords;

	#ifdef DEBUGGING
	cout << "Coordinates constructed.\n";
	#endif // DEBUGGING

	coords.first = -1;
	coords.second = -1;

	#ifdef DEBUGGING
	cout << "Set initial coordinates.\n";
	#endif // DEBUGGING

	b.print ( );

	#ifdef DEBUGGING
	cout << "Printed board.\n";
	#endif // DEBUGGING

	cout << "Player #" << player << "s turn. Choose a tile:\n";

	while ( !b.isValidTile( coords ) || b.getTile ( coords ) -> getContents ( ) != player ) {

		cout << "x = ";
		cin >> coords.first;
		cout << "y = ";
		cin >> coords.second;

		if ( !b.isValidTile ( coords) ) {
			cout << "Invalid tile.\n";
		} else if ( b.getTile ( coords ) -> getContents ( ) != player ) {
			cout << "That is not your tile.\n";
		}

	}

	cout << "Possible moves for ["
        << coords.first
        << ", "
        << coords.second
        << "]: ";

	vector < board_move > v = b.getPossibleMoves ( b.getTile ( coords ) );

	for ( int i = 0; i < v.size ( ); ++ i ) {
        cout << v [ i ].getRawData ( ) << " ";
	}

	m.setTileStartCoords ( coords );

	cout << "Make a move: ";
	int moveData;
	cin >> moveData;

	m.setRawData ( moveData );

	t.moves.push_back ( m );

	return t;

}
