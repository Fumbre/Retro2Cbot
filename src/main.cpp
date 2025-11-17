#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"
#include "common/tools/tests/test_pulses.h"
#include "common/tools/timer.h"
#include "common/robot/sonar/sonar.h"
#include <Arduino.h>

const int SETTING_MODE = 2;

Timer doCoolRotation;
Timer test;

void setup()
{
  Serial.begin(9600);
  setupMotor();
  setupSonar();
}

Timer stampForward;
Timer stampBackward;
Timer stampRotateLeft;
Timer stampRotateRight;

int pass = false;

void loop()
{
  switch (SETTING_MODE)
  {
  case 0:
    // to do followSingleLine
    break;
  case 1:
    // to do mazeLine
    break;
  case 2:

      // If robot is currently performing the avoidance sequence,
      //    avoidObstacleStep() takes full control of movement.
      if (avoidObstacleStep())
        return;           // DO NOT execute the code below

      // If NOT avoiding, check if a new obstacle appears
      if (isObstacleDetected(30.0))
      {
        moveStopAll();            // Stop everything clean
        startAvoidObstacle();  // Start the whole sequence again
        return;
      }

      // If no obstacle and not avoiding, move forward normally
      moveForward(200);

      break;
  }
    
  // testPulses(1000);

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

  // if (!doCoolRotation.timeout(32000))
  // {
  //   if (test.interval(25))
  //   {

  //     if (stampRotateLeft.interval(20, 20))
  //     {
  //       rotateLeft(255);
  //     }
  //     else
  //     {
  //       rotateRight(255);
  //     }
  //     moveForward(255);
  //   }
  // }

  // if (doCoolRotation.executeOnce(32000))
  // {
  //   moveStopAll();
  // }

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

  // default:
  //   Serial.print("NO SUCH A PROGRAM");
  //   break;
}
