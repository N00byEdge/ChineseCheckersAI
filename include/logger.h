#ifndef LOGGER
#define LOGGER

#include <includes.h>

class logger {

    public:

        void log ( string s, int loglvl );
        void logNoEndl ( string s, int loglvl );

        void setLogLevel ( int loglvl );
        int getLogLevel ( );

        void setUseTimePrefix ( bool useTimePrefix );
        bool getUseTimePrefix ( );

        void addFileOutput ( string filename );
        void addOstreamOutput ( ostream * );
        void addStringstreamOutput ( stringstream * );

    protected:

    private:

        int loglvl;
        bool useTimePrefix;



};

namespace logging {

    void log ( string s, int loglvl );
    void logNoEndl ( string s, int loglvl );

    vector < logger > loggers;

}

#endif // LOGGER
