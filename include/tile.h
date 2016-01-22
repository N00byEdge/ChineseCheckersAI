#pragma once

#include <includes.h>

using namespace std;

/* Tile class */
class tile {

	friend class board;

	public:

		/* Constructor */
		tile ( int, int, int );

		/* Get the x coordinate of a tile */
		int getX ( );

		/* Get the y coordinate of a tile */
		int getY ( );

		/*
		 * Get the contents of a tile:
		 *
		 * -1 = impassable
		 * 0 = empty
		 * 1 ≤ n ≤ 6 = piece that belongs to player n
		 */
		int getContents ( );

		pair < int, int > getCoordinates ( );

	protected:

		/* Set the coordinates for the tile */
		void updateCoordinates ( int x, int y );

		/* Set the contents for the tile */
		void setContents ( int i );

	private:

		/* The coordinates of a given tile, for reference only */
		int x = - 1, y = - 1;

		/* The content of the tile is stored in this int */
		int c = - 1;

};
