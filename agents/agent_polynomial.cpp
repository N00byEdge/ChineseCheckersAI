#include "agent_polynomial.h"

#include <cmath>

double agent_polynomial::scoreBoard ( board & b, int player ) {

	double score = 0.0f;

	vector < tile * > playerTiles = b.getPlayerTiles ( player );

	for ( size_t i = 0; i < playerTiles.size ( ); ++ i ) {

		double y = playerTiles [ i ] -> getCoordinates ( ).second;
		double x = abs ( playerTiles [ i ] -> getCoordinates ( ).first - b.getMiddleXCoord ( y ) );

		/* [2/8/16, 5:19 PM]: */
		/* 5 st    15 doubles */
		//c(y+a)**e
		for ( unsigned i = 0; i < 5; ++ i )
			score += p [ i * 3 ] * pow (
										 y + p [ i * 3 + 1 ],
											 p [ i * 3 + 2 ] );

		/* 5 st    15 doubles */
		//c(x+a)**e
		for ( unsigned i = 0; i < 5; ++ i )
			score += p [ i * 3 + 15 ] * pow (
											  y + p [ i * 3 + 16 ],
												  p [ i * 3 + 17 ] );

		/* 3 st    15 doubles */
		//c(x+a)**e(y+b)**f
		for ( unsigned i = 0; i < 3; ++ i )
			score += p [ i * 5 + 30 ] * pow (
											  x + p [ i * 5 + 31 ],
												  p [ i * 5 + 32 ] )
									  * pow (
										  	  y + p [ i * 5 + 33 ],
												  p [ i * 5 + 33 ] );


	}

	return score;

}

double agent_polynomial::scoreTurn ( board_turn & t, board & b, int player ) {

	board dummyBoard = b;
	dummyBoard.makeTurn ( t );
	return scoreBoard ( dummyBoard, player );

}

const bool operator< ( const pair < double, board_turn > & l, const pair < double, board_turn > & r ) {

	return l.first < r.first;

}

board_turn agent_polynomial::doTurn ( board b, int player ) {

	board originalBoard = b;

	int boardRotations = b.rotateForPerspective( player );

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

	vector < pair < double, board_turn > > possibleTurns;
	auto turns = b.findAllPossibleTurns ( player );

	for ( size_t i = 0; i < turns.size ( ); ++ i ) if ( b.canMakeTurn ( turns [ i ] ) ) possibleTurns.push_back ( { 5.0f, turns [ i ] } );
	for ( size_t i = 0; i < possibleTurns.size ( ); ++ i ) possibleTurns [ i ].first = scoreTurn ( possibleTurns [ i ].second, b, player );

	sort ( possibleTurns.begin ( ), possibleTurns.end ( ) );

	possibleTurns [ 0 ].second.rotate ( 6 - boardRotations );

	return possibleTurns [ 0 ].second;

}

agent_polynomial::agent_polynomial ( ): p ( 45, 1.0f ) {



}

agent_polynomial::agent_polynomial ( vector < double > _p ): p( _p ) { }
