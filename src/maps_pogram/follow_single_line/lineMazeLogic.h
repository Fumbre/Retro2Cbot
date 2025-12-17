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
    TURNING,
    UTURNING,
    BACKTRACKING
};

enum TurnPreference {
    LEFT_FIRST,
    RIGHT_FIRST
};

enum TurnDir {
    LEFT_DIR,
    RIGHT_DIR
};

class MazeLogic {
public:
    MazeLogic(TurnPreference pref);
    MazeMove decide(LineState state);

private:
    TurnPreference pref;
    RobotState robotState;

    LineState lastStableState;

    // Turn memory stack
    static const int MAX_TURNS = 32;
    TurnDir turnStack[MAX_TURNS];
    int stackTop;

    void pushTurn(TurnDir dir);
    bool popTurn(TurnDir &dir);
};
