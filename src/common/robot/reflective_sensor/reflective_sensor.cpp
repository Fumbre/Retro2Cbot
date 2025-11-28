#include "reflective_sensor.h"

void initReflectiveSensorPins()
{
    for (int i = 0; i < PINS_RS_LENGTH; i++)
    {
        pinMode(PINS_RS[i], INPUT);
    }
}

WheelSpeed checkLine(int baseSpeed)
{
    // define some variables
    int sum = 0;
    int weightedSum = 0;
    int max_adjust_value = 30;
    WheelSpeed speed;
    // loop analog pins
    for (int i = 0; i < PINS_RS_LENGTH; i++)
    {
        // check black line
        int blackLine = analogRead(PINS_RS[i]) > THRESHOLD ? 1 : 0;
        if (blackLine)
        {
            sum++;
            weightedSum += WEIGHT[i];
        }
    }
    // check whether exist black line
    if (sum == 0)
    {
        // TODO
        speed.leftSpeed = baseSpeed;
        speed.rightSpeed = baseSpeed;
        return speed;
    }
    // get the current position
    int position = weightedSum / sum;
    // position transfer to speed difference
    int speedDifference = (float)position / (float)WEIGHT[PINS_RS_LENGTH - 1] * max_adjust_value;
    int leftSpeed, rightSpeed;
    leftSpeed = baseSpeed + speedDifference;
    rightSpeed = baseSpeed - speedDifference;
    leftSpeed = constrain(leftSpeed,0,100);
    rightSpeed = constrain(rightSpeed,0,100);
    speed.leftSpeed = leftSpeed;
    speed.rightSpeed = rightSpeed;
    return speed;
}
