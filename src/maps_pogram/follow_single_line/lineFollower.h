// =================================================

#pragma once
#include "lineSensor.h"
#include "lineInterpreter.h"
#include "lineFollowerLogic.h"
#include "command.h"

class LineFollower {
public:
    LineFollower(int baseSpeed, int turnSpeed);

    MotorCommand follow(LineSensor& sensor,
                        LineInterpreter& interpreter,
                        LineFollowerLogic& logic);

private:
    int baseSpeed;
    int turnSpeed;
};
