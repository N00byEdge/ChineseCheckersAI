#include "board.h"

tile * orgTile;
static vector < tile* > staticEmptyTilePointerVector;

/* An empty board in the data format that we store the board */
vector < string > emptyBoard =

{"0", // 16
"00", // 15
"000", // 14
"0000", // 13
"0000000000000", // 12
"000000000000", // 11
"00000000000", // 10
"0000000000", // 9
"000000000", // 8
"0000000000", // 7
"00000000000", // 6
"000000000000", // 5
"0000000000000", // 4
"0000", // 3
"000", // 2
"00", // 1
"0"}; // 0

vector < string > Board2Players =

{"2", // 16
"22", // 15
"222", // 14
"2222", // 13
"0000000000000", // 12
"000000000000", // 11
"00000000000", // 10
"0000000000", // 9
"000000000", // 8
"0000000000", // 7
"00000000000", // 6
"000000000000", // 5
"0000000000000", // 4
"1111", // 3
"111", // 2
"11", // 1
"1"}; // 0

/*
            2
           2 2
          2 2 2
         2 2 2 2
0 0 0 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0 0 0
  0 0 0 0 0 0 0 0 0 0 0
   0 0 0 0 0 0 0 0 0 0
  0 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
         1 1 1 1
          1 1 1
           1 1
            1
*/

/*
 *  Reset the board to a empty board. A good idea after creating a board object, but not required as you may have a template. If you are not copying a board, always reset it.
 *  Set numPlayers first, as the new board state depends on the number of players.
 */

void board::print ( ) {

	for ( int i = this -> tb.size ( ) - 1; i != -1; -- i ) {

        if ( i == 0 || i == tb.size ( ) - 1 ) {
            cout << "            ";
        } else if ( i == 1 || i == tb.size ( ) - 2 ) {
            cout << "           ";
        } else if ( i == 2 || i == tb.size ( ) - 3 ) {
            cout << "          ";
        } else if ( i == 3 || i == tb.size ( ) - 4 ) {
            cout << "         ";
        } else if ( i == 5 || i == tb.size ( ) - 6 ) {
            cout << " ";
        } else if ( i == 6 || i == tb.size ( ) - 7 ) {
            cout << "  ";
        } else if ( i == 7 || i == tb.size ( ) - 8 ) {
            cout << "   ";
        } else if ( i == 8 ) {
            cout << "    ";
        }

		for ( int j = 0; j < this -> tb [ i ].size ( ); ++ j )

			cout << this -> tb [ i ] [ j ]. getContents ( ) << " ";

		cout << endl;

	}

}

void board::printWithCoords ( ) {

	for ( int i = this -> tb.size ( ) - 1; i != -1; -- i ) {

		for ( int j = 0; j < this -> tb [ i ].size ( ); ++ j ) {

			pair < int, int > coords = this -> tb [ i ] [ j ].getCoordinates ( );

			cout << "[" << this -> tb [ i ] [ j ].getCoordinates ( ).first << ", " << this -> tb [ i ] [ j ].getCoordinates ( ).second << "]" << this -> tb [ i ] [ j ]. getContents ( );

		}

		cout << endl;

	}

}

void board::resetBoard ( int numPlayers ) {

	/* If the number of players is not equal to 2, 3, 4 or 6, we are going to use 2 players. */
	if( !( numPlayers == 2 || numPlayers == 4 || numPlayers == 6 ) ) numPlayers = 2;

	this -> numPlayers = numPlayers;

	/* Sets the board to an empty board, defined at the top. */
	if ( numPlayers == 2 ) board::setBoard ( Board2Players, numPlayers );
	else board::setBoard ( emptyBoard, numPlayers );

}

void board::setBoard ( vector < string > board, int numPlayers ) {

	#ifdef DEBUGGING
	cout << "Setting board state:\n";
	for( int i = board.size ( ) - 1; i != -1; -- i ) cout << board [ i ] << endl;
	#endif //DEBUGGING

	for ( int i = 0; i < board.size ( ); ++ i ){
		for( int j = 0; j < board [ i ].size ( ); ++ j )
			board [ i ] [ j ] -= 48;
	}

	this -> b = board;

	vector < tile > emptyTileVector;
	vector < tile * > emptyTilePointerVector;

	for ( int i = 0; i < numPlayers + 1; ++ i ) {

		this -> nests.push_back ( emptyTilePointerVector );
		this -> playerTiles.push_back ( emptyTilePointerVector );

	}

	for ( int i = board.size ( ) - 1; i != - 1; -- i ) {

		this -> tb.push_back ( emptyTileVector );

		for ( int j = 0; j < board [ i ].size ( ); ++ j ) {

			#ifdef DEBUGGING
			cout << "Setting tile properties.\n";
			#endif // DEBUGGING

			tile t (

				j, /* x coordinate */
				i, /* y coordinate */
				int ( board [ i ] [ j ] ) /* Contents */

				);

			#ifdef DEBUGGING
			cout << "Finished setting tile properties.\n";
			cout << "Pushing back tile.\n";
			#endif // DEBUGGING

			this -> tb [ this -> tb.size ( ) - 1 ].push_back ( t );

			#ifdef DEBUGGING
			cout << "Finished pushing back tile.\n";
			#endif // DEBUGGING

		}
	}

	for ( int i = 0; i < tb.size ( ); ++ i ) {

		for ( int j = 0; j < tb [ i ].size ( ); ++ j ) {

			pair < int, int > pii;
			pii.first = j;
			pii.second = i;

			tile * t = this -> getTile ( pii );

			this -> nests [ t -> getContents ( ) ].push_back ( t );
			this -> playerTiles [ t -> getContents ( ) ].push_back ( t );

		}

	}

	#ifdef DEBUGGING
	cout << "Resorting list.\n";
	#endif // DEBUGGING

	reverse ( this -> tb.begin ( ), this -> tb.end ( ) );

	#ifdef DEBUGGING
	cout << "Finished setting board state.\n";
	#endif // DEBUGGING
}

tile * board::getTile ( pair < int, int > pii ) {

	tile t ( pii.first, pii.second, 0 );
	if ( this -> isValidTile ( t.getCoordinates ( ) ) )
		return & ( this -> tb [ pii.second ] [ pii.first ] );
	else return nullptr;

}

bool board::isValidTile ( pair < int, int > pii ) {

	#ifdef DEBUGGING
	cout << "Is [" << pii.first << ", " << pii.second << "] a valid tile?\n";
	#endif // DEBUGGING

	if ( pii.second < this -> tb.size ( ) && - 1 < pii.second ) {

		if ( pii.first < this -> tb [ pii.second ]. size ( )  && - 1 < pii.first ) {

			#ifdef DEBUGGING
			cout << "We have reason to believe that this tile is valid.\n";
			#endif // DEBUGGING

			return true;

		} else {

			#ifdef DEBUGGING
			cout << pii.first << " was not a valid x coordinate where y = " << pii.second << endl;
			#endif // DEBUGGING

			return false;

		}

	} else {

		#ifdef DEBUGGING
		cout << pii.second << " was not a valid y coordinate.\n";
		#endif // DEBUGGING

		return false;

	}

}

bool board::isValidTile ( tile * t ) {

	if ( t == nullptr ) {

		#ifdef DEBUGGING
		cout << "isValidTile: Null pointer! Terminating.\n";
		#endif // DEBUGGING

		return false;

	}

	#ifdef DEBUGGING

	cout << "Is " << t << " a valid tile?\n";

	if ( isValidTile( t -> getCoordinates ( ) ) ) {
		cout << t << " has coordinates [" << t -> getCoordinates ( ).first << ", " << t -> getCoordinates ( ).second << "]\n";
	} else {
		cout << t << "did not have valid coordinates.\n";
	}

	#endif // DEBUGGING

	return this -> isValidTile ( t -> getCoordinates ( ) );

}

vector < tile * > board::getPlayerTiles ( int player ) {

	this -> playerTiles.clear ( );
	for ( int i = 0; i < player + 1; ++ i )
        this -> playerTiles.push_back ( staticEmptyTilePointerVector );

	for ( int i = 0; i < tb.size ( ); ++ i ) {

		for ( int j = 0; j < tb [ i ].size ( ); ++ j ) {

			pair < int, int > pii;
			pii.first = j;
			pii.second = i;

			tile * t = this -> getTile ( pii );

			this -> nests [ t -> getContents ( ) ].push_back ( t );
			this -> playerTiles [ t -> getContents ( ) ].push_back ( t );

		}

	}

	if ( player < playerTiles.size ( ) )
		return playerTiles [ player ];

}

pair < int, int > board::getCoordRight ( pair < int, int > pii ) {

	pii.first ++;

	return pii;

}

pair < int, int > board::getCoordRight ( tile * t ) {

	return getCoordRight ( t -> getCoordinates ( ) );

}

tile * board::getTileRight ( pair < int, int> pii ) {

	pii = getCoordRight ( pii );

	tile * t = getTile ( pii );

	if ( this -> isValidTile ( t ) )

		return t;

}

tile * board::getTileRight ( tile * t ) {

	t = this -> getTile ( this -> getCoordRight ( t ) );

	if( isValidTile ( t ) )
		return t;

}

pair < int, int > board::getCoordUpRight ( pair < int, int > pii ) {

	if ( pii.second <= 2 ) {

		pii.first ++;

	}

	else if ( pii.second == 3 ) {

		pii.first += 5;

	}

	else if ( 4 <= pii.second && pii.second <= 7 ) {


	}

	else if ( 8 <= pii.second && pii.second <= 12 ) {

		pii.first ++;

	}

	else if ( pii.second == 13 ) {

		pii.first -= 4;

	}

	else if ( 13 <= pii.second ) {

	}

	pii.second ++;

	return pii;

}

pair < int, int > board::getCoordUpRight ( tile * t ) {

	return getCoordUpRight ( t -> getCoordinates ( ) );

}

tile * board::getTileUpRight ( pair < int, int> pii ) {

	pii = getCoordUpRight ( pii );

	if ( isValidTile ( pii ) )
		return getTile ( pii );

}

tile * board::getTileUpRight ( tile * t ) {

	t = this -> getTile ( this -> getCoordUpRight ( t ) );

	if( isValidTile ( t ) )
		return t;

}

pair < int, int > board::getCoordDownRight ( pair < int, int > pii ) {

	if ( pii.second <= 3 ) {

	}

	else if ( pii.second == 4 ) {

		pii.first -= 4;

	}

	else if ( 5 <= pii.second && pii.second <= 8 ) {

		pii.first ++;

	}

	else if ( 9 <= pii.second && pii.second <= 12 ) {

	}

	else if ( pii.second == 13 ) {

		pii.first += 5;

	}

	else if ( 14 <= pii.second ){

		pii.first ++;

	}


	pii.second --;

	return pii;

}

pair < int, int > board::getCoordDownRight ( tile * t ) {

	return getCoordDownRight( t -> getCoordinates ( ) );

}

tile * board::getTileDownRight ( pair < int, int> pii ) {

	pii = getCoordDownRight ( pii );

	if ( isValidTile ( pii ) )
		return getTile ( pii );

}

tile * board::getTileDownRight ( tile * t ) {

	t = this -> getTile ( this -> getCoordDownRight ( t ) );

	if( isValidTile ( t ) )
		return t;

}

pair < int, int > board::getCoordLeft ( pair < int, int > pii ){

	pii.first --;

	return pii;

}

pair < int, int > board::getCoordLeft ( tile * t ) {

	return getCoordLeft( t -> getCoordinates ( ) );

}

tile * board::getTileLeft ( pair < int, int> pii ) {

	pii = getCoordLeft ( pii );

	if ( isValidTile ( pii ) )
		return getTile ( pii );

}

tile * board::getTileLeft ( tile * t ) {

	t = this -> getTile ( this -> getCoordLeft ( t ) );

	if( isValidTile ( t ) )
		return t;

}

pair < int, int > board::getCoordUpLeft ( pair < int, int > pii ) {

	if ( pii.second <= 2 ) {

	} else if ( pii.second == 3 ) {

		pii.first += 4;

	} else if ( 4 <= pii.second && pii.second <= 7 ) {

		pii.first --;

	} else if ( 8 <= pii.second && pii.second <= 11) {


	} else if ( pii.second == 12 ) {

		pii.first -= 5;

	} else if ( 13 <= pii.second ) {

		pii.first --;

	}

	pii.second ++;

	return pii;

}

pair < int, int > board::getCoordUpLeft ( tile * t ) {

	return getCoordUpLeft ( t -> getCoordinates ( ) );

}

tile * board::getTileUpLeft ( pair < int, int> pii ) {

	pii = getCoordUpLeft ( pii );

	if ( isValidTile ( pii ) )
		return getTile ( pii );

}

tile * board::getTileUpLeft ( tile * t ) {

	t = this -> getTile ( this -> getCoordUpLeft ( t ) );

	if( isValidTile ( t ) )
		return t;

}

pair < int, int > board::getCoordDownLeft ( pair < int, int > pii ) {

	if ( pii.second <= 3 ) {

		pii.first --;

	}

	else if ( pii.second == 4 ) {

		pii.first -= 5;

	}

	else if ( 5 <= pii.second && pii.second <= 8 ) {

	}

	else if ( 9 <= pii.second && pii.second <= 12 ) {

			pii.first --;

	}

	else if ( pii.second == 13 ) {

		pii.first += 4;

	}

	else if ( 14 <= pii.second ){

	}

	pii.second --;

	return pii;

}

pair < int, int > board::getCoordDownLeft ( tile * t ) {

	return getCoordDownLeft ( t -> getCoordinates ( ) );

}

tile * board::getTileDownLeft ( pair < int, int> pii ) {

	pii = getCoordDownLeft ( pii );

	if ( isValidTile ( pii ) )
		return getTile ( pii );

}

tile * board::getTileDownLeft ( tile * t ) {

	t = this -> getTile ( this -> getCoordDownLeft ( t ) );

	if( isValidTile ( t ) )
		return t;

}

bool board::canWalkRight ( tile * t ) {

	#ifdef DEBUGGING
	cout << "Can " << t << " walk right?\n";
	#endif // DEBUGGING

	tile * tRight;

	if ( this -> getTileRight( t ) ){

		tRight = this -> getTileRight( t );

		if ( tRight == nullptr ) {

			#ifdef DEBUGGING
			cout << "canWalkRight: null pointer. Terminating.\n";
			#endif //DEBUGGING

			return false;

		}

		return ( tRight ) -> getContents ( ) == 0;

	}

	return false;

}

bool board::canWalkUpRight ( tile * t ) {

	#ifdef DEBUGGING
	cout << "Can " << t << " walk upRight?\n";
	#endif // DEBUGGING

	tile * tUpRight;

	if ( this -> getTileUpRight( t ) ){

		tUpRight = this -> getTileUpRight( t );

		if ( tUpRight == nullptr ) {

			#ifdef DEBUGGING
			cout << "canWalkUpRight: null pointer. Terminating.\n";
			#endif //DEBUGGING

			return false;

		}

		return ( tUpRight ) -> getContents ( ) == 0;

	}

	return false;

}

bool board::canWalkDownRight ( tile * t ) {

	#ifdef DEBUGGING
	cout << "Can " << t << " walk downRight?\n";
	#endif // DEBUGGING

	tile * tDownRight;

	if ( this -> getTileDownRight( t ) ){

		tDownRight = this -> getTileDownRight( t );

		if ( tDownRight == nullptr ) {

			#ifdef DEBUGGING
			cout << "canWalkDownRight: null pointer. Terminating.\n";
			#endif //DEBUGGING

			return false;

		}

		return ( tDownRight ) -> getContents ( ) == 0;

	}

	return false;

}

bool board::canWalkLeft ( tile * t ) {

	#ifdef DEBUGGING
	cout << "Can " << t << " walk left?\n";
	#endif // DEBUGGING

	tile * tLeft;

	if ( this -> getTileLeft( t ) ){

		tLeft = this -> getTileLeft( t );

		if ( tLeft == nullptr ) {

			#ifdef DEBUGGING
			cout << "canWalkLeft: null pointer. Terminating.\n";
			#endif //DEBUGGING

			return false;

		}

		return ( tLeft ) -> getContents ( ) == 0;

	}

	return false;

}

bool board::canWalkUpLeft ( tile * t ) {

	#ifdef DEBUGGING
	cout << "Can " << t << " walk upLeft?\n";
	#endif // DEBUGGING

	tile * tUpLeft;

	if ( this -> getTileUpLeft( t ) ){

		tUpLeft = this -> getTileUpLeft( t );

		if ( tUpLeft == nullptr ) {

			#ifdef DEBUGGING
			cout << "canWalkUpLeft: null pointer. Terminating.\n";
			#endif //DEBUGGING

			return false;

		}

		return ( tUpLeft ) -> getContents ( ) == 0;

	}

	return false;

}

bool board::canWalkDownLeft ( tile * t ) {

	#ifdef DEBUGGING
	cout << "Can " << t << " walk downLeft?\n";
	#endif // DEBUGGING

	tile * tDownLeft;

	if ( this -> getTileDownLeft( t ) ){

		tDownLeft = this -> getTileDownLeft( t );

		if ( tDownLeft == nullptr ) {

			#ifdef DEBUGGING
			cout << "canWalkDownLeft: null pointer. Terminating.\n";
			#endif //DEBUGGING

			return false;

		}

		return ( tDownLeft ) -> getContents ( ) == 0;

	}

	return false;

}

bool board::canJumpRight ( tile * t ) {

	orgTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = this -> getTileRight ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpRight: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = this -> getTileRight ( t ) ) && t != nullptr ) {

					#ifdef DEBUGGING
					cout << "canJumpRight: ["
						<< orgTile -> getCoordinates ( ).first
						<< ", "
						<< orgTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return true;

			} else {

				#ifdef DEBUGGING
				cout << "canJumpRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can't end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

		lastTile = t;
	}

	return false;

}

pair < int, int > board::getCoordJumpRight ( tile * tile ) {

	pair < int, int > pii;

	for ( int i = 0; tile = this -> getTileRight ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = this -> getTileRight ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpUpRight ( tile * t ) {

	orgTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = this -> getTileUpRight ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpUpRight: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = this -> getTileUpRight ( t ) ) && t != nullptr ) {

					#ifdef DEBUGGING
					cout << "canJumpUpRight: ["
						<< orgTile -> getCoordinates ( ).first
						<< ", "
						<< orgTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpUpRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return true;

			} else {

				#ifdef DEBUGGING
				cout << "canJumpUpRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can't end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

		lastTile = t;
	}

	return false;

}

pair < int, int > board::getCoordJumpUpRight ( tile * tile ) {

	pair < int, int > pii;

	for ( int i = 0; tile = this -> getTileUpRight ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = this -> getTileUpRight ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpDownRight ( tile * t ) {

	orgTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = this -> getTileDownRight ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpDownRight: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = this -> getTileDownRight ( t ) ) && t != nullptr ) {

					#ifdef DEBUGGING
					cout << "canJumpDownRight: ["
						<< orgTile -> getCoordinates ( ).first
						<< ", "
						<< orgTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpDownRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return true;

			} else {

				#ifdef DEBUGGING
				cout << "canJumpDownRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can't end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

		lastTile = t;
	}

	return false;

}

pair < int, int > board::getCoordJumpDownRight ( tile * tile ) {

	pair < int, int > pii;

	for ( int i = 0; tile = this -> getTileDownRight ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = this -> getTileDownRight ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpLeft ( tile * t ) {

	orgTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = this -> getTileLeft ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpLeft: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = this -> getTileLeft ( t ) ) && t != nullptr ) {

					#ifdef DEBUGGING
					cout << "canJumpLeft: ["
						<< orgTile -> getCoordinates ( ).first
						<< ", "
						<< orgTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return true;

			} else {

				#ifdef DEBUGGING
				cout << "canJumpLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can't end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

		lastTile = t;
	}

	return false;

}

pair < int, int > board::getCoordJumpLeft ( tile * tile ) {

	pair < int, int > pii;

	for ( int i = 0; tile = this -> getTileLeft ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = this -> getTileLeft ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpUpLeft ( tile * t ) {

	orgTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = this -> getTileUpLeft ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpUpLeft: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = this -> getTileUpLeft ( t ) ) && t != nullptr ) {

					#ifdef DEBUGGING
					cout << "canJumpUpLeft: ["
						<< orgTile -> getCoordinates ( ).first
						<< ", "
						<< orgTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpUpLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return true;

			} else {

				#ifdef DEBUGGING
				cout << "canJumpUpLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can't end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

		lastTile = t;
	}

	return false;

}

pair < int, int > board::getCoordJumpUpLeft ( tile * tile ) {

	pair < int, int > pii;

	for ( int i = 0; tile = this -> getTileUpLeft ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = this -> getTileUpLeft ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpDownLeft ( tile * t ) {

	orgTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = this -> getTileDownLeft ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpDownLeft: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = this -> getTileDownLeft ( t ) ) && t != nullptr ) {

					#ifdef DEBUGGING
					cout << "canJumpDownLeft: ["
						<< orgTile -> getCoordinates ( ).first
						<< ", "
						<< orgTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpDownLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return true;

			} else {

				#ifdef DEBUGGING
				cout << "canJumpDownLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can't end jump at ["
					<< t -> getCoordinates ( ).first
					<< ", "
					<< t -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

		lastTile = t;
	}

	return false;

}

pair < int, int > board::getCoordJumpDownLeft ( tile * tile ) {

	pair < int, int > pii;

	for ( int i = 0; tile = this -> getTileDownLeft ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = this -> getTileDownLeft ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canWalk ( tile * t, unsigned int direction ) {

	switch ( direction ) {

	case 1:
		return this -> canWalkRight ( t );

	case 2:
		return this -> canWalkDownRight ( t );

	case 3:
		return this -> canWalkDownLeft ( t );

	case 4:
		return this -> canWalkLeft ( t );

	case 5:
		return this -> canWalkUpLeft ( t );

	case 6:
		return this -> canWalkUpRight ( t );

	default:
		return false;

	}

}

bool board::canJump ( tile * t, unsigned int direction ) {

	switch ( direction ) {

	case 1:
		return this -> canJumpRight ( t );

	case 2:
		return this -> canJumpDownRight ( t );

	case 3:
		return this -> canJumpDownLeft ( t );

	case 4:
		return this -> canJumpLeft ( t );

	case 5:
		return this -> canJumpUpLeft ( t );

	case 6:
		return this -> canJumpUpRight ( t );

	default:
		return false;

	}

}

bool board::canMove ( tile * t, unsigned int move ) {
	if ( 1 <= move && move <= 6 )
		return this -> canWalk ( t, move );
	else if ( 7 <= move && move <= 12 )
		return this -> canJump ( t, move - 6 );
	else
		return false;
}

bool board::canMove ( board_move m ) {

	tile * t;

	if ( t = getTile ( m.getTileStartCoords ( ) ) )
		return this -> canMove ( this -> getTile ( m.getTileStartCoords ( ) ), m.getRawData ( ) );

	return false;
}

bool board::walkRight ( tile * t ) {
	if ( this -> canWalkRight ( t ) ) {
		this -> getTileRight ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTileRight ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkUpRight ( tile * t ) {
	if ( this -> canWalkUpRight ( t ) ) {
		this -> getTileUpRight ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTileUpRight ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkDownRight ( tile * t ) {
	if ( this -> canWalkDownRight ( t ) ) {
		this -> getTileDownRight ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTileDownRight ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkLeft ( tile * t ) {
	if ( this -> canWalkLeft ( t ) ) {
		this -> getTileLeft ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTileLeft ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkUpLeft ( tile * t ) {
	if ( this -> canWalkUpLeft ( t ) ) {
		this -> getTileUpLeft ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTileUpLeft ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkDownLeft ( tile * t ) {
	if ( this -> canWalkDownLeft ( t ) ) {
		this -> getTileDownLeft ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTileDownLeft ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpRight ( tile * t ) {
	if ( this -> canJumpRight ( t ) ) {
		this -> getTile ( this -> getCoordJumpRight ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTile ( this -> getCoordJumpRight ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpUpRight ( tile * t ) {
	if ( this -> canJumpUpRight ( t ) ) {
		this -> getTile ( this -> getCoordJumpUpRight ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTile ( this -> getCoordJumpUpRight ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpDownRight ( tile * t ) {
	if ( this -> canJumpDownRight ( t ) ) {
		this -> getTile ( this -> getCoordJumpDownRight ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTile ( this -> getCoordJumpDownRight ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpLeft ( tile * t ) {
	if ( this -> canJumpLeft ( t ) ) {
		this -> getTile ( this -> getCoordJumpLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTile ( this -> getCoordJumpLeft ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpUpLeft ( tile * t ) {
	if ( this -> canJumpUpLeft ( t ) ) {
		this -> getTile ( this -> getCoordJumpUpLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTile ( this -> getCoordJumpUpLeft ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpDownLeft ( tile * t ) {
	if ( this -> canJumpDownLeft ( t ) ) {
		this -> getTile ( this -> getCoordJumpDownLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( this -> playerTiles [ t -> getContents ( ) ] [ i ] == t )
				this -> playerTiles [ t -> getContents ( ) ] [ i ] = this -> getTile ( this -> getCoordJumpDownLeft ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

pair < int, int > board::getWalkCoords ( tile * t, unsigned int direction ) {

	switch ( direction ) {

		case 1:
			return this -> getCoordRight ( t );

		case 2:
			return this -> getCoordDownRight ( t );

		case 3:
			return this -> getCoordDownLeft ( t );

		case 4:
			return this -> getCoordLeft ( t );

		case 5:
			return this -> getCoordUpLeft ( t );

		case 6:
			return this -> getCoordUpRight ( t );

	}
}

pair < int, int > board::getJumpCoords ( tile * t, unsigned int direction ) {

	switch ( direction ) {

		case 1:
			return this -> getCoordJumpRight ( t );

		case 2:
			return this -> getCoordJumpDownRight ( t );

		case 3:
			return this -> getCoordJumpDownLeft ( t );

		case 4:
			return this -> getCoordJumpLeft ( t );

		case 5:
			return this -> getCoordJumpUpLeft ( t );

		case 6:
			return this -> getCoordJumpUpRight ( t );

	}
}

pair < int, int > board::getMoveCoords ( board_move m ) {

	if ( 1 <= m.getRawData ( ) && m.getRawData ( ) <= 6 )
		return this -> getWalkCoords ( this -> getTile ( m.getTileStartCoords ( ) ), m.getRawData ( ) );
	else if ( 7 <= m.getRawData ( ) && m.getRawData ( ) <= 12 )
		return this -> getJumpCoords ( this -> getTile ( m.getTileStartCoords ( ) ), m.getRawData ( ) - 6 );

}

bool board::walk ( tile * t, unsigned int direction ) {

	switch ( direction ) {

		case 1:
			return this -> walkRight ( t );

		case 2:
			return this -> walkDownRight ( t );

		case 3:
			return this -> walkDownLeft ( t );

		case 4:
			return this -> walkLeft ( t );

		case 5:
			return this -> walkUpLeft ( t );

		case 6:
			return this -> walkUpRight ( t );

		default:
			return false;
	}

}

bool board::jump ( tile * t, unsigned int direction ) {

	switch ( direction ) {

		case 1:
			return this -> jumpRight ( t );

		case 2:
			return this -> jumpDownRight ( t );

		case 3:
			return this -> jumpDownLeft ( t );

		case 4:
			return this -> jumpLeft ( t );

		case 5:
			return this -> jumpUpLeft ( t );

		case 6:
			return this -> jumpUpRight ( t );

		default:
			return false;
	}

}

bool board::move ( tile * t, unsigned int move ) {
	if ( 1 <= move && move <= 6 )
		return this -> walk ( t, move );
	else if ( 7 <= move && move <= 12 )
		return this -> jump ( t, move - 6 );
	else
		return false;
}

bool board::move ( board_move m ) {
	return this -> move ( this -> getTile ( m.getTileStartCoords ( ) ), m.getRawData ( ) );
}

vector < board_move > board::getPossibleMoves ( tile * t ) {

	#ifdef DEBUGGING
	cout << "getPossibleMoves: " << t << endl;
	#endif //DEBUGGING

	vector < board_move > r;

	if ( ! this -> isValidTile ( t ) )
		return r;

	if ( t -> getContents ( ) == 0 )
		return r;

	board_move m;

	m.setTileStartCoords ( t -> getCoordinates ( ) );

	for ( int i = 1; i <= 12; ++ i ) {
		if ( this -> canMove ( t, i ) ) {
			m.setRawData ( i );
			r.push_back ( m );
		}

	}

	return r;

}

vector < board_move > board::getPossibleMoves ( ) {

	vector < board_move > r;

	for ( int i = 0; i < tb.size ( ); ++ i ) {

		for ( int j = 0; j < tb [ i ].size ( ); ++ j ) {

			vector < board_move > temp = this -> getPossibleMoves ( & tb [ i ] [ j ] );

			for ( int k = 0; k < temp.size ( ); ++ k )
				r.push_back ( temp [ k ] );

		}

	}

	return r;

}

bool board::canMakeTurn ( board_turn trn ) {

	board deadBoard = * this;
	return deadBoard.makeTurn ( trn );

	return true;

}

bool board::makeTurn ( board_turn trn ) {

	if ( trn.moves.size ( ) == 1 ) {

		/* If the turn only is one move, do that move */
		return this -> move ( trn.moves [ 0 ] );

	} else if ( trn.moves.size ( ) == 0 ) {

		/* If the turn doesn't contain any moves, don't do anything. */
		return true;

	}


	/* If the turn contains more than one move, and doesn't contain only jumps, the turn is invalid. */
	for ( int i = 0; i < trn.moves.size ( ); ++ i ) {

		if ( trn.moves [ 0 ].getRawData ( ) <= 6 )
			return false;

	}

	/* If the tile has the same position more than once during a turn, the turn is invalid. */

	vector < pair < int, int > > v;

	for ( int i = 0; i < trn.moves.size ( ); ++ i ) {
		for ( int j = 0; j < v.size ( ); ++ j ) {
			if ( trn.moves [ i ].getTileStartCoords ( ) == v [ j ] )
				return false;
		}
		v.push_back ( trn.moves [ i ].getTileStartCoords ( ) );
	}

	/*
	 * Checking that the tile start coords are right for every move (that the last move would end up in the correct tile).
	 * Also checks that all moves are valid.
	 */

	board dummyBoard;

	for ( int i = 0; i < trn.moves.size ( ) - 1; ++ i ) {
		if ( trn.moves [ i + 1 ].getTileStartCoords ( ) != dummyBoard.getMoveCoords ( trn.moves [ i ] ) );
			return false;
		if ( !dummyBoard.move ( trn.moves [ i ] ) )
			return false;
	}

	* this = dummyBoard;

	return true;

}

void board::rotate ( ) {

	#ifdef DEBUGGING
	cout << "Rotating board:\n";
	this -> print ( );
	#endif //DEBUGGING

	auto rotationMap = lib::getCoordTranslationTable ( );

	pair < int, int > pii1, pii2;

	auto tb2 = this -> tb;

	for ( int i = 0; i < tb.size ( ); ++ i ) {

		for ( int j = 0; j < tb [ i ].size ( ); ++ j ) {

			pii1.first = j;
			pii1.second = i;
			pii2 = rotationMap [ pii1 ];

			tb2 [ pii2.second ] [ pii2.first ].updateCoordinates ( pii2.first, pii2.second );
			tb2 [ pii2.second ] [ pii2.first ].setContents ( tb [ i ] [ j ].getContents ( ) );

		}

	}

	/* Save board changes */

	for ( int i = 0; i < this -> tb.size ( ); ++ i ) {
		for ( int j = 0; j < this -> tb [ i ].size ( ); ++ j )
			this -> tb [ i ] [ j ] = tb2 [ i ] [ j ];
	}

	for ( int i = 0; i < this -> playerTiles.size ( ); ++ i ) {

		for ( int j = 0; j < this -> playerTiles [ i ].size ( ); ++ j ) {

			this -> playerTiles [ i ] [ j ] = this -> getTile ( rotationMap [ playerTiles [ i ] [ j ] -> getCoordinates ( ) ] );

		}

	}

	for ( int i = 0; i < this -> nests.size ( ); ++ i ) {

		for ( int j = 0; j < this -> nests [ i ].size ( ); ++ j ) {

			this -> nests [ i ] [ j ] = this -> getTile ( rotationMap [ nests [ i ] [ j ] -> getCoordinates ( ) ] );

		}

	}

	#ifdef DEBUGGING
	cout << "Rotated board:\n";
	this -> print ( );
	#endif //DEBUGGING

}

void board::rotate ( int steps ) {

	for ( int i = 0; i < steps % 6; ++ i )
		this -> rotate ( );

}

int board::rotateForPerspective ( int player ) {

	bool correctRotation = false;

	int rotations = 0;

	while ( !correctRotation ) {

		if ( nests [ player ] [ 0 ] -> getCoordinates ( ).second <= 3 ){

			correctRotation = true;

			#ifdef DEBUGGING
			cout << "I think that the board is correctly rotated now, "
				<< "nests [ player ] [ 0 ] -> getCoordinates ( ).second = "
				<< nests [ player ] [ 0 ] -> getCoordinates ( ).second
				<< endl;
			#endif //DEBUGGING

			return rotations;

		} else {

			#ifdef DEBUGGING
			cout << "This board needs to be rotated again, "
				<< "nests [ player ] [ 0 ] -> getCoordinates ( ).second = "
				<< nests [ player ] [ 0 ] -> getCoordinates ( ).second
				<< endl;
			#endif //DEBUGGING

			this -> rotate ( );
			++ rotations;

		}

	}

}
