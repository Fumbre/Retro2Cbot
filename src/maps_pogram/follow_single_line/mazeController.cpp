#include "mazeController.h"

MazeController::MazeController(int baseSpeed, int turnSpeed)
    : baseSpeed(baseSpeed), turnSpeed(turnSpeed) {}

MotorCommand MazeController::execute(MazeMove move) {

    switch(move) {
        // case TEST_PATTERN:
        //      return { turnSpeed, -turnSpeed };

        case TURN_LEFT:
            return { -baseSpeed, turnSpeed };

        case TURN_RIGHT:
            return { turnSpeed, -baseSpeed };

        case SOFT_LEFT:
            return { baseSpeed * 0.5, baseSpeed };

        case SOFT_RIGHT:
            return { baseSpeed, baseSpeed * 0.5 };

        case NO_ACTION:
            return { };

        case UTURN:
            return { -turnSpeed, turnSpeed };

        default:
            return { baseSpeed, baseSpeed };
    }
}
