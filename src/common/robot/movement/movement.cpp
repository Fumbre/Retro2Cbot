#include "movement.h"

void moveForward(int speed)
{
  MotorSpeed dynamicalPower = motorStability(speed);

  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    analogWrite(PINS_MOTOR[i], 0);
    if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_FORWARD)
      analogWrite(PIN_MOTOR_RIGHT_FORWARD, dynamicalPower.speedRight); // dynamicalPower.speedRight
    if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_FORWARD)
      analogWrite(PIN_MOTOR_LEFT_FORWARD, dynamicalPower.speedLeft); //  dynamicalPower.speedLeft
  }
};

void moveBackward(int speed)
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    analogWrite(PINS_MOTOR[i], 0);
    if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_BACKWARD)
      analogWrite(PIN_MOTOR_LEFT_BACKWARD, speed);
    if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_BACKWARD)
      analogWrite(PIN_MOTOR_RIGHT_BACKWARD, speed);
  }
};

void moveRight(int speed) {

};

void moveLeft(int speed) {

};

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

void moveStop(int motor_pin)
{
  analogWrite(motor_pin, 0);
};

void moveStopAll()
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    digitalWrite(PINS_MOTOR[i], 0);
  }
};