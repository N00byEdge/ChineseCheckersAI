#include "board_move.h"

bool board_move::didJump ( ) {
    return !( 1 <= this -> i && this -> i <= 6 );
}

bool board_move::didWalk ( ) {
    return !( 7 <= this -> i && this -> i <= 12 );
}

unsigned int board_move::getDirection ( ) {
    if ( 1 <= this -> i && this -> i <= 12 ) return ( ( this -> i - 1 ) % 6 ) + 1;
    return 0;
}

void board_move::setRawData ( int i ) {
    this -> i = i;
}

int board_move::getRawData ( ) {
    return this -> i;
}

void board_move::setTileStartCoords ( pair < int, int > pii ) {
	this -> tileStartCoords = pii;
}

pair < int, int > board_move::getTileStartCoords ( ) {
	return this -> tileStartCoords;
}

void board_move::rotate ( ) {

	auto rotationMap = lib::getCoordTranslationTable ( );

	this -> tileStartCoords = rotationMap [ this -> tileStartCoords ];
	if ( this -> i % 6 == 5 )
		i -= 5;
	else
		++ i;

}
