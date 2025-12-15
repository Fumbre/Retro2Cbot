#include "movement.h"

static int prevPulsesLeft = 0;
int prevPulsesRigt = 0;

Timer didMoveRightTimer;
Timer didMoveLeftTimer;

// bool didMoveRight(int speed, int ms)
// {
//     if (!didMoveRightTimer.timeout(ms)) {
//         moveStabilized(speed, -speed);
//         return false;
//     }

//     didMoveRightTimer.resetTimeout();
//     return true;
// }


/**
 * @name resetMoveLeft
 * @author Fumbre(Vladyslav)
 * @date 27-11-2025
 * @param speed(-255|255)
 * @param pulses(0 99)
 * @details reset didMoveLeft timer
 */
void resetMoveLeft()
{
  didMoveLeftTimer.resetExecuteOnce();
}

/**
 * @name resetMoveRight
 * @author Fumbre(Vladyslav)
 * @date 27-11-2025
 * @param speed(-255|255)
 * @param pulses(0 99)
 * @details reset didMoveRight timer
 */
void resetMoveRight()
{
  didMoveRightTimer.resetExecuteOnce();
}

/**
 * @name didMoveRight
 * @author Fumbre(Vladyslav)
 * @date 27-11-2025
 * @param speed(0|255)
 * @param pulses(0 99)
 * @return bool
 * @details after pulses rotation return true, otherwise false
 */
bool didMoveRight(int speed, int pulses)
{
  if (didMoveRightTimer.executeOnce(0))
  {
    prevPulsesLeft = motor_left_pulses_counter;
  }

  if (motor_left_pulses_counter >= prevPulsesLeft + pulses)
  {
    didMoveRightTimer.resetExecuteOnce();
    moveStopAll();
    return true;
  }
  else
  {
    moveStabilized(speed, -speed);
    return false;
  }
}

/**
 * @name didMoveLeft
 * @author Fumbre(Vladyslav)
 * @date 27-11-2025
 * @param speed(0|255)
 * @param pulses(0 99)
 * @return bool
 * @details after pulses rotation return true, otherwise false
 */
bool didMoveLeft(int speed, int pulses)
{
  if (didMoveLeftTimer.executeOnce(0))
  {
    prevPulsesRigt = motor_right_pulses_counter;
  }

  if (motor_right_pulses_counter >= prevPulsesRigt + pulses)
  {
    didMoveLeftTimer.resetExecuteOnce();
    moveStopAll();
    return true;
  }
  else
  {
    moveStabilized(-speed, speed);
    return false;
  }
}


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
 * @details this function doesn't count your pulses
 * @details you can use speed from -255 to 255
 */
void moveSpeed(int speedLeft, int speedRight)
{

  if (speedLeft < 0)
  {
    analogWrite(PIN_MOTOR_LEFT_FORWARD, LOW);
    analogWrite(PIN_MOTOR_LEFT_BACKWARD, speedLeft * -1);
  }
  else
  {
    analogWrite(PIN_MOTOR_LEFT_BACKWARD, LOW);
    analogWrite(PIN_MOTOR_LEFT_FORWARD, speedLeft);
  }

  if (speedRight < 0)
  {
    analogWrite(PIN_MOTOR_RIGHT_FORWARD, LOW);
    analogWrite(PIN_MOTOR_RIGHT_BACKWARD, speedRight * -1);
  }
  else
  {
    analogWrite(PIN_MOTOR_RIGHT_BACKWARD, LOW);
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
    
    #define LEFT_CORRECTION  1.00   
    #define RIGHT_CORRECTION 0.93   

    speedLeft  = speedLeft  * LEFT_CORRECTION;
    speedRight = speedRight * RIGHT_CORRECTION;

    static int step = 0;
    static Timer stampForward;
    static Timer stampRotateLeft;
    static Timer stampRotateRight;

    switch (step)
    {
    case 0:
        if (stampForward.interval(20))
        {
            writeSpeed(speedLeft, speedRight);
        }
        if (stampForward.executeOnce(40))
        {
            step++;
        }
        break;

    case 1:
        if (motor_left_pulses_counter < motor_right_pulses_counter)
        {
            if (stampRotateLeft.interval(0))
            {
                writeSpeed(speedLeft, speedRight / 1.8);
            }
            if (stampRotateLeft.executeOnce(20))
            {
                step++;
            }
        }
        else
        {
            step++;
        }
        break;

    case 2:
        if (motor_left_pulses_counter > motor_right_pulses_counter)
        {
            if (stampRotateRight.interval(0))
            {
                writeSpeed(speedLeft / 1.8, speedRight);
            }
            step++;
        }
        else
        {
            step++;
        }
        break;

    case 3:
        stampForward.hardReset();
        stampRotateLeft.hardReset();
        stampRotateRight.hardReset();

        step = 0;
        break;
    }
}


/**
 * @name writeSpeed
 * @author Fumbre(Vladyslav)
 * @date 26-11-2025
 * @param speedLeft(-255|255)
 * @param speedRight(-255|255)
 *
 * @details put to left and right motors high depending on values
 * @details for minus value motor go backward
 * @details this funciton put all pins to LOW (used for moveStabilized)
 */
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