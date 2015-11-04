#include "board_turn.h"

void board_turn::rotate ( ) {

	for ( int i = 0; i < this -> moves.size ( ); ++ i )
		this -> moves.rotate ( );

}

void board_turn::rotate ( int steps ) {

	for ( int i = 0; i < steps % 6; ++ i )
		this -> rotate ( );

}