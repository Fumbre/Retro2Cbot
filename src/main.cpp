#include "common/constant/robot.h"
#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/robot/sonar/sonar.h"
#include <Arduino.h>
#include "common/tools/timer.h"
#include "common/tools/tests/test_basic_movements/test_basic_movements.h"
#include "common/tools/tests/test_reflective_sensor/test_reflective_sensor.h"
#include "common/tools/tests/test_pulses.h"

#include "maps_pogram/maze_line/maze_line.h"

#include "common/robot/movement/movementPID.h"

const int SETTING_MODE = 2;

Timer doCoolRotation;
Timer test;

void setup()
{
  Serial.begin(9600);
  setupMotor();
  setupSonar();
}

Timer t;
Timer t1;

bool flag = true;

void loop()
{

  // testBasicMovement();

  // moveStabilized(-240, -240);

  // if (t.executeOnce(0, 1000))
  // {
  //   moveStabilized(240, 240);
  // }

  if (t.executeOnce(0, 500))
  {
    // Serial.print("asfdasdf");
    moveStabilized(-255, -255);
  }
  if (t1.timeout(500) && flag)
  {
    if (didMoveRight(255, 36))
    {
      flag = false;
      resetMoveRight();
      stopMotors();
    }
  }

  // moveLeft(180, 36);

  // testPulses(20);
}