#include "board.h"

tile * orgTile;

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
 *  Reset the board to a empty board. A good idea after creating a board object, but not required as you may have a template. If you are not copying a board, always reset it.
 *  Set numPlayers first, as the new board state depends on the number of players.
 */

void board::print ( ) {

	for ( int i = this -> tb.size ( ) - 1; i != -1; -- i ) {

		for ( int j = 0; j < this -> tb [ i ].size ( ); ++ j )

			cout << this -> tb [ i ] [ j ]. getContents ( );

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
	if ( isValidTile ( t.getCoordinates ( ) ) )
		return & ( this -> tb [ pii.second ] [ pii.first ] );

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

	if ( t == 0 ) {

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

	pii.second ++;

	if ( pii.second <= 2 ) {

		pii.first ++;

	}

	else if ( pii.second == 4 ) {

		pii.first += 5;

	}

	else if ( 5 <= pii.second && pii.second <= 7 ) {


	}

	else if ( 8 <= pii.second && pii.second <= 11) {

		pii.first ++;

	}

	else if ( pii.second == 12 ) {

		pii.first -= 4;

	}

	else if ( 13 <= pii.second ) {

	}

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

	pii.second --;

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

	pii.second ++;

	if ( pii.second <= 2 ) {

	} else if ( pii.second == 4 ) {

		pii.first += 4;

	} else if ( 5 <= pii.second && pii.second <= 7 ) {

		pii.first --;

	} else if ( 8 <= pii.second && pii.second <= 11) {


	} else if ( pii.second == 12 ) {

		pii.first -= 5;

	} else if ( 13 <= pii.second ) {

		pii.first --;

	}

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

	pii.second --;

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

		if ( tRight == 0 ) {

			#ifdef DEBUGGING
			cout << "canWalkRight: null pointer. Terminating.\n";
			#endif //DEBUGGING

			return false;

		}

		return ( t ) -> getContents ( ) == 0;

	}

	return false;

}

bool board::canWalkUpRight ( tile * tile ) {

	return getTileUpRight ( tile ) -> getContents ( ) == 0;

}

bool board::canWalkDownRight ( tile * tile ) {

	return getTileDownRight ( tile ) -> getContents ( ) == 0;

}

bool board::canWalkLeft ( tile * tile ) {

	return getTileLeft ( tile ) -> getContents ( ) == 0;

}

bool board::canWalkUpLeft ( tile * tile ) {

	return getTileUpLeft ( tile ) -> getContents ( ) == 0;

}

bool board::canWalkDownLeft ( tile * tile ) {

	return getTileDownLeft ( tile ) -> getContents ( ) == 0;

}

bool board::canJumpRight ( tile * tile ) {

	orgTile = tile;

	if ( tile -> getContents ( ) == 0 )
		return false;

	for ( int i = 0; tile = this -> getTileRight ( tile ); ++ i ) {

		#ifdef DEBUGGING
		cout << "canJumpRight: i: " << i << endl;
		#endif //DEBUGGING

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( tile = this -> getTileRight ( tile ) ) ) {

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

			if ( tile -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
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
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

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

bool board::canJumpUpRight ( tile * tile ) {

	orgTile = tile;

	if ( tile -> getContents ( ) == 0 )
		return false;

	for ( int i = 0; tile = this -> getTileUpRight ( tile ); ++ i ) {

		#ifdef DEBUGGING
		cout << "canJumpUpRight: i: " << i << endl;
		#endif //DEBUGGING

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( tile = this -> getTileUpRight ( tile ) ) ) {

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

			if ( tile -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpUpRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
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
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;
			}

		}

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

bool board::canJumpDownRight ( tile * tile ) {

	orgTile = tile;

	if ( tile -> getContents ( ) == 0 )
		return false;

	for ( int i = 0; tile = this -> getTileDownRight ( tile ); ++ i ) {

		#ifdef DEBUGGING
		cout << "canJumpDownRight: i: " << i << endl;
		#endif //DEBUGGING

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( tile = this -> getTileDownRight ( tile ) ) ) {

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

			if ( tile -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpDownRight: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
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
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

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

bool board::canJumpLeft ( tile * tile ) {

	orgTile = tile;

	if ( tile -> getContents ( ) == 0 )
		return false;

	for ( int i = 0; tile = this -> getTileLeft ( tile ); ++ i ) {

		#ifdef DEBUGGING
		cout << "canJumpLeft: i: " << i << endl;
		#endif //DEBUGGING

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( tile = this -> getTileLeft ( tile ) ) ) {

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

			if ( tile -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
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
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

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

bool board::canJumpUpLeft ( tile * tile ) {

	orgTile = tile;

	if ( tile -> getContents ( ) == 0 )
		return false;

	for ( int i = 0; tile = this -> getTileUpLeft ( tile ); ++ i ) {

		#ifdef DEBUGGING
		cout << "canJumpUpLeft: i: " << i << endl;
		#endif //DEBUGGING

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( tile = this -> getTileUpLeft ( tile ) ) ) {

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

			if ( tile -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpUpLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", " << orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
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
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;

			}

		}

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

bool board::canJumpDownLeft ( tile * tile ) {

	orgTile = tile;

	#ifdef DEBUGGING
	cout << "Can " << tile << " jump DownLeft?\n";
	#endif //DEBUGGING

	if ( tile -> getContents ( ) == 0 )
		return false;

	for ( int i = 0; tile = this -> getTileDownLeft ( tile ); ++ i ) {

		#ifdef DEBUGGING
		cout << "canJumpDownLeft: i: " << i << endl;
		#endif //DEBUGGING

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( tile = this -> getTileDownLeft ( tile ) ) ) {

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

			if ( tile -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpDownLeft: ["
					<< orgTile -> getCoordinates ( ).first
					<< ", "
					<< orgTile -> getCoordinates ( ).second
					<< "] can end jump at ["
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
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
					<< tile -> getCoordinates ( ).first
					<< ", "
					<< tile -> getCoordinates ( ).second
					<< "]\n";
				#endif //DEBUGGING

				return false;
			}

		}

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
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkUpRight ( tile * t ) {
	if ( this -> canWalkUpRight ( t ) ) {
		this -> getTileUpRight ( t ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkDownRight ( tile * t ) {
	if ( this -> canWalkDownRight ( t ) ) {
		this -> getTileDownRight ( t ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkLeft ( tile * t ) {
	if ( this -> canWalkLeft ( t ) ) {
		this -> getTileLeft ( t ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkUpLeft ( tile * t ) {
	if ( this -> canWalkUpLeft ( t ) ) {
		this -> getTileUpLeft ( t ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkDownLeft ( tile * t ) {
	if ( this -> canWalkDownLeft ( t ) ) {
		this -> getTileDownLeft ( t ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpRight ( tile * t ) {
	if ( this -> canJumpRight ( t ) ) {
		this -> getTile ( this -> getCoordJumpRight ( t ) ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpUpRight ( tile * t ) {
	if ( this -> canJumpUpRight ( t ) ) {
		this -> getTile ( this -> getCoordJumpUpRight ( t ) ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpDownRight ( tile * t ) {
	if ( this -> canJumpDownRight ( t ) ) {
		this -> getTile ( this -> getCoordJumpDownRight ( t ) ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpLeft ( tile * t ) {
	if ( this -> canJumpLeft ( t ) ) {
		this -> getTile ( this -> getCoordJumpLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpUpLeft ( tile * t ) {
	if ( this -> canJumpUpLeft ( t ) ) {
		this -> getTile ( this -> getCoordJumpUpLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpDownLeft ( tile * t ) {
	if ( this -> canJumpDownLeft ( t ) ) {
		this -> getTile ( this -> getCoordJumpDownLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		t -> setContents ( 0 );
		return true;
	} else return false;
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

	vector < board_move > r;

	if ( ! this -> isValidTile ( t ) )
		return r;

	if ( t -> getContents ( ) == 0 )
		return r;

	board_move m;

	m.setTileStartCoords ( t -> getCoordinates ( ) );

	for ( int i = 0; i < 12; ++ i ) {
		if ( this -> canMove ( t, i + 1 ) ) {
			m.setRawData ( i + 1 );
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

bool board::canMakeTurn ( board_turn t ) {

	for ( int i = 0; i < t.moves.size ( ); ++ i ){

	}

}

bool board::makeTurn ( board_turn t ) {

	for ( int i = 0; i < t.moves.size ( ); ++ i ) {

	}

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

			tb2 [ pii2.second ] [ pii2.first ].updateCoordinates ( pii2.second, pii2.first );
			tb2 [ pii2.second ] [ pii2.first ].setContents ( tb [ i ] [ j ].getContents ( ) );

		}

	}

	/* Save board changes */

	for ( int i = 0; i < this -> tb.size ( ); ++ i ) {
		for ( int j = 0; j < this -> tb [ i ].size ( ); ++ j )
			this -> tb [ i ] [ j ] = tb2 [ i ] [ j ];
	}

	for ( int i = 0; i < nests.size ( ); ++ i ) {
		nests [ i ].clear ( );
	}

	for ( int i = 0; i < playerTiles.size ( ); ++ i ) {
		playerTiles [ i ].clear ( );
	}

	for ( int i = 0; i < tb.size ( ); ++ i ) {

		for ( int j = 0; j < tb [ i ].size ( ); ++ j ) {

			pair < int, int > pii;
			pii.first = j;
			pii.second = i;

			tile * t = this -> getTile ( rotationMap [ pii ] );

			this -> nests [ t -> getContents ( ) ].push_back ( t );
			this -> playerTiles [ t -> getContents ( ) ].push_back ( t );

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
