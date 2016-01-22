#include "tile.h"

/* Tile Constructor*/
tile::tile ( int x, int y, int c ) {

	/* Sets the coordinates of a given tile, for reference only. */
	this -> x = x;
	this -> y = y;

	/* Set the initial contents of the tile. These may change during the game, unlike the coordinates. */
	this -> c = c;

	#ifdef DEBUGGING
	cout << "Set x coordinate: " << this -> x << endl;
	cout << "Set y coordinate: " << this -> y << endl;
	cout << "Set contents: " << this -> c << endl;
	#endif

}

/* Get the coordinates of a given tile */
int tile::getX ( ) {
	if ( this == nullptr )
		return -1;

	return this -> x;

}

int tile::getY ( ) {
	if ( this == nullptr )
		return -1;

	return this -> y;

}

/* Get the contents of a tile */
int tile::getContents ( ) {
	if ( this == nullptr )
		return -1;

	return this -> c;

}

/* Set the contents of a given tile */
void tile::setContents ( int i ) {

	this -> c = i;

}

void tile::updateCoordinates ( int x, int y ) {

	this -> x = x;
	this -> y = y;

}

pair < int, int > tile::getCoordinates ( ) {

	pair < int, int > p;


	if ( this == nullptr ) {

		p.first = -1;
		p.second = -1;

		return p;

	}

	p.first = this -> x;
	p.second = this -> y;

	return p;

}
