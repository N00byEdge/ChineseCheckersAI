#pragma once

	#define N_THREADS 32

	#define deb(x) ( #x ) << " = " << ( x )
	/* std universal includes */

	#include <algorithm>
	#include <iostream>
	#include <stdarg.h>
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

	/* SFML universal includes */

	#include <SFML/Graphics.hpp>

	#endif

	/* Game engine universal includes */

	#ifndef LIB
	#include <lib.h>
	#endif

	#define endl "\n"
