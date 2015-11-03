#ifndef AGENT
#define AGENT

#include <includes.h>

#include <board.h>

class agent {

    public:

        agent ( );

        virtual ~agent ( );

        virtual board_turn doTurn ( board, int );

    protected:

    private:
};

#endif // AGENT
