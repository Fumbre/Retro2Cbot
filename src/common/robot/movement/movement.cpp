#include "movement.h"

void moveForward(int speed, bool isPure)
{
  if (isPure)
  {
    for (int i = 0; i < WHEEL_ARRAY_LENGTH; i++)
    {
      analogWrite(WHEEL_ARRAY[i].PIN, 0);
      if (WHEEL_ARRAY[i].title == "WHEEL_RIGHT_FORWARD_PIN")
        analogWrite(WHEEL_RIGHT_FORWARD_PIN, speed);
      if (WHEEL_ARRAY[i].title == "WHEEL_LEFT_FORWARD_PIN")
        analogWrite(WHEEL_LEFT_FORWARD_PIN, speed);
    }
  }
  else
  {
    analogWrite(WHEEL_RIGHT_FORWARD_PIN, speed);
    analogWrite(WHEEL_LEFT_FORWARD_PIN, speed);
  }
};

void moveBackward(int speed)
{
  for (int i = 0; i < WHEEL_ARRAY_LENGTH; i++)
  {
    analogWrite(WHEEL_ARRAY[i].PIN, 0);
    if (WHEEL_ARRAY[i].title == "WHEEL_LEFT_BACKWARD_PIN")
      analogWrite(WHEEL_LEFT_BACKWARD_PIN, speed);
    if (WHEEL_ARRAY[i].title == "WHEEL_RIGHT_BACKWARD_PIN")
      analogWrite(WHEEL_RIGHT_BACKWARD_PIN, speed);
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
    for (int i = 0; i < WHEEL_ARRAY_LENGTH; i++)
    {
      analogWrite(WHEEL_ARRAY[i].PIN, 0);
      if (WHEEL_ARRAY[i].title == "WHEEL_LEFT_FORWARD_PIN")
        analogWrite(WHEEL_LEFT_FORWARD_PIN, speed);
      if (WHEEL_ARRAY[i].title == "WHEEL_RIGHT_BACKWARD_PIN")
        analogWrite(WHEEL_RIGHT_BACKWARD_PIN, speed);

      // if (WHEEL_ARRAY[i].title == "WHEEL_LEFT_ROTATION_PIN")
      // analogWrite(WHEEL_LEFT_ROTATION_PIN, speed);
      // if (WHEEL_ARRAY[i].title == "WHEEL_LEFT_ROTATION_PIN")
      // analogWrite(WHEEL_LEFT_ROTATION_PIN, speed);
    }
  }
  else
  {
    analogWrite(WHEEL_LEFT_FORWARD_PIN, speed);
    analogWrite(WHEEL_LEFT_ROTATION_PIN, speed);
  }
};

void rotateLeft(int speed) {

};

void moveStop(int wheel_pin)
{
  analogWrite(wheel_pin, 0);
};

void moveStopAll()
{
  for (int i = 0; i < WHEEL_ARRAY_LENGTH; i++)
  {
    analogWrite(WHEEL_ARRAY[i].PIN, 0);
  }
};