#ifndef BOARD_MOVE
#define BOARD_MOVE

#include <includes.h>

using namespace std;

class board_move {

    public:

        /* Constructor */
        board_move ( );

        /* Destructor */
        ~board_move ( );

        bool didJump ( );
        bool didWalk ( );

        unsigned int getDirection ( );

        void setRawData ( int );
        int getRawData ( );

        void setTileStartCoords ( pair < int, int > );
        pair < int, int > getTileStartCoords ( );

    protected:

    private:

        pair < int, int > tileStartCoords;
    
        int i = 0;
};

#endif // BOARD_MOVE
