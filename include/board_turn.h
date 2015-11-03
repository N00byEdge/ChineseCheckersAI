#ifndef BOARD_TURN
#define BOARD_TURN

#include <includes.h>

#include <board_move.h>

/* Board Turn class */
class board_turn {

    public:

        /* Constructor */
        board_turn ( );

        /* Destructor */
        ~board_turn ( );

        /* A vector of moves for the turn */
        vector < board_move > moves;

    protected:

    private:

};

#endif // BOARD_TURN
