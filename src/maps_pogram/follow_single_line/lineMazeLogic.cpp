#include "LineMazeLogic.h"

MazeLogic::MazeLogic(TurnPreference pref)
    : pref(pref) {}

MazeMove MazeLogic::decide(LineState state) {

    if (state == ALL_WHITE)
        return UTURN;

    if (state == ALL_BLACK && pref == RIGHT_FIRST)
        return CROSSING;

    if (state == SLIGHT_LEFT)
        return SOFT_LEFT;

    if (state == SLIGHT_RIGHT)
        return SOFT_RIGHT;

    if (state == HARD_LEFT)
        return TURN_LEFT;

    if (state == HARD_RIGHT)
        return TURN_RIGHT;

    if (state == LEFT_TURN )
        return TURN_LEFT;

    if (state == RIGHT_TURN )
        return TURN_RIGHT;

    return GO_FORWARD;
}
