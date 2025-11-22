#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"
#include "common/tools/tests/test_pulses.h"
#include "common/tools/timer.h"
#include "common/robot/sonar/sonar.h"
#include <Arduino.h>
#include "common/tools/tests/test_basicMovements.h"
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/tools/tests/test_reflective_sensor/test_reflective_sensor.h"

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

Timer sadness;
Timer sadness1;

void loop()
{
  // testReflectiveSensor();
  // if (!avoiding)
  // {
  //   moveForward(255);
  // }

  // if (isObstacleDetected(30))
  // {
  //   avoidObstacleSmoothNonBlocking(255);
  // }

  // if (avoiding)
  // {
  //   avoidObstacleSmoothNonBlocking(255);
  // }
  // // moveForward(255);

  // testBasicMovement();
  MotorSpeed motorSpeed =  checkLine(70);
  switchDirection(motorSpeed.leftSpeed,motorSpeed.rightSpeed);
  // moveBackward(100);
  // delay(2000);
  // stopMotors();
  //   // //------------some test------------------

  // if (sadness.executeOnce(0))
  // {
  //   moveForward(100);
  // }

  // if (sadness1.executeOnce(2000))
  // {
  //   // rotate(100, "left", 180);
  //   // rotate(100, "right", 180);
  //   sadness.resetExecuteOnce();
  //   sadness1.resetExecuteOnce();

  //   // stopMotors();
  // }

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
  // if (stampForward.interval(4500))
  // {
  //   stampForward.hardReset();
  //   stampBackward.hardReset();
  //   stampRotateLeft.hardReset();
  // }

  // if (stampForward.executeOnce(0))
  // {
  //   moveForward(255);
  // }

  // if (stampBackward.executeOnce(1000))
  // {
  //   moveBackward(255);
  // }

  // if (stampRotateLeft.executeOnce(2000))
  // {
  //   rotateLeft(255);
  // }

  // if (stampRotateLeft.executeOnce(3500))
  // {
  //   rotateRight(255);
  // }

  //------------three test------------------

  // if (!doCoolRotation.timeout(32000))
  // {
  //   if (test.interval(25))
  //   {

  //     if (stampRotateLeft.interval(20, 20))
  //     {
  //       rotateLeft(250);
  //     }
  //     else
  //     {
  //       rotateRight(255);
  //     }
  //     moveBackward(255);
  //   }
  // }

  // if (doCoolRotation.executeOnce(32000))
  // {
  //   stopMotors();
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

  // switch (SETTING_MODE)
  // {
  // case 0:
  //   // to do followSingleLine
  //   break;
  // case 1:
  //   // to do mazeLine
  //   break;
  // case 2:
  //   // to do physicalMaze
  //   break;

  // default:
  //   Serial.print("NO SUCH A PROGRAM");
  //   break;
  // }
}
