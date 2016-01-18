#pragma once

#include <includes.h>

using namespace std;

class board_move {

	public:

		bool didJump ( );
		bool didWalk ( );

		unsigned int getDirection ( );

		void setRawData ( unsigned int );
		int getRawData ( );

		void setTileStartCoords ( pair < int, int > );
		pair < int, int > getTileStartCoords ( );

		void rotate ( );

	protected:

	private:

		pair < int, int > tileStartCoords;

		unsigned int i = 0;
};

