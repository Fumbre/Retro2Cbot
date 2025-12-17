#include "lineMazeLogic.h"

MazeLogic::MazeLogic(TurnPreference pref)
    : pref(pref),
      robotState(FOLLOW_LINE),
      lastStableState(CENTER),
      stackTop(1),
      stopStartTime(0),
      stopDurationMs(150)
{}

void MazeLogic::pushTurn(TurnDir dir) {
    if (stackTop < MAX_TURNS)
        turnStack[stackTop++] = dir;
}

bool MazeLogic::popTurn(TurnDir &dir) {
    if (stackTop == 0) return false;
    dir = turnStack[--stackTop];
    return true;
}

MazeMove MazeLogic::decide(LineState state) {

    switch (robotState) {

    // ================= FOLLOW LINE =================
    case FOLLOW_LINE:

        if (state != ALL_WHITE)
            lastStableState = state;

        // Detect ignored turns
        if (state == LEFT_TURN && pref == RIGHT_FIRST) {
            pushTurn(LEFT_DIR);
        }

        if (state == RIGHT_TURN && pref == LEFT_FIRST) {
            pushTurn(RIGHT_DIR);
        }

        if (state == ALL_WHITE) {

            robotState = STOPPED;
            stopStartTime = millis(); 
            return NO_ACTION;
        }

        if (state == SLIGHT_LEFT)  return SOFT_LEFT;
        if (state == SLIGHT_RIGHT) return SOFT_RIGHT;

    return GO_FORWARD;

    // ================= STOPPED =================

    case STOPPED:

    // Stay stopped until delay expires
    if (millis() - stopStartTime < stopDurationMs) {
        return NO_ACTION;
    }

    // Decide after stopping
    if (lastStableState == LEFT_TURN) {
        robotState = TURNING;
        return TURN_LEFT;
    }

    if (lastStableState == RIGHT_TURN) {
        robotState = TURNING;
        return TURN_RIGHT;
    }

    if (lastStableState == ALL_BLACK) {
        robotState = TURNING;
        return (pref == LEFT_FIRST) ? TURN_LEFT : TURN_RIGHT;
    }

    robotState = UTURNING;
    return UTURN;


    // ================= UTURNING =================
    case UTURNING:

        if (state != ALL_WHITE) {
            robotState = BACKTRACKING;
            return GO_FORWARD;
        }
        return NO_ACTION;

    // ================= BACKTRACKING =================
    case BACKTRACKING:

        if (state == LEFT_TURN || state == RIGHT_TURN) {

            TurnDir dir;
            if (popTurn(dir)) {
                robotState = TURNING;
                return (dir == LEFT_DIR) ? TURN_LEFT : TURN_RIGHT;
            }
        }

        if (state == SLIGHT_LEFT)  return SOFT_LEFT;
        if (state == SLIGHT_RIGHT) return SOFT_RIGHT;

        return GO_FORWARD;

    // ================= TURNING =================
    case TURNING:

        if (state != ALL_WHITE) {
            robotState = FOLLOW_LINE;
            return GO_FORWARD;
        }
        return NO_ACTION;
    }

    return NO_ACTION;
}
