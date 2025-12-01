#include "common/constant/robot.h"
#include "common/robot/motor/motor.h"
#include "common/tools/bluetooth.h"
#include "common/robot/movement/movement.h"
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/robot/sonar/sonar.h"
#include <Arduino.h>
#include "common/tools/Timer.h"
#include "common/tools/tests/test_basic_movements/test_basic_movements.h"
#include "common/tools/tests/test_reflective_sensor/test_reflective_sensor.h"
#include "common/robot/gripper/gripper.h"

// const int SETTING_MODE = 2;

Timer doCoolRotation;
Timer test;

void setup()
{
  Serial.begin(9600);
  blueTooth.begin(9600);
  setupMotor();
  setupSonar();
  setupGripper();
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

  // ========== gripper =============
  gripper(0);

  float d = getDistanceCM();

  if (d < 10 && d > 0) {                  // 0 < distance < 10
      gripperCatch();                     // close gripper
  }

  if (d > 20) {                           // distance > 20
      gripperUnCatch();                   // open gripper
  }

  //========== avoiding =============

  // static bool safeZone = true;

  // float distance = getDistanceCM();

  // if (!avoiding) {

  //   if (safeZone && distance <= 20 && distance >= 2) {
  //     safeZone = false;                   // exiting safe zone
  //     avoidObstacleSmoothNonBlocking(255);
  //   }
  //   else {
  //     moveForward(255);

  //     if (distance > 20) {                
  //       safeZone = true;                
  //     }
  //   }
  // } else {
  //   avoidObstacleSmoothNonBlocking(255);
  // }

  //==============================

  // testBasicMovement();

  // if (current > 20)
  // {
  //   digitalWrite(PINS_MOTOR[0], LOW);
  //   digitalWrite(PINS_MOTOR[1], LOW);
  //   digitalWrite(PINS_MOTOR[2], LOW);
  //   digitalWrite(PINS_MOTOR[3], LOW);

  //   Serial.println("Its working");
  // }

  // currenRstData[3].mean + 20 > storedRsData[3].mean &&storedRsData[3].mean - 20 < currenRstData[3].mean

  // Serial.println("why we stopped working");

  // testPulses(20);
}