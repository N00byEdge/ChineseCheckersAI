#ifndef LIB
#define LIB

#include <includes.h>

using namespace std;

namespace lib {

	map < pair < int, int >, pair < int, int > > getCoordTranslationTable ( );

    int charToInt ( char );

    int randInt ( );
    int randInt ( int mod );

    long double phi ( long double v );

}

#endif // LIB
