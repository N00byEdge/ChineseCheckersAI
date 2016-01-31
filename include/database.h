#pragma once

#include <map>
#include <iostream>

using namespace std;

class database {

    public:

		void addToDB ( string key, bool val );
		map < string, pair < float, int > >::iterator find ( string );
		bool isEnd ( map < string, pair < float, int > >::iterator );
		map < string, pair < float, int > > m;
		float chanceToWin ( string key );

    protected:

    private:

};

ostream & operator<< ( ostream &, database & );
istream & operator>> ( istream &, database & );
void operator+= ( database &, const database & );
