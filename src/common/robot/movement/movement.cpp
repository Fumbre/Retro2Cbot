#include "movement.h"

void moveRight(int speed) {

};

void moveLeft(int speed) {

};

/**
 * @name moveStop
 * @author Fumbre(Vladyslav)
 * @date 13-11-2025
 * @details stop specific motor pin
 */
void moveStop(int motor_pin) { digitalWrite(motor_pin, LOW); };

/**
 * @name moveStopAll
 * @author Fumbre(Vladyslav)
 * @date 13-11-2025
 * @details stop all motor pins
 */
void moveStopAll()
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    digitalWrite(PINS_MOTOR[i], LOW);
  }
};

/**
 * @name moveSpeed
 * @author Fumbre(Vladyslav)
 * @date 26-11-2025
 * @param speedLeft(-255|255)
 * @param speedRight(-255|255)
 *
 * @details you can use speed from -255 to 255
 */
void moveSpeed(int speedLeft, int speedRight)
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
 * @name moveStabilized
 * @author Fumbre(Vladyslav)
 * @date 26-11-2025
 * @param speedLeft(-255|255)
 * @param speedRight(-255|255)
 *
 * @details movement is stabilized by pulses
 * @details you can use speed from -255 to 255
 */
void moveStabilized(int speedLeft, int speedRight)
{
  static int step = 0;
  static Timer stampForward;
  static Timer stampRotateLeft;
  static Timer stampRotateRight;

  setupPulseCounter();

  switch (step)
  {
  case 0:
    stampForward.hardReset();
    stampRotateLeft.hardReset();
    stampRotateRight.hardReset();

    step = 1;
    break;

  case 1:
    if (stampForward.interval(0))
    {
      moveSpeed(speedLeft, speedRight);
    }
    if (stampForward.executeOnce(20))
    {
      step++;
    }
    break;

  case 2:
    if (motor_left_pulses_counter < motor_right_pulses_counter)
    {
      if (stampRotateLeft.interval(0))
      {
        moveSpeed(speedLeft, speedRight / 1.7);
      }
      if (stampRotateLeft.executeOnce(4))
      {
        step++;
      }
    }
    else
    {
      step++;
    }
    break;

  case 3:
    if (motor_left_pulses_counter > motor_right_pulses_counter)
    {
      if (stampRotateRight.interval(0))
      {
        moveSpeed(speedLeft / 1.7, speedRight);
      }
      if (stampRotateRight.executeOnce(4))
      {
        step++;
      }
    }
    else
    {
      step++;
    }
    break;
  }
}