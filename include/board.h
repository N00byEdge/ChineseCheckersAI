#ifndef BOARD
#define BOARD

#include <includes.h>

#include <board_turn.h>
#include <tile.h>

/* Board class */
class board {

	public:

		/* Constructor */
		board ( );

		/* Destructor */
		~board ( );

		void print ( );
		void printWithCoords ( );

		/*
			Reset the board to a empty board. A good idea after creating a board object, but not required as you may have a template. If you are not copying a board, always reset it.
			Set numPlayers first, as the new board state depends on the number of players.
		*/
		void resetBoard ( int );

		bool makeTurn ( board_turn );
		bool canMakeTurn ( board_turn );

		vector < board_move > getPossibleMoves ( );
		vector < board_move > getPossibleMoves ( tile * tile );

		tile * getTile ( pair < int, int > coordinates );

		bool isValidTile ( pair < int, int > coordinates );
		bool isValidTile ( tile * tile );

		pair < int, int > getCoordRight ( pair < int, int> coordinates );
		pair < int, int > getCoordRight ( tile * tile );
		pair < int, int > getCoordJumpRight ( tile * tile );
		tile * getTileRight ( pair < int, int> coordinates );
		tile * getTileRight ( tile * tile );
		bool canWalkRight ( pair < int, int> coordinates );
		bool canWalkRight ( tile * tile );
		bool canJumpRight ( pair < int, int> coordinates );
		bool canJumpRight ( tile * tile );
		bool walkRight ( tile * tile );
		bool jumpRight ( tile * tile );

		pair < int, int > getCoordUpRight ( pair < int, int> coordinates );
		pair < int, int > getCoordUpRight ( tile * tile );
		pair < int, int > getCoordJumpUpRight ( tile * tile );
		tile * getTileUpRight ( pair < int, int> coordinates );
		tile * getTileUpRight ( tile * tile );
		bool canWalkUpRight ( pair < int, int> coordinates );
		bool canWalkUpRight ( tile * tile );
		bool canJumpUpRight ( pair < int, int> coordinates );
		bool canJumpUpRight ( tile * tile );
		bool walkUpRight ( tile * tile );
		bool jumpUpRight ( tile * tile );

		pair < int, int > getCoordDownRight ( pair < int, int> coordinates );
		pair < int, int > getCoordDownRight ( tile * tile );
		pair < int, int > getCoordJumpDownRight ( tile * tile );
		tile * getTileDownRight ( pair < int, int> coordinates );
		tile * getTileDownRight ( tile * tile );
		bool canWalkDownRight ( pair < int, int> coordinates );
		bool canWalkDownRight ( tile * tile );
		bool canJumpDownRight ( pair < int, int> coordinates );
		bool canJumpDownRight ( tile * tile );
		bool walkDownRight ( tile * tile );
		bool jumpDownRight ( tile * tile );

		pair < int, int > getCoordLeft ( pair < int, int> coordinates );
		pair < int, int > getCoordLeft ( tile * tile );
		pair < int, int > getCoordJumpLeft ( tile * tile );
		tile * getTileLeft ( pair < int, int> coordinates );
		tile * getTileLeft ( tile * tile );
		bool canWalkLeft ( pair < int, int> coordinates );
		bool canWalkLeft ( tile * tile );
		bool canJumpLeft ( pair < int, int> coordinates );
		bool canJumpLeft ( tile * tile );
		bool walkLeft ( tile * tile );
		bool jumpLeft ( tile * tile );

		pair < int, int > getCoordUpLeft ( pair < int, int> coordinates );
		pair < int, int > getCoordUpLeft ( tile * tile );
		pair < int, int > getCoordJumpUpLeft ( tile * tile );
		tile * getTileUpLeft ( pair < int, int> coordinates );
		tile * getTileUpLeft ( tile * tile );
		bool canWalkUpLeft ( pair < int, int> coordinates );
		bool canWalkUpLeft ( tile * tile );
		bool canJumpUpLeft ( pair < int, int> coordinates );
		bool canJumpUpLeft ( tile * tile );
		bool walkUpLeft ( tile * tile );
		bool jumpUpLeft ( tile * tile );

		pair < int, int > getCoordDownLeft ( pair < int, int> coordinates );
		pair < int, int > getCoordDownLeft ( tile * tile );
		pair < int, int > getCoordJumpDownLeft ( tile * tile );
		tile * getTileDownLeft ( pair < int, int> coordinates );
		tile * getTileDownLeft ( tile * tile );
		bool canWalkDownLeft ( pair < int, int> coordinates );
		bool canWalkDownLeft ( tile * tile );
		bool canJumpDownLeft ( pair < int, int> coordinates );
		bool canJumpDownLeft ( tile * tile );
		bool walkDownLeft ( tile * tile );
		bool jumpDownLeft ( tile * tile );

		bool canWalk ( tile * tile, unsigned int direction );
		bool canJump ( tile * tile, unsigned int direction );
		bool canMove ( tile * tile, unsigned int move );
		bool canMove ( board_move move );
		bool walk ( tile * tile, unsigned int direction );
		bool jump ( tile * tile, unsigned int direction );
		bool move ( tile * tile, unsigned int direction );
		bool move ( board_move move );

	protected:

	private:

		/* Sets the board to a state using a vector of strings */
		void setBoard ( vector < string >, int );

		/* The board in a vector of strings */
		vector < string > b;

		/* The board in a 2-dimensional vector of tiles. */
		vector < vector < tile > > tb;

		/* The tiles that make up the nest of a player */
		vector < vector < tile * > > nests;

		/* The tiles belonging to a player, never reorganized. */
		vector < vector < tile * > > playerTiles;

};

#endif // board
