#pragma once
#include "lineInterpreter.h"
#include "mazeMove.h"

enum TurnPreference { LEFT_FIRST, RIGHT_FIRST };

class MazeLogic {
public:
    MazeLogic(TurnPreference pref);

    MazeMove decide(LineState state);

private:
    TurnPreference pref;
};

