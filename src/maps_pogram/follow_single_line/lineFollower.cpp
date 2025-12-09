


// ============================================

#include "lineFollower.h"

LineFollower::LineFollower(int baseSpeed, int turnSpeed)
    : baseSpeed(baseSpeed), turnSpeed(turnSpeed) {}

MotorCommand LineFollower::follow(LineSensor& sensor,
                                  LineInterpreter& interpreter,
                                  LineFollowerLogic& logic) {

    LineReading reading = sensor.read();
    LineState st = interpreter.interpret(reading.mask);

    return logic.decide(st);
}

