#include "reflective_sensor.h"

LineSensor lineSensor(PINS_RS, PINS_RS_LENGTH);
LineFollower lineFollower;
LineInterpreter interpreter;

void initReflectiveSensor()
{
    lineSensor.setup();
}

FollowerResult lineFollow(int speed)
{
    int pwmValue = getPWM(speed);
    lineFollower.setupPWMValue(pwmValue);
    return lineFollower.follow(lineSensor, interpreter);
}

int getPWM(int speed)
{
    int pwmValue = (float)speed / 100 * 255;
    return constrain(pwmValue, 0, 255);
}