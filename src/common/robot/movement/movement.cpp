#include "movement.h"

void moveForward(int speed)
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    analogWrite(PINS_MOTOR[i], 0);
    if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_FORWARD)
      analogWrite(PIN_MOTOR_RIGHT_FORWARD, 255);
    if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_FORWARD)
      analogWrite(PIN_MOTOR_LEFT_FORWARD, 255);
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

void rotateRight(int speed)
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    analogWrite(PINS_MOTOR[i], 0);
    if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_BACKWARD)
      analogWrite(PIN_MOTOR_RIGHT_BACKWARD, speed);
    if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_FORWARD)
      analogWrite(PIN_MOTOR_LEFT_FORWARD, speed);
  }
};

void moveStop(int motor_pin) { digitalWrite(motor_pin, 0); };

void stopMotors()
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    digitalWrite(PINS_MOTOR[i], 0);
  }
};

void switchDirection(int speedLeft, int speedRight)
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    analogWrite(PINS_MOTOR[i], 0);
    if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_FORWARD)
      analogWrite(PIN_MOTOR_RIGHT_FORWARD, speedRight);
    if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_FORWARD)
      analogWrite(PIN_MOTOR_LEFT_FORWARD, speedLeft);
  }
}

void writeSpeed(int speedLeft, int speedRight)
{

  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    analogWrite(PINS_MOTOR[i], LOW);
  }

  if (speedLeft < 0)
  {
    analogWrite(PIN_MOTOR_LEFT_BACKWARD, speedLeft * -1);
  }
  else
  {
    analogWrite(PIN_MOTOR_LEFT_FORWARD, speedLeft);
  }

  if (speedRight < 0)
  {
    analogWrite(PIN_MOTOR_RIGHT_BACKWARD, speedRight * -1);
  }
  else
  {
    analogWrite(PIN_MOTOR_RIGHT_FORWARD, speedRight);
  }
}

/**
 * @name moveTo
 * @author Fumbre(Vladyslav)
 * @date 26-11-2025
 * @param speedLeft(-255 255)
 * @param speedRight(-255 255)
 *
 * @details you can use speed from -255 to 255
 */

int stap = 0;
Timer stampForward;
Timer stampBackward;
Timer stampRotateLeft;
Timer stampRotateRight;

void moveSpeed(int speedLeft, int speedRight)
{
  switch (stap)
  {
  case 0:
    if (stampForward.interval(20))
    {
      writeSpeed(speedLeft, speedRight);
    }
    if (stampForward.executeOnce(40))
    {
      stap++;
    }
    break;

  case 1:
    if (motor_left_pulses_counter < motor_right_pulses_counter)
    {
      if (stampRotateLeft.interval(0))
      {
        writeSpeed(speedLeft, speedRight / 1.7);
        // switchDirection(200, 90);
      }
      if (stampRotateLeft.executeOnce(4))
      {
        stap++;
      }
    }
    else
    {
      stap++;
    }
    break;

  case 2:
    if (motor_left_pulses_counter > motor_right_pulses_counter)
    {
      if (stampRotateRight.interval(0))
      {
        writeSpeed(speedLeft / 1.7, speedRight);
      }
      if (stampRotateRight.executeOnce(4))
      {
        stap++;
      }
    }
    else
    {
      stap++;
    }
    break;

  case 3:
    stampForward.hardReset();
    stampRotateLeft.hardReset();
    stampRotateRight.hardReset();

    stap = 0;
    break;
  }
}
