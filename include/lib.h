#ifndef LIB
#define LIB

#include <includes.h>

using namespace std;

namespace lib {

	map < pair < int, int >, pair < int, int > > getCoordTranslationTable ( );

    int charToInt ( char );

    int randInt ( int mod );

}

#endif // LIB
