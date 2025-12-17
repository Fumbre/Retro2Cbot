#include "mazeController.h"

MazeController::MazeController(int baseSpeed, int turnSpeed)
    : baseSpeed(baseSpeed), turnSpeed(turnSpeed) {}

MotorCommand MazeController::execute(MazeMove move) {

    switch(move) {
        case TURN_LEFT:
            return { -turnSpeed, turnSpeed };

        case TURN_RIGHT:
            return { turnSpeed, -turnSpeed };

        case SOFT_LEFT:
            return { baseSpeed * 0.5, baseSpeed };

        case SOFT_RIGHT:
            return { baseSpeed, baseSpeed * 0.5 };

        case NO_ACTION:
            return { };

        case UTURN:
            return { -turnSpeed + 10 , turnSpeed - 10};

        default:
            return { baseSpeed, baseSpeed };
    }
}
