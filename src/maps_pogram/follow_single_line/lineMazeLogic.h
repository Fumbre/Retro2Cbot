#pragma once
#include "lineInterpreter.h"

enum MazeMove {
    GO_FORWARD,
    SOFT_LEFT,
    SOFT_RIGHT,
    TURN_LEFT,
    TURN_RIGHT,
    UTURN,
    NO_ACTION
};

enum RobotState {
    FOLLOW_LINE,
    STOPPED,
    TURNING,
    UTURNING,
    BACKTRACKING
};

enum TurnPreference {
    LEFT_FIRST,
    RIGHT_FIRST
};

class MazeLogic {
public:
    MazeLogic(TurnPreference pref);
    MazeMove decide(LineState state);

private:
    TurnPreference pref;
    RobotState robotState;

    LineState lastStableState;

    LineState pendingFollowState;
    int pendingFollowCount;
    static const int FOLLOW_CONFIRM_COUNT = 7;
};
