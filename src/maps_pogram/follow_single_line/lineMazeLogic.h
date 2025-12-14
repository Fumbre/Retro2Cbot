#pragma once
#include "lineInterpreter.h"
 
enum MazeMove {
    GO_FORWARD,
    TURN_LEFT,
    TURN_RIGHT,
    UTURN,
    SOFT_LEFT,
    SOFT_RIGHT,
    CROSSING,
    NO_ACTION   
};

enum TurnPreference { LEFT_FIRST, RIGHT_FIRST };

class MazeLogic {
public:
    MazeLogic(TurnPreference pref, unsigned long cooldownMs);
    MazeMove decide(LineState state, unsigned long timeNow);

private:
    TurnPreference pref;

    // previous state robot acted on
    LineState lastState;

    // cooldown timer
    unsigned long lastDecisionTime;
    unsigned long cooldownMs;

    // confirmation filter
    LineState pendingState;
    int pendingCount;
};
