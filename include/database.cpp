#include "database.h"

map < string, pair < float, int > >::iterator database::find ( string key ) {

	return m.find ( key );

}

bool database::isEnd ( map < string, pair < float, int > >::iterator it ) {

	return it == m.end ( );

}

void database::addToDB ( string key, bool val ) {

	map < string, pair < float, int > >::iterator it = m.find ( key );
	if ( it == m.end ( ) ) {

		m [ key ] = { val, 1 };

	} else {

	    it -> second.first = ( float ) ( ( float ) it -> second.second * ( float ) it -> second.first + ( float ) val ) / ( ( float ) it -> second.second + 1 );
	    ++ it -> second.second;

	}

}

float database::chanceToWin ( string key ) {

	auto it = m.find ( key );

	if ( it == m.end ( ) ) return 0.5f;

	else return it -> second.first;

	return 0.5f;

}

ostream & operator<< ( ostream & os, database & db ) {

	for ( auto & it: db.m ) {

		os << it.first << " " << it.second.first << " " << it.second.second << endl;

	}

    return os;

}

istream & operator>> ( istream & is, database & db ) {

	string temp;

    while ( is >> temp ) {

		float f;
		is >> f;

		int i;
		is >> i;

		db.m [ temp ] = { f, i };

	}

	return is;

}
