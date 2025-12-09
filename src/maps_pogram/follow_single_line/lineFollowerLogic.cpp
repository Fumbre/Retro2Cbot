#include "lineFollowerLogic.h"

LineFollowerLogic::LineFollowerLogic(int baseSpeed, int turnSpeed)
    : baseSpeed(baseSpeed), turnSpeed(turnSpeed) {}

MotorCommand LineFollowerLogic::decide(LineState state) {

    switch (state) {

        case CENTER:        return { baseSpeed, baseSpeed };
        case SLIGHT_LEFT:   return { baseSpeed * 0.5, baseSpeed };
        case SLIGHT_RIGHT:  return { baseSpeed, baseSpeed * 0.5 };
        case HARD_LEFT:     return { -turnSpeed, turnSpeed };
        case HARD_RIGHT:    return { turnSpeed, -turnSpeed };
        case ALL_WHITE:     return { baseSpeed, -baseSpeed };

        default:
            return { baseSpeed, baseSpeed };
    }
}
