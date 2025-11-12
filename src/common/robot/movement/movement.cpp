#include "movement.h"

void moveForward(int speed, bool isPure)
{
  if (isPure)
  {
    for (int i = 0; i < MOTOR_ARRAY_LENGTH; i++)
    {
      analogWrite(MOTOR_ARRAY[i].PIN, 0);
      if (MOTOR_ARRAY[i].title == "MOTOR_RIGHT_FORWARD_PIN")
        analogWrite(MOTOR_RIGHT_FORWARD_PIN, speed);
      if (MOTOR_ARRAY[i].title == "MOTOR_LEFT_FORWARD_PIN")
        analogWrite(MOTOR_LEFT_FORWARD_PIN, speed);
    }
  }
  else
  {
    analogWrite(MOTOR_RIGHT_FORWARD_PIN, speed);
    analogWrite(MOTOR_LEFT_FORWARD_PIN, speed);
  }
};

void moveBackward(int speed)
{
  for (int i = 0; i < MOTOR_ARRAY_LENGTH; i++)
  {
    analogWrite(MOTOR_ARRAY[i].PIN, 0);
    if (MOTOR_ARRAY[i].title == "MOTOR_LEFT_BACKWARD_PIN")
      analogWrite(MOTOR_LEFT_BACKWARD_PIN, speed);
    if (MOTOR_ARRAY[i].title == "MOTOR_RIGHT_BACKWARD_PIN")
      analogWrite(MOTOR_RIGHT_BACKWARD_PIN, speed);
  }
};

void moveRight(int speed) {

};

void moveLeft(int speed) {

};

void rotateRight(int speed, bool isPure)
{
  if (isPure)
  {
    for (int i = 0; i < MOTOR_ARRAY_LENGTH; i++)
    {
      analogWrite(MOTOR_ARRAY[i].PIN, 0);
      if (MOTOR_ARRAY[i].title == "MOTOR_LEFT_FORWARD_PIN")
        analogWrite(MOTOR_LEFT_FORWARD_PIN, speed);
      if (MOTOR_ARRAY[i].title == "MOTOR_RIGHT_BACKWARD_PIN")
        analogWrite(MOTOR_RIGHT_BACKWARD_PIN, speed);

      // if (MOTOR_ARRAY[i].title == "MOTOR_LEFT_PULSE_PIN")
      // analogWrite(MOTOR_LEFT_PULSE_PIN, speed);
      // if (MOTOR_ARRAY[i].title == "MOTOR_LEFT_PULSE_PIN")
      // analogWrite(MOTOR_LEFT_PULSE_PIN, speed);
    }
  }
  else
  {
    analogWrite(MOTOR_LEFT_FORWARD_PIN, speed);
    analogWrite(MOTOR_LEFT_PULSE_PIN, speed);
  }
};

void rotateLeft(int speed) {

};

void moveStop(int motor_pin)
{
  analogWrite(motor_pin, 0);
};

void moveStopAll()
{
  for (int i = 0; i < MOTOR_ARRAY_LENGTH; i++)
  {
    analogWrite(MOTOR_ARRAY[i].PIN, 0);
  }
};