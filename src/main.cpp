#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"
#include "common/tools/tests/test_pulses.h"
#include "common/tools/timer.h"
#include "common/robot/sonar/sonar.h"
#include <Arduino.h>
#include "common/tools/tests/test_basic_movements/test_basic_movements.h"
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
  // testPulses(20);
  // testReflectiveSensor();

  //========== avoiding =============

  static bool safeZone = true;

  float distance = getDistanceCM();

  if (!avoiding) {

    if (safeZone && distance <= 30 && distance >= 2) {
      safeZone = false;                   // exiting safe zone
      avoidObstacleSmoothNonBlocking(255);
    }
    else {
      moveForward(255);

      if (distance > 30) {                // hysteresis threshold
        safeZone = true;                // re-enter safe zone only after a clear reading
      }
    }
  } else {
    avoidObstacleSmoothNonBlocking(255);
  }



  //==============================

  // testBasicMovement();

  // MotorSpeed motorSpeed = checkLine(70);
  // switchDirection(motorSpeed.leftSpeed, motorSpeed.rightSpeed);

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
