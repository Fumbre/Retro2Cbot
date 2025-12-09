#pragma once
#include "mazeMove.h"
#include "command.h"

class MazeController {
public:
    MazeController(int baseSpeed, int turnSpeed);

    MotorCommand execute(MazeMove move);

private:
    int baseSpeed;
    int turnSpeed;
};
