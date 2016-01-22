#include <logger.h>

void logger::logNoEndl ( string s, int loglvl ) {

	if ( loglvl < this -> loglvl )
		return;

	cout << s;

}

void logger::log ( string s, int loglvl ) {

	stringstream ss;

	if ( this -> useTimePrefix ) {

		time_t t = time( NULL );
		struct tm * n = localtime( &t );

		ss
		<< "["
		<< (n -> tm_year + 1900)
		<< "-"
		<< ( n -> tm_mon + 1)
		<< "-"
		<< ( n -> tm_mday )
		<< ", "
		<< n -> tm_hour
		<< ":"
		<< n -> tm_min
		<< ":"
		<< n -> tm_sec
		<< "] ";
	}

	ss << s << endl;

	return logNoEndl ( ss.str ( ).c_str ( ), loglvl );

}

void logging::log ( string s, int loglvl ) {

	for ( int i = 0; i < logging::loggers.size ( ); ++ i ) {

		loggers [ i ].log ( s, loglvl );

	}

}

void logging::logNoEndl ( string s, int loglvl ) {

}
