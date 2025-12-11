/**
 * @name the basic functions of robots
 * @authors Sunny
 * @date 10-11-2025
 */
#include "movementPID.h"

PID forwardPID(Kp_f, Ki_f, Kd_f);
PID backwardPID(Kp_b, Ki_b, Kd_b);

unsigned long lastPIDTime = 0;
const unsigned long PID_INTERVAL = 10;
bool moveForwardStart = false;
bool moveBackWardStart = false;
bool isMovingForward = true;

float leftPWM = 0;
float rightPWM = 0;

/**
 * @name getPWMvalue
 * @author Sunny
 * @date 11-11-2025
 * @param speed
 *
 * @details  that function calclulate procantage of speed for analogWrite(255) is max speed is in procatage
 * so we will have correcrt procatage based on max value of PWM_VALUE
 *
 * @return PWM value
 */
float getPWMvalue(int speed)
{
    speed = constrain(speed, 0, FULL_SPEED); // if more than full speed put full speed variable [100%]
    float value = (float)speed / 100.0;
    return roundf(value * FULL_PWM_VALUE); // 0.80 * 255 = 204 * 0.97
}

/**
 * @name moveForward
 * @author Sunny
 * @date 10-11-2025
 * @param speed(0|100)
 */
void moveForward(int speed)
{
    if (!moveForwardStart)
    {
        forwardPID.integral = 0;
        moveForwardStart = true;
        float pwmValue = getPWMvalue(100);
        leftPWM = pwmValue;
        rightPWM = pwmValue;
    }

    isMovingForward = true;

    Stability stability = adjustPWMvalueByPulse(&leftPWM, &rightPWM);

    analogWrite(PIN_MOTOR_LEFT_FORWARD, stability.speedLeft);
    digitalWrite(PIN_MOTOR_LEFT_BACKWARD, LOW);
    analogWrite(PIN_MOTOR_RIGHT_FORWARD, stability.speedRight);
    digitalWrite(PIN_MOTOR_RIGHT_BACKWARD, LOW);
}

/**
 * @name moveBackward
 * @author Sunny
 * @date 10-11-2025
 * @param speed
 */
void moveBackward(int speed)
{
    if (!moveBackWardStart)
    {
        backwardPID.integral = 0;
        float pwmValue = getPWMvalue(speed);
        leftPWM = pwmValue;
        rightPWM = pwmValue;
        moveBackWardStart = true;
    }

    isMovingForward = false;

    // get PWM value
    Stability stability = adjustPWMvalueByPulse(&leftPWM, &rightPWM);

    // Serial.print("left: ");
    // Serial.println(stability.speedLeft);
    // Serial.print("right: ");
    // Serial.println(stability.speedRight);

    analogWrite(PIN_MOTOR_LEFT_BACKWARD, stability.speedLeft);
    digitalWrite(PIN_MOTOR_LEFT_FORWARD, LOW);
    analogWrite(PIN_MOTOR_RIGHT_BACKWARD, stability.speedRight);
    digitalWrite(PIN_MOTOR_RIGHT_FORWARD, LOW);
}

/**
 * @name switchDirection
 * @author Sunny
 * @date 10-11-2025
 * @param leftSpeed
 * @param rightSpeed
 */
void switchDirection(int leftSpeed, int rightSpeed)
{
    leftPWM = getPWMvalue(leftSpeed);
    rightPWM = getPWMvalue(rightSpeed);
    adjustPWMvalueByPulse(&leftPWM, &rightPWM);
    // put left wheel pin
    analogWrite(PIN_MOTOR_LEFT_FORWARD, leftPWM);
    digitalWrite(PIN_MOTOR_LEFT_BACKWARD, LOW);
    // put right wheel pin
    analogWrite(PIN_MOTOR_RIGHT_FORWARD, rightPWM);
    digitalWrite(PIN_MOTOR_RIGHT_BACKWARD, LOW);
}

/**
 * @name stopMotors
 * @author Fumbre (Vladyslav)
 * @date 10-11-2025
 */
void stopMotors()
{
    for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
    {
        digitalWrite(PINS_MOTOR[i], LOW);
    }
}

/**
 * @name rotateLeft
 * @author Fumbre (Vladyslav)
 * @date 19-11-2025
 * @param speed (0-255)
 */
void rotateLeft(int speed)
{
    for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
    {
        analogWrite(PINS_MOTOR[i], 0);
        if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_BACKWARD)
            analogWrite(PIN_MOTOR_LEFT_BACKWARD, speed);
        if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_FORWARD)
            analogWrite(PIN_MOTOR_RIGHT_FORWARD, speed);
    }
};

/**
 * @name rotateLeft
 * @author Fumbre (Vladyslav)
 * @date 19-11-2025
 * @param speed (0-255)
 */
void rotateRight(int speed)
{
    for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
    {
        analogWrite(PINS_MOTOR[i], 0);
        if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_FORWARD)
            analogWrite(PIN_MOTOR_LEFT_BACKWARD, speed);
        if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_BACKWARD)
            analogWrite(PIN_MOTOR_RIGHT_FORWARD, speed);
    }
};

// /**
//  * @name rotate
//  * @author Sunny
//  * @date 12-11-2025
//  * @param speed (0-100%)
//  * @param direction (left, right)
//  * @param angle (0-360)
//  */
// void rotate(int speed, String direction, float angle)
// {

//     // reset encoder count
//     motor_left_pulses_counter = 0;
//     motor_right_pulses_counter = 0;

//     // caculate the max number of rotation of wheels for rotate 180 degrees
//     angle = constrain(angle, 0.0, 360.0);
//     float rotateDistance = (angle / 360.0) * (2 * PI * ROBOT_RADUIS);
//     float wheelTurns = rotateDistance / (2 * PI * WHEEL_RADUIS);
//     int targetPulses = wheelTurns * PPR;

//     // get PWM value
//     int pwmValue = getPWMvalue(speed);
//     leftPWM = pwmValue;
//     rightPWM = pwmValue;
//     adjustPWMvalueByPulse(&leftPWM, &rightPWM);
//     if (direction.equalsIgnoreCase("right"))
//     {
//         // let right wheel go forward, let left wheel go backward
//         analogWrite(PIN_MOTOR_LEFT_FORWARD, pwmValue);
//         digitalWrite(PIN_MOTOR_LEFT_BACKWARD, LOW);
//         analogWrite(PIN_MOTOR_RIGHT_BACKWARD, pwmValue);
//         digitalWrite(PIN_MOTOR_RIGHT_FORWARD, LOW);
//     }
//     else if (direction.equalsIgnoreCase("left"))
//     {
//         // let right wheel go forward, let left wheel go backward
//         analogWrite(PIN_MOTOR_RIGHT_FORWARD, pwmValue);
//         digitalWrite(PIN_MOTOR_RIGHT_BACKWARD, LOW);
//         analogWrite(PIN_MOTOR_LEFT_BACKWARD, pwmValue);
//         digitalWrite(PIN_MOTOR_LEFT_FORWARD, LOW);
//     }
//     // waiting rotate finish

//     // TODO: FIGURE OUT WAY WITHOUT while

//     while (motor_left_pulses_counter <= targetPulses && motor_right_pulses_counter <= targetPulses)
//     {
//     };
//     stopMotors();
// }

/**
 * @name adjustPWMvalueByPulse
 * @author Sunny
 * @date 15-11-2025
 * @details use PID
 */
Stability adjustPWMvalueByPulse(float *leftPWMValue, float *rightPWMValue)
{

    unsigned long now = millis();
    Stability stability;
    // Ensure PID runs at a fixed interval
    if (now - lastPIDTime < INTERNAL)
    {
        stability.speedLeft = *leftPWMValue;
        stability.speedRight = *rightPWMValue;
        return stability;
    }
    lastPIDTime = now;
    // stop interrupting functions to avoid pulses value changing when getting current pulses
    noInterrupts();
    long leftP = motor_left_pulses_counter;
    long rightP = motor_right_pulses_counter;
    motor_left_pulses_counter = 0;
    motor_right_pulses_counter = 0;
    // start interrupting functions
    interrupts();
    // get the distance of left and right wheels running with current pulses. unit:cm
    float leftD = ((float)leftP / (float)PPR) * (2 * PI * WHEEL_RADUIS);
    float rightD = ((float)rightP / (float)PPR) * (2 * PI * WHEEL_RADUIS);
    // caculate correction value
    float correction;
    if (isMovingForward)
    {
        correction = forwardPID.caculateCorrection(leftD, rightD);
    }
    else
    {
        correction = backwardPID.caculateCorrection(leftD, rightD);
    }
    // if(fabs(correction) < 0.5) correction = 0;
    // correction = constrain(correction,-20,20);
    // Serial.print("correction: ");
    // Serial.println(correction);
    // get new pwm value
    *leftPWMValue = constrain(*leftPWMValue - correction, 0, FULL_PWM_VALUE);
    *rightPWMValue = constrain(*rightPWMValue + correction, 0, FULL_PWM_VALUE);
    // Serial.print("inside Left: ");
    // Serial.println(*leftPWMValue);
    // Serial.print("inside right: ");
    // Serial.println(*rightPWMValue);
    stability.speedLeft = *leftPWMValue;
    stability.speedRight = *rightPWMValue;

    return stability;
}