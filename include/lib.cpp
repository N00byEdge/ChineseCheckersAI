#include <lib.h>

map < pair < int, int >, pair < int, int > > coordTranslationTable;

bool translationTableGenerated = false;

void addMap ( int i1, int i2, int i3, int i4 ) {

	pair < int, int > pii1, pii2;

	pii1.first = i1;
	pii1.second = i2;
	pii2.first = i3;
	pii2.second= i4;

	coordTranslationTable [ pii1 ] = pii2;

}

int lib::charToInt ( char c ) {
	return int ( c - 48 );
}

void generateCoordTranslationTable ( ) {

	if ( translationTableGenerated )
		return;

	translationTableGenerated = true;

	// center tile

	addMap ( 4, 8, 4, 8 );

	// tiles 1 tile from center

	addMap ( 5, 8, 5, 7 );
	addMap ( 5, 7, 4, 7 );
	addMap ( 4, 7, 3, 8 );
	addMap ( 3, 8, 4, 9 );
	addMap ( 4, 9, 5, 9 );
	addMap ( 5, 9, 5, 8 );

	// tiles 2 tiles from center

	addMap ( 6, 8, 6, 6 );
	addMap ( 6, 7, 5, 6 );

	addMap ( 6, 6, 4, 6 );
	addMap ( 5, 6, 3, 7 );

	addMap ( 4, 6, 2, 8 );
	addMap ( 3, 7, 3, 9 );

	addMap ( 2, 8, 4, 10 );
	addMap ( 3, 9, 5, 10 );

	addMap ( 4, 10, 6, 10 );
	addMap ( 5, 10, 6, 9 );

	addMap ( 6, 10, 6, 8);
	addMap ( 6, 9, 6, 7);

	// tiles 3 tiles from center

	addMap ( 7, 8, 7, 5 );
	addMap ( 7, 7, 6, 5 );
	addMap ( 7, 6, 5, 5 );

	addMap ( 7, 5, 4, 5);
	addMap ( 6, 5, 3, 6 );
	addMap ( 5, 5, 2, 7 );

	addMap ( 4, 5, 1, 8 );
	addMap ( 3, 6, 2, 9 );
	addMap ( 2, 7, 3, 10 );

	addMap ( 1, 8, 4, 11 );
	addMap ( 2, 9, 5, 11 );
	addMap ( 3, 10, 6, 11 );

	addMap ( 4, 11, 7, 11 );
	addMap ( 5, 11, 7, 10 );
	addMap ( 6, 11, 7, 9 );

	addMap ( 7, 11, 7, 8 );
	addMap ( 7, 10, 7, 7 );
	addMap ( 7, 9, 7, 6 );

	// tiles 4 tiles from center

	addMap ( 8, 8, 8, 4 );
	addMap ( 8, 7, 7, 4 );
	addMap ( 8, 6, 6, 4 );
	addMap ( 8, 5, 5, 4 );

	addMap ( 8, 4, 4, 4 );
	addMap ( 7, 4, 3, 5 );
	addMap ( 6, 4, 2, 6 );
	addMap ( 5, 4, 1, 7 );

	addMap ( 4, 4, 0, 8 );
	addMap ( 3, 5, 1, 9 );
	addMap ( 2, 6, 2, 10 );
	addMap ( 1, 7, 3, 11 );

	addMap ( 0, 8, 4, 12 );
	addMap ( 1, 9, 5, 12 );
	addMap ( 2, 10, 6, 12 );
	addMap ( 3, 11, 7, 12 );

	addMap ( 4, 12, 8, 12 );
	addMap ( 5, 12, 8, 11 );
	addMap ( 6, 12, 8, 10 );
	addMap ( 7, 12, 8, 9 );

	addMap ( 8, 12, 8, 8 );
	addMap ( 8, 11, 8, 7 );
	addMap ( 8, 10, 8, 6 );
	addMap ( 8, 9, 8, 5 );

	// tiles 5 tiles from center

	addMap ( 9, 7, 3, 3 );
	addMap ( 9, 6, 2, 3 );
	addMap ( 9, 5, 1, 3 );
	addMap ( 9, 4, 0, 3 );

	addMap ( 3, 3, 3, 4 );
	addMap ( 2, 3, 2, 5 );
	addMap ( 1, 3, 1, 6 );
	addMap ( 0, 3, 0, 7 );

	addMap ( 3, 4, 0, 9 );
	addMap ( 2, 5, 1, 10 );
	addMap ( 1, 6, 2, 11 );
	addMap ( 0, 7, 3, 12 );

	addMap ( 0, 9, 0, 13 );
	addMap ( 1, 10, 1, 13 );
	addMap ( 2, 11, 2, 13 );
	addMap ( 3, 12, 3, 13 );

	addMap ( 0, 13, 9, 12 );
	addMap ( 1, 13, 9, 11 );
	addMap ( 2, 13, 9, 10 );
	addMap ( 3, 13, 9, 9 );

	addMap ( 9, 12 , 9, 7 );
	addMap ( 9, 11, 9, 6 );
	addMap ( 9, 10, 9, 5 );
	addMap ( 9, 9, 9, 4 );

	// tiles 6 tiles from center

	addMap ( 10, 6, 2, 2 );
	addMap ( 10, 5, 1, 2 );
	addMap ( 10, 4, 0, 2 );

	addMap ( 2, 2, 2, 4 );
	addMap ( 1, 2, 1, 5 );
	addMap ( 0, 2, 0, 6 );

	addMap ( 2, 4, 0, 10 );
	addMap ( 1, 5, 1, 11 );
	addMap ( 0, 6, 2, 12 );

	addMap ( 0, 10, 0, 14 );
	addMap ( 1, 11, 1, 14 );
	addMap ( 2, 12, 2, 14 );

	addMap ( 0, 14, 10, 12 );
	addMap ( 1, 14, 10, 11 );
	addMap ( 2, 14, 10, 10 );

	addMap ( 10, 12, 10, 6 );
	addMap ( 10, 11, 10, 5 );
	addMap ( 10, 10, 10, 4 );

	//tiles 7 tiles from center

	addMap ( 11, 5, 1, 1 );
	addMap ( 11, 4, 0, 1 );

	addMap ( 1, 1, 1, 4 );
	addMap ( 0, 1, 0, 5 );

	addMap ( 1, 4, 0, 11 );
	addMap ( 0, 5, 1, 12 );

	addMap ( 0, 11, 0, 15 );
	addMap ( 1, 12, 1, 15 );

	addMap ( 0, 15, 11, 12 );
	addMap ( 1, 15, 11, 11 );

	addMap ( 11, 12, 11, 5 );
	addMap ( 11, 11, 11, 4 );

	//outer tiles

	addMap ( 12, 4, 0, 0 );
	addMap ( 0, 0, 0, 4 );
	addMap ( 0, 4, 0, 12 );
	addMap ( 0, 12, 0, 16 );
	addMap ( 0, 16, 12, 12 );
	addMap ( 12, 12, 12, 4 );

}

map < pair < int, int >, pair < int, int > > lib::getCoordTranslationTable ( ) {

	if ( !translationTableGenerated )
		generateCoordTranslationTable ( );

	return coordTranslationTable;

}