#include "lineMazeLogic.h"

MazeLogic::MazeLogic(TurnPreference pref, unsigned long cooldownMs)
    : pref(pref),
      cooldownMs(cooldownMs),
      lastState(CENTER),
      lastDecisionTime(0),
      pendingState(CENTER),
      pendingCount(0),
      uturnActive(false),
      turnActive(false),
      activeTurn(GO_FORWARD),
      turnStartTime(0),
      minTurnDurationMs(120)
{}

MazeMove MazeLogic::decide(LineState state, unsigned long timeNow) {

    // --- U-TURN MODE ---
if (uturnActive) {

    // Exit condition: line found again
    if (state != ALL_WHITE) {
        uturnActive = false;
        lastState = state;
        lastDecisionTime = timeNow;
        return GO_FORWARD;
    }

    // Still searching → keep turning
    return UTURN;
}


    //  2-of-3 confirmation filter
    if (state == pendingState) {
        pendingCount++;
    } else {
        pendingState = state;
        pendingCount = 1;
    }

    // require 2 identical readings in a row
    if (pendingCount < 5) {
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

// --- PREFERRED HARD TURNS ONLY ---

// HARD / L TURN (LEFT)
if ((pendingState == HARD_LEFT || pendingState == LEFT_TURN) &&
    pref == LEFT_FIRST) {

    turnActive = true;
    activeTurn = TURN_LEFT;
    turnStartTime = timeNow;
    lastDecisionTime = timeNow;
    return TURN_LEFT;
}

// HARD / R TURN (RIGHT)
if ((pendingState == HARD_RIGHT || pendingState == RIGHT_TURN) &&
    pref == RIGHT_FIRST) {

    turnActive = true;
    activeTurn = TURN_RIGHT;
    turnStartTime = timeNow;
    lastDecisionTime = timeNow;
    return TURN_RIGHT;
}


    if (pendingState == LEFT_TURN)
        return TURN_LEFT;

    if (pendingState == RIGHT_TURN)
        return TURN_RIGHT;


    if (pendingState == ALL_WHITE) {
    uturnActive = true;
    lastDecisionTime = timeNow;
    return UTURN;
    }

    // Ignore non-preferred hard turns (side T-junctions)
if (pendingState == HARD_LEFT || pendingState == HARD_RIGHT ||
    pendingState == LEFT_TURN || pendingState == RIGHT_TURN) {

    // Treat as straight / continue following
    return GO_FORWARD;
}


    return GO_FORWARD;
}
