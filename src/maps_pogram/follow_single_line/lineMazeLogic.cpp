#include "lineMazeLogic.h"

MazeLogic::MazeLogic(TurnPreference pref, unsigned long cooldownMs)
    : pref(pref),
      cooldownMs(cooldownMs),
      lastState(CENTER),
      lastDecisionTime(0),
      pendingState(CENTER),
      pendingCount(0)
{}

MazeMove MazeLogic::decide(LineState state, unsigned long timeNow) {

    //  2-of-3 confirmation filter
    if (state == pendingState) {
        pendingCount++;
    } else {
        pendingState = state;
        pendingCount = 1;
    }

    // require 2 identical readings in a row
    if (pendingCount < 3) {
        return NO_ACTION;
    }

    // after confirming, clear counter so next change must be reconfirmed
    pendingCount = 0;

    // cooldown
    if (timeNow - lastDecisionTime < cooldownMs) {
        return NO_ACTION;
    }

    if (pendingState == lastState) {
        return NO_ACTION;
    }

    // accept final state
    lastState = pendingState;
    lastDecisionTime = timeNow;


    if (pendingState == CENTER)
        return GO_FORWARD;

    if (pendingState == ALL_BLACK && pref == RIGHT_FIRST)
        return TURN_RIGHT;
    
    if (pendingState == ALL_BLACK && pref == LEFT_FIRST)
        return TURN_LEFT;

    if (pendingState == SLIGHT_LEFT)
        return SOFT_LEFT;

    if (pendingState == SLIGHT_RIGHT)
        return SOFT_RIGHT;

    if (pendingState == HARD_LEFT)
        return TURN_LEFT;

    if (pendingState == HARD_RIGHT)
        return TURN_RIGHT;

    if (pendingState == LEFT_TURN)
        return TURN_LEFT;

    if (pendingState == RIGHT_TURN)
        return TURN_RIGHT;

    if (pendingState == ALL_WHITE)
        return UTURN;

    return GO_FORWARD;
}
