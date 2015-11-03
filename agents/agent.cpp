#include "agent.h"

agent::agent ( ) { }

agent::~agent ( ) { }

board_turn agent::doTurn ( board b, int player ) {

    board_turn t;

    cout << "This is not a valid agent, and is meant to be overwritten.\n";

    return t;

}
