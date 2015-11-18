#ifndef INCLUDES
#define INCLUDES

	#define deb(x) ( #x ) << " = " << ( x )
	/* std universal includes */

	#include <algorithm>
	#include <iostream>
	#include <stdlib.h>
	#include <iomanip>
	#include <sstream>
	#include <stdio.h>
	#include <limits>
	#include <string>
	#include <vector>
	#include <cmath>
	#include <map>

	#ifndef NOLIB

	/* Boost universal includes */

	#include <boost/thread.hpp>
	#include <boost/date_time.hpp>

	/* SFML universal includes */

	#include <SFML/Graphics.hpp>

	#endif

	/* Game engine universal includes */

	#ifndef LIB
	#include <lib.h>
	#endif

    #define endl "\n"

#endif // INCLUDES
