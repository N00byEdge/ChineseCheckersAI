#include "board.h"

tile * originalTile;
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

{"1", // 16
"11", // 15
"111", // 14
"1111", // 13
"0000000000000", // 12
"000000000000", // 11
"00000000000", // 10
"0000000000", // 9
"000000000", // 8
"0000000000", // 7
"00000000000", // 6
"000000000000", // 5
"0000000000000", // 4
"2222", // 3
"222", // 2
"22", // 1
"2"}; // 0

vector < string > Board4Players =

{"1", // 16
"11", // 15
"111", // 14
"1111", // 13
"3333000000000", // 12
"333000000000", // 11
"33000000000", // 10
"3000000000", // 9
"000000000", // 8
"0000000004", // 7
"00000000044", // 6
"000000000444", // 5
"0000000004444", // 4
"2222", // 3
"222", // 2
"22", // 1
"2"}; // 0

vector < string > Board6Players =

{"1", // 16
"11", // 15
"111", // 14
"1111", // 13
"3333000006666", // 12
"333000000666", // 11
"33000000066", // 10
"3000000006", // 9
"000000000", // 8
"5000000004", // 7
"55000000044", // 6
"555000000444", // 5
"5555000004444", // 4
"2222", // 3
"222", // 2
"22", // 1
"2"}; // 0

/*
14	            2
13	           2 2
12	          2 2 2
11	         2 2 2 2
10	0 0 0 0 0 0 0 0 0 0 0 0 0
9	 0 0 0 0 0 0 0 0 0 0 0 0
8	  0 0 0 0 0 0 0 0 0 0 0
7	   0 0 0 0 0 0 0 0 0 0
6	  0 0 0 0 0 0 0 0 0 0 0
5	 0 0 0 0 0 0 0 0 0 0 0 0
4	0 0 0 0 0 0 0 0 0 0 0 0 0
3	         1 1 1 1
2	          1 1 1
1	           1 1
0	            1
*/

/*
 *  Reset the board to a empty board. A good idea after creating a board object, but not required as you may have a template. If you are not copying a board, always reset it.
 *  Set numPlayers first, as the new board state depends on the number of players.
 */

void board::print ( ) {

	for ( int i = tb.size ( ) - 1; i != -1; -- i ) {
    cout << i << "\t ";
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

		for ( int j = 0; j < tb [ i ].size ( ); ++ j )

			cout << tb [ i ] [ j ]. getContents ( ) << " ";

		cout << endl;

	}
	cout<<flush<<endl;

}

void board::printWithCoords ( ) {

	for ( int i = tb.size ( ) - 1; i != -1; -- i ) {

		for ( int j = 0; j < tb [ i ].size ( ); ++ j ) {

			pair < int, int > coords = tb [ i ] [ j ].getCoordinates ( );

			cout << "[" << tb [ i ] [ j ].getCoordinates ( ).first << ", " << tb [ i ] [ j ].getCoordinates ( ).second << "]" << tb [ i ] [ j ]. getContents ( );

		}

		cout << endl;

	}

}

void board::resetBoard ( int numPlayers ) {

	/* If the number of players is not equal to 2, 3, 4 or 6, we are going to use 2 players. */
	if( !( numPlayers == 2 || numPlayers == 4 || numPlayers == 6 ) ) numPlayers = 2;

	/* Sets the board to an empty board, defined at the top. */
	if ( numPlayers == 2 ) { board::setBoard ( Board2Players, 2 ); numPlayers = 2; }
	else if ( numPlayers == 4 ) { board::setBoard ( Board4Players, 4 ); numPlayers = 4; }
	else if ( numPlayers == 6 ) { board::setBoard ( Board6Players, 6 ); numPlayers = 6; }
	else { board::setBoard ( Board2Players, 2 ); numPlayers = 2; }

	this -> numPlayers = numPlayers;

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

	b = board;

	vector < tile > emptyTileVector;
	vector < tile * > emptyTilePointerVector;

	for ( int i = 0; i < numPlayers + 1; ++ i ) {

		nests.push_back ( emptyTilePointerVector );
		playerTiles.push_back ( emptyTilePointerVector );

	}

	for ( int i = board.size ( ) - 1; i != - 1; -- i ) {

		tb.push_back ( emptyTileVector );

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

			tb [ tb.size ( ) - 1 ].push_back ( t );

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

			tile * t = getTile ( pii );

			nests [ t -> getContents ( ) ].push_back ( t );
			playerTiles [ t -> getContents ( ) ].push_back ( t );

		}

	}

	#ifdef DEBUGGING
	cout << "Resorting list.\n";
	#endif // DEBUGGING

	reverse ( tb.begin ( ), tb.end ( ) );

	#ifdef DEBUGGING
	cout << "Finished setting board state.\n";
	#endif // DEBUGGING
}

tile * board::getTile ( pair < int, int > pii ) {

	//tile t ( pii.first, pii.second, 0 );
	if ( isValidTile ( pii ) )
		return & ( tb [ pii.second ] [ pii.first ] );
	else return nullptr;

}

tile * board::intToTile ( int in ) {

    if ( in <= 121 ) {

        for ( int i = 0; i < this -> tb.size ( ); ++ i ) {

            if ( in < this -> tb [ i ].size ( ) )
                return & this -> tb [ i ] [ in ];
            else in -= this -> tb [ i ].size ( );

        }

    }

}

int board::tileToInt ( tile * t ) {

    int r = 0;

    for ( int i = 0; i < t -> getCoordinates ( ).second; ++ i )
        r += this -> tb [ i ].size ( );
    r += t -> getCoordinates ( ).first;

    return r;

}

bool board::isValidTile ( pair < int, int > pii ) {

	#ifdef DEBUGGING
	//cout << "Is [" << pii.first << ", " << pii.second << "] a valid tile?\n";
	#endif // DEBUGGING

	if ( pii.second < tb.size ( ) && - 1 < pii.second ) {

		if ( pii.first < tb [ pii.second ]. size ( )  && - 1 < pii.first ) {

			#ifdef DEBUGGING
			//cout << "We have reason to believe that this tile is valid.\n";
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

	//cout << "Is " << t << " a valid tile?\n";

	/*if ( isValidTile( t -> getCoordinates ( ) ) ) {
		cout << t << " has coordinates [" << t -> getCoordinates ( ).first << ", " << t -> getCoordinates ( ).second << "]\n";
	} else {
		cout << t << "did not have valid coordinates.\n";
	}*/

	#endif // DEBUGGING

	return isValidTile ( t -> getCoordinates ( ) );

}

vector < tile * > board::getPlayerTiles ( int player ) {

    vector < tile * > playerTiles;

	/*playerTiles.clear ( );
	for ( int i = 0; i < player + 1; ++ i )
        playerTiles.push_back ( staticEmptyTilePointerVector );*/

	for ( int i = 0; i < tb.size ( ); ++ i ) {

		for ( int j = 0; j < tb [ i ].size ( ); ++ j ) {

			pair < int, int > pii;
			pii.first = j;
			pii.second = i;

            tile * t = getTile ( pii );

			//nests [ t -> getContents ( ) ].push_back ( t );
			if ( t -> getContents ( ) == player )
                playerTiles.push_back ( t );

		}

	}

	if ( player < playerTiles.size ( ) )
		return playerTiles;
    return *new vector < tile * >;

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

	if ( isValidTile ( t ) )
		return t;

}

tile * board::getTileRight ( tile * t ) {

	t = getTile ( getCoordRight ( t ) );

	if( isValidTile ( t ) )
		return t;
    return nullptr;

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

	t = getTile ( getCoordUpRight ( t ) );

	if( isValidTile ( t ) )
		return t;
    return nullptr;

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

	t = getTile ( getCoordDownRight ( t ) );

	if( isValidTile ( t ) )
		return t;
    return nullptr;

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

	t = getTile ( getCoordLeft ( t ) );

	if( isValidTile ( t ) )
		return t;
    return nullptr;

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

	t = getTile ( getCoordUpLeft ( t ) );

	if( isValidTile ( t ) )
		return t;
    return nullptr;

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

	t = getTile ( getCoordDownLeft ( t ) );

	if( isValidTile ( t ) )
		return t;
    return nullptr;

}

bool board::canWalkRight ( tile * t ) {

	#ifdef DEBUGGING
	//cout << "Can " << t << " walk right?\n";
	#endif // DEBUGGING

	tile * tRight;

	if ( getTileRight( t ) ){

		tRight = getTileRight( t );

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
	//cout << "Can " << t << " walk upRight?\n";
	#endif // DEBUGGING

	tile * tUpRight;

	if ( getTileUpRight( t ) ){

		tUpRight = getTileUpRight( t );

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
	//cout << "Can " << t << " walk downRight?\n";
	#endif // DEBUGGING

	tile * tDownRight;

	if ( getTileDownRight( t ) ){

		tDownRight = getTileDownRight( t );

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
	//cout << "Can " << t << " walk left?\n";
	#endif // DEBUGGING

	tile * tLeft;

	if ( getTileLeft( t ) ){

		tLeft = getTileLeft( t );

		if ( tLeft == nullptr ) {

			#ifdef DEBUGGINGn
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
	//cout << "Can " << t << " walk upLeft?\n";
	#endif // DEBUGGING

	tile * tUpLeft;

	if ( getTileUpLeft( t ) ){

		tUpLeft = getTileUpLeft( t );

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
	//cout << "Can " << t << " walk downLeft?\n";
	#endif // DEBUGGING

	tile * tDownLeft;

	if ( getTileDownLeft( t ) ){

		tDownLeft = getTileDownLeft( t );

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

    if ( !isValidTile ( t ) )
        return false;

	originalTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = getTileRight ( t ) ); ++ i ) {

		if ( t == lastTile )
			break;

		if ( !isValidTile ( t ) )
			return false;

		#ifdef DEBUGGING
		cout << "canJumpRight: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = getTileRight ( t ) ) && t != nullptr ) {


					#ifdef DEBUGGING
					cout << "canJumpRight: ["
						<< originalTile -> getCoordinates ( ).first
						<< ", "
						<< originalTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

				if ( t -> getContents ( ) != 0 )
					return false;

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpRight: ["
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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

	for ( int i = 0; tile = getTileRight ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = getTileRight ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpUpRight ( tile * t ) {

    if ( !isValidTile ( t ) )
        return false;

	originalTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = getTileUpRight ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpUpRight: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = getTileUpRight ( t ) ) && t != nullptr ) {


					#ifdef DEBUGGING
					cout << "canJumpUpRight: ["
						<< originalTile -> getCoordinates ( ).first
						<< ", "
						<< originalTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

				if ( t -> getContents ( ) != 0 )
					return false;

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpUpRight: ["
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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

	for ( int i = 0; tile = getTileUpRight ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = getTileUpRight ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpDownRight ( tile * t ) {

    if ( !isValidTile ( t ) )
        return false;

	originalTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = getTileDownRight ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpDownRight: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = getTileDownRight ( t ) ) && t != nullptr  && t -> getContents ( ) == 0 ) {


					#ifdef DEBUGGING
					cout << "canJumpDownRight: ["
						<< originalTile -> getCoordinates ( ).first
						<< ", "
						<< originalTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

				if ( t -> getContents ( ) != 0 )
					return false;

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpDownRight: ["
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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

	for ( int i = 0; tile = getTileDownRight ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = getTileDownRight ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpLeft ( tile * t ) {

    if ( !isValidTile ( t ) )
        return false;

	originalTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = getTileLeft ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpLeft: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = getTileLeft ( t ) ) && t != nullptr ) {


					#ifdef DEBUGGING
					cout << "canJumpLeft: ["
						<< originalTile -> getCoordinates ( ).first
						<< ", "
						<< originalTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

				if ( t -> getContents ( ) != 0 )
					return false;

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpLeft: ["
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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

	for ( int i = 0; tile = getTileLeft ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = getTileLeft ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpUpLeft ( tile * t ) {

    if ( !isValidTile ( t ) )
        return false;

	originalTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = getTileUpLeft ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpUpLeft: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = getTileUpLeft ( t ) ) && t != nullptr ) {


					#ifdef DEBUGGING
					cout << "canJumpUpLeft: ["
						<< originalTile -> getCoordinates ( ).first
						<< ", "
						<< originalTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

				if ( t -> getContents ( ) != 0 )
					return false;

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpUpLeft: ["
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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

	for ( int i = 0; tile = getTileUpLeft ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = getTileUpLeft ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canJumpDownLeft ( tile * t ) {

    if ( !isValidTile ( t ) )
        return false;

	originalTile = t;

	if ( t -> getContents ( ) == 0 )
		return false;

	tile * lastTile = t;

	for ( int i = 0; ( t = getTileDownLeft ( t ) ) && t != nullptr; ++ i ) {

		if ( t == lastTile )
			break;

		#ifdef DEBUGGING
		cout << "canJumpDownLeft: i: " << i << " t: " << t << endl;
		#endif //DEBUGGING

		if ( 1 <= t -> getContents ( ) && t -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j ) {

				if ( ! ( t = getTileDownLeft ( t ) ) && t != nullptr ) {


					#ifdef DEBUGGING
					cout << "canJumpDownLeft: ["
						<< originalTile -> getCoordinates ( ).first
						<< ", "
						<< originalTile -> getCoordinates ( ).second
						<< "]: could not find a piece to jump over.\n";
					#endif //DEBUGGING

					return false;
				}

				if ( t -> getContents ( ) != 0 )
					return false;

			}

			if ( t -> getContents ( ) == 0 ) {

				#ifdef DEBUGGING
				cout << "canJumpDownLeft: ["
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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
					<< originalTile -> getCoordinates ( ).first
					<< ", "
					<< originalTile -> getCoordinates ( ).second
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

	for ( int i = 0; tile = getTileDownLeft ( tile ); ++ i ) {

		if ( 1 <= tile -> getContents ( ) && tile -> getContents ( ) <= 6 ) {

			for ( int j = - 1; j < i; ++ j )
				tile = getTileDownLeft ( tile );

			return tile -> getCoordinates ( );

		}

	}

}

bool board::canWalk ( tile * t, unsigned int direction ) {

    if ( direction == 1 )
		return canWalkRight ( t );

	else if ( direction == 2 )
		return canWalkDownRight ( t );

	else if ( direction == 3 )
		return canWalkDownLeft ( t );

	else if ( direction == 4 )
		return canWalkLeft ( t );

	else if ( direction == 5 )
		return canWalkUpLeft ( t );

	else if ( direction == 6 )
		return canWalkUpRight ( t );

	else
		return false;

}

bool board::canJump ( tile * t, unsigned int direction ) {

	if ( direction == 1 )
		return canJumpRight ( t );

	else if ( direction == 2 )
		return canJumpDownRight ( t );

	else if ( direction == 3 )
		return canJumpDownLeft ( t );

	else if ( direction == 4 )
		return canJumpLeft ( t );

	else if ( direction == 5 )
		return canJumpUpLeft ( t );

	else if ( direction == 6 )
		return canJumpUpRight ( t );

	else
		return false;

}

bool board::canMove ( tile * t, unsigned int move ) {

    #ifdef DEBUGGING
    cout << "Can " << t << " move " << move << "?\n";
    #endif // DEBUGGING

	if ( 1 <= move && move <= 6 )
		return canWalk ( t, move );
	else if ( 7 <= move && move <= 12 )
		return canJump ( t, move - 6 );
	else
		return false;
}

bool board::canMove ( board_move m ) {

	tile * t;

	if ( t = getTile ( m.getTileStartCoords ( ) ) )
		return canMove ( getTile ( m.getTileStartCoords ( ) ), m.getRawData ( ) );

	return false;
}

bool board::walkRight ( tile * t ) {
	if ( canWalkRight ( t ) ) {
		getTileRight ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTileRight ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkUpRight ( tile * t ) {
	if ( canWalkUpRight ( t ) ) {
		getTileUpRight ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTileUpRight ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkDownRight ( tile * t ) {
	if ( canWalkDownRight ( t ) ) {
		getTileDownRight ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTileDownRight ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkLeft ( tile * t ) {
	if ( canWalkLeft ( t ) ) {
		getTileLeft ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTileLeft ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkUpLeft ( tile * t ) {
	if ( canWalkUpLeft ( t ) ) {
		getTileUpLeft ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTileUpLeft ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::walkDownLeft ( tile * t ) {
	if ( canWalkDownLeft ( t ) ) {
		getTileDownLeft ( t ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTileDownLeft ( t );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpRight ( tile * t ) {
	if ( canJumpRight ( t ) ) {
		getTile ( getCoordJumpRight ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTile ( getCoordJumpRight ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpUpRight ( tile * t ) {
	if ( canJumpUpRight ( t ) ) {
		getTile ( getCoordJumpUpRight ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
                if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTile ( getCoordJumpUpRight ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpDownRight ( tile * t ) {
	if ( canJumpDownRight ( t ) ) {
		getTile ( getCoordJumpDownRight ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTile ( getCoordJumpDownRight ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpLeft ( tile * t ) {
	if ( canJumpLeft ( t ) ) {
		getTile ( getCoordJumpLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTile ( getCoordJumpLeft ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpUpLeft ( tile * t ) {
	if ( canJumpUpLeft ( t ) ) {
		getTile ( getCoordJumpUpLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTile ( getCoordJumpUpLeft ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

bool board::jumpDownLeft ( tile * t ) {
	if ( canJumpDownLeft ( t ) ) {
		getTile ( getCoordJumpDownLeft ( t ) ) -> setContents ( t -> getContents ( ) );
		for ( int i = 0; i < 10; ++ i ) {
			if ( playerTiles [ t -> getContents ( ) ] [ i ] == t )
				playerTiles [ t -> getContents ( ) ] [ i ] = getTile ( getCoordJumpDownLeft ( t ) );
		}
		t -> setContents ( 0 );
		return true;
	} else return false;
}

pair < int, int > board::getWalkCoords ( tile * t, unsigned int direction ) {

	switch ( direction ) {

		case 1:
			return getCoordRight ( t );

		case 2:
			return getCoordDownRight ( t );

		case 3:
			return getCoordDownLeft ( t );

		case 4:
			return getCoordLeft ( t );

		case 5:
			return getCoordUpLeft ( t );

		case 6:
			return getCoordUpRight ( t );

	}
}

pair < int, int > board::getJumpCoords ( tile * t, unsigned int direction ) {

	switch ( direction ) {

		case 1:
			return getCoordJumpRight ( t );

		case 2:
			return getCoordJumpDownRight ( t );

		case 3:
			return getCoordJumpDownLeft ( t );

		case 4:
			return getCoordJumpLeft ( t );

		case 5:
			return getCoordJumpUpLeft ( t );

		case 6:
			return getCoordJumpUpRight ( t );

	}
}

pair < int, int > board::getMoveCoords ( board_move m ) {

	if ( 1 <= m.getRawData ( ) && m.getRawData ( ) <= 6 )
		return getWalkCoords ( getTile ( m.getTileStartCoords ( ) ), m.getRawData ( ) );
	else if ( 7 <= m.getRawData ( ) && m.getRawData ( ) <= 12 )
		return getJumpCoords ( getTile ( m.getTileStartCoords ( ) ), m.getRawData ( ) - 6 );

}

pair < int, int > board::getTurnCoords ( board_turn t ) {

    board dummyBoard = * this;

    auto t2 = t;
    t2.moves.erase ( t2.moves.begin ( ) + t2.moves.size ( ) - 1 );

    dummyBoard.makeTurn ( t2 );
    return dummyBoard.getMoveCoords ( t.moves [ t.moves.size ( ) - 1 ] );

}

bool board::walk ( tile * t, unsigned int direction ) {

	switch ( direction ) {

		case 1:
			return walkRight ( t );

		case 2:
			return walkDownRight ( t );

		case 3:
			return walkDownLeft ( t );

		case 4:
			return walkLeft ( t );

		case 5:
			return walkUpLeft ( t );

		case 6:
			return walkUpRight ( t );

		default:
			return false;
	}

}

bool board::jump ( tile * t, unsigned int direction ) {

	switch ( direction ) {

		case 1:
			return jumpRight ( t );

		case 2:
			return jumpDownRight ( t );

		case 3:
			return jumpDownLeft ( t );

		case 4:
			return jumpLeft ( t );

		case 5:
			return jumpUpLeft ( t );

		case 6:
			return jumpUpRight ( t );

		default:
			return false;
	}

}

bool board::move ( tile * t, unsigned int move ) {
	if ( 1 <= move && move <= 6 )
		return walk ( t, move );
	else if ( 7 <= move && move <= 12 )
		return jump ( t, move - 6 );
	else
		return false;
}

bool board::move ( board_move m ) {
	return move ( getTile ( m.getTileStartCoords ( ) ), m.getRawData ( ) );
}

vector < board_move > board::getPossibleMoves ( tile * t ) {

	#ifdef DEBUGGING
	cout << "getPossibleMoves: " << t << endl;
	#endif //DEBUGGING

	vector < board_move > r;

	if ( ! isValidTile ( t ) )
		return r;

	if ( t -> getContents ( ) == 0 )
		return r;

	board_move m;

	m.setTileStartCoords ( t -> getCoordinates ( ) );

	for ( int i = 1; i <= 12; ++ i ) {
		if ( canMove ( t, i ) ) {
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

			vector < board_move > temp = getPossibleMoves ( & tb [ i ] [ j ] );

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
		return move ( trn.moves [ 0 ] );

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
		if ( trn.moves [ i + 1 ].getTileStartCoords ( ) != dummyBoard.getMoveCoords ( trn.moves [ i ] ) )
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
	print ( );
	#endif //DEBUGGING

	auto rotationMap = lib::getCoordTranslationTable ( );

	pair < int, int > pii1, pii2;

	auto tb2 = tb;

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

	for ( int i = 0; i < tb.size ( ); ++ i ) {
		for ( int j = 0; j < tb [ i ].size ( ); ++ j )
			tb [ i ] [ j ] = tb2 [ i ] [ j ];
	}

	for ( int i = 0; i < playerTiles.size ( ); ++ i ) {

		for ( int j = 0; j < playerTiles [ i ].size ( ); ++ j ) {

			playerTiles [ i ] [ j ] = getTile ( rotationMap [ playerTiles [ i ] [ j ] -> getCoordinates ( ) ] );

		}

	}

	for ( int i = 0; i < nests.size ( ); ++ i ) {

		for ( int j = 0; j < nests [ i ].size ( ); ++ j ) {

			nests [ i ] [ j ] = getTile ( rotationMap [ nests [ i ] [ j ] -> getCoordinates ( ) ] );

		}

	}

	#ifdef DEBUGGING
	cout << "Rotated board:\n";
	print ( );
	#endif //DEBUGGING

}

void board::rotate ( int steps ) {

	for ( int i = 0; i < steps % 6; ++ i )
		rotate ( );

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
				<< deb ( nests [ player ] [ 0 ] -> getCoordinates ( ).second )
				<< endl;
			#endif //DEBUGGING

			rotate ( );
			++ rotations;

		}

	}

	return rotations;

}

float board::getMiddleXCoord ( int y ) {

	return ( float ) tb [ y ].size ( ) / 2.0f - 0.5f;

}

vector < board_turn > board::findAllPossibleTurns ( tile * t, vector < board_move > moves, vector < bool > visited ) {

    vector < board_turn > allPossibleTurns;

	auto possibleMoves = getPossibleMoves ( t );

	for ( int i = 0; i < possibleMoves.size ( ); ++ i ) {

		if ( 0 < moves.size ( ) ) {

            if ( possibleMoves [ i ].getRawData ( ) <= 6 || moves [ moves.size ( ) - 1 ].getRawData ( ) <= 6 )
                goto nomove;

		}

		if ( canMove ( possibleMoves [ i ] ) ) {


            if ( visited  [ tileToInt ( getTile ( getMoveCoords ( possibleMoves [ i ] ) ) ) ] )
                goto nomove;

			board_move mv;
			mv = possibleMoves [ i ];
			moves.push_back ( mv );

			board_turn trn;
			trn.moves = moves;
			allPossibleTurns.push_back ( trn );

			visited [ tileToInt ( getTile ( getMoveCoords ( possibleMoves [ i ] ) ) ) ] = true;
			//visitedCoords.push_back ( getMoveCoords ( possibleMoves [ i ] ) );
			tile * originalTile = t;
			t = getTile ( getMoveCoords ( mv ) );
			board originalBoard = *this;
			move ( mv );
			board b = *this;
			auto w = b.findAllPossibleTurns ( t, moves, visited );
			b = originalBoard;
			t = originalTile;

			for ( int k = 0; k < w.size ( ); ++ k )
                allPossibleTurns.push_back ( w [ k ] );

			moves.erase ( moves.end ( ) - 1 );
			visited [ tileToInt ( getTile ( getMoveCoords ( possibleMoves [ i ] ) ) ) ] = false;

		}

		nomove:
		if ( 5 ) { }

	}

	return allPossibleTurns;

}

float board::score ( int player ) {
	float score = 0;

	for ( int i = 0; i < getPlayerTiles ( player ).size ( ); ++ i ) {

		tile * t = getPlayerTiles ( player ) [ i ];
		int x = t -> getCoordinates ( ).first;
		int y = t -> getCoordinates ( ).second;

		int h = 17 - y;
		int d = abs ( x - getMiddleXCoord ( y ) );

		score -= h * h * h;
		score -= d * d;

        #ifdef DEBUGGING
		cout << deb ( x ) << ", " << deb ( y ) << ", " << deb ( h ) << ", " << deb ( d ) << "\n";
		#endif

	}

	return score;
}

vector < board_turn > board::findAllPossibleTurns ( int player ) {

	vector < board_turn > allPossibleTurns;

	vector < tile * > playerTiles = this -> getPlayerTiles ( player );

	for ( int i = 0; i < playerTiles.size ( ); ++ i ) {

		vector < board_turn > v = this -> findAllPossibleTurns ( playerTiles [ i ], *new vector < board_move > , *new vector < bool > ( 121, false ) );

		for ( int j = 0; j < v.size ( ); ++ j )
			allPossibleTurns.push_back ( v [ j ] );

	}

	return allPossibleTurns;

}

bool board::hasFilledOpposingNest ( int player ) {

    for ( int i = 0; i < this -> nests [ player ].size ( ); ++ i ) {

        auto coord = this -> nests [ player ] [ i ] -> getCoordinates ( );

        auto tt = lib::getCoordTranslationTable ( );

        for ( int j = 0; j < 3; ++ j )
            coord = tt.at ( coord );

		//cout << deb ( this -> getTile ( coord ) -> getContents ( ) != player ) << endl;

        if ( this -> getTile ( coord ) -> getContents ( ) != player ) return false;

    }

    return true;

}

board_turn board::tilesToTurn ( tile * startTile, tile * endTile ) {

    board_turn t;

    auto possibleTurns = findAllPossibleTurns ( startTile, * new vector < board_move >, * new vector < bool > ( 121 ) );

    for ( size_t i = 0; i < possibleTurns.size ( ); ++ i )
        if ( getTile ( getTurnCoords ( possibleTurns [ i ] ) ) == endTile ) return possibleTurns [ i ];

    return t;

}
