#pragma once
#include "lineMazeLogic.h"
#include "command.h"

class MazeController {
public:
    MazeController(int baseSpeed, int turnSpeed);

    MotorCommand execute(MazeMove move);

private:
    int baseSpeed;
    int turnSpeed;
};
