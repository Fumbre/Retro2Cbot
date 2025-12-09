#pragma once
#include "lineInterpreter.h"
#include "command.h"

class LineFollowerLogic {
public:
    LineFollowerLogic(int baseSpeed, int turnSpeed);
    MotorCommand decide(LineState state);

private:
    int baseSpeed;
    int turnSpeed;
};
