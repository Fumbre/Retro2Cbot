#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsMaze(PINS_RS, PINS_RS_LENGTH, THRESHOLD);

float slightConf = .8;

void mazeLineSetup()
{
    setupMotor();
    rsMaze.setup();
}

void mazeLine(int speed)
{
    uint8_t currentLineStatus = rsMaze.readBlackLine();
    float pwmValue = getPWMValue(speed);
    switch (currentLineStatus)
    {
    case CENTER:
        moveSpeed(pwmValue, pwmValue);
        break;
    case SLIGHT_LEFT:
        moveSpeed(pwmValue * slightConf, pwmValue);
        break;
    case SLIGHT_RIGHT:
        moveSpeed(pwmValue, pwmValue * slightConf);
        break;
    case HARD_LEFT:
        break;
    case HARD_RIGHT:
        break;
    case ALL_WHITE:
        break;
    case ALL_BLACK:
        break;                 
    }
}

float getPWMValue(int speed)
{
    speed = constrain(speed, 0, FULL_SPEED);
    float pwmValue = (float)speed / FULL_SPEED * FULL_PWM_VALUE;
    return constrain(pwmValue, 0, FULL_PWM_VALUE);
}