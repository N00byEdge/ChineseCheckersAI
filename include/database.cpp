#include "database.h"

map < string, pair < float, int > >::iterator database::find ( string key ) {

	return m.find ( key );

}

bool database::isEnd ( map < string, pair < float, int > >::iterator it ) {

	return it == m.end ( );

}

void database::addToDB ( string key, bool val ) {

	auto it = m.find ( key );
	if ( it == m.end ( ) ) m [ key ] = { val, 1 };
	else it -> second.first = ( float ) ( ( float ) it -> second.second * ( float ) it -> second.first + ( float ) val ) / ( ( float ) ( it -> second.second ++ ) + 1 );

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

void operator+= ( database & dbl, const database & dbr ) {

    for ( auto & itr: dbr.m ) {

        auto itl = dbl.m.find ( itr.first );
        if ( itl == dbl.m.end ( ) ) dbl.m [ itr.first ] = itr.second;
        else {
            itl -> second.first = ( float ) ( itl -> second.first * itl -> second.second + itr.second.first * itr.second.second ) / ( itl -> second.second + itr.second.second );
            itl -> second.second += itr.second.second;
        }

    }

}
