#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"
#include "common/tools/tests/test_pulses.h"
#include "common/tools/timer.h"
#include <Arduino.h>

const int SETTING_MODE = 2;

Timer doCoolRotation;
Timer test;

void setup()
{
  Serial.begin(9600);
  setupMotor();
}

Timer stampForward;
Timer stampBackward;
Timer stampRotateLeft;
Timer stampRotateRight;

int pass = false;

void loop()
{

  testPulses(1000);

  //------------first test------------------
  // if (stampForward.interval(1000, 1500))
  // {
  //   moveBackward(255);
  // }
  // else
  // {
  //   moveForward(255);
  // }

  //------------second test------------------
  //  if (stampForward.timeout(3000))
  //   {
  //     stampForward.hardReset();
  //     stampBackward.hardReset();
  //     stampRotateLeft.hardReset();
  //   }

  //   if (stampForward.executeOnce(0))
  //   {
  //     moveForward(255);
  //   }

  //   if (stampBackward.executeOnce(1000))
  //   {
  //     moveBackward(255);
  //   }

  //   if (stampRotateLeft.executeOnce(2000))
  //   {
  //     rotateLeft(255);
  //   }

  //------------three test------------------

  if (!doCoolRotation.timeout(32000))
  {
    if (test.interval(25))
    {

      if (stampRotateLeft.interval(20, 20))
      {
        rotateLeft(255);
      }
      else
      {
        rotateRight(255);
      }
      moveForward(255);
    }
  }

  if (doCoolRotation.executeOnce(32000))
  {
    moveStopAll();
  }

  //------------four test------------------

  // if (!doCoolRotation.timeout(32000))
  // {
  //   // if (test.interval(20))
  //   // {
  //   if (test.executeOnce(0))
  //   {
  //     moveForward(255);
  //   }
  //   if (stampRotateLeft.interval(25, 15))
  //   {
  //     analogWrite(PIN_MOTOR_LEFT_BACKWARD, 0);
  //     // rotateLeft(255);
  //   }
  //   // else
  //   // {
  //   //   // rotateRight(255);
  //   // }
  //   moveForward(255);
  //   // }
  // }

  // if (doCoolRotation.executeOnce(32000))
  // {
  //   moveStopAll();
  // }

  switch (SETTING_MODE)
  {
  case 0:
    // to do followSingleLine
    break;
  case 1:
    // to do mazeLine
    break;
  case 2:
    // to do physicalMaze
    break;

  default:
    Serial.print("NO SUCH A PROGRAM");
    break;
  }
}
