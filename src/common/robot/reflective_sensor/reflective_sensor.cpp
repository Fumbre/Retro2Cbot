/**
 * @name functions of reflective sensor
 * @author Sunny
 * @date 21-11-2025
 */
#include "reflective_sensor.h"


/**
 * @name initReflectiveSensorsPins
 * @author Sunny
 * @date 24-11-2025
 */
void initReflectiveSensorsPins(){
    for(int i = 0; i < PINS_RS_LENGTH; i++){
        pinMode(PINS_RS[i],INPUT);
    }
}

/**
 * @name checkLine
 * @author Sunny
 * @date 21-11-2025
 * @details Acording the reflective sensor, getting current left and right wheel speed (0-100%)
 * @param baseSpeed initial speed of motors (0-100%)
 * @return MotorSpeed  It's a struct, which include left wheel speed and right wheel speed
 */
MotorSpeed checkLine(int baseSpeed)
{
    // define some variables
    MotorSpeed motorSpeed;
    int sum = 0;
    long weightedSum = 0;
    // loop reflective sensor pins
    for (int i = 0; i < PINS_RS_LENGTH; i++)
    {
        // get value for analog pins
        int black = (analogRead(PINS_RS[i]) > THRESHOLD ? 1 : 0);
        // if checked the black line
        if (black)
        {
            weightedSum += WEIGHT[i];
            sum++;
        }
    }
    // there is no black line on the ground, robot go forward
    if (sum == 0)
    {
        motorSpeed.leftSpeed = baseSpeed;
        motorSpeed.rightSpeed = baseSpeed;
        return motorSpeed;
    }
    // caculate the position of black line center
    int position = weightedSum / sum;
    // caculate left and right wheel speed (0-100%)
    int strength = (position * 100) / 350;
    int adjustTurnPower = (TURNPOWER * baseSpeed) / 100;

    int leftSpeed = baseSpeed - (strength * adjustTurnPower) / 100;
    int rightSpeed = baseSpeed + (strength * adjustTurnPower) / 100;
    leftSpeed = constrain(leftSpeed,0,100);
    rightSpeed = constrain(rightSpeed,0,100);
    // return result;
    motorSpeed.leftSpeed = leftSpeed;
    motorSpeed.rightSpeed = rightSpeed;
    return motorSpeed;
}