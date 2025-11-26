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

const int SETTING_MODE = 2;

Timer doCoolRotation;
Timer test;

void setup()
{
  Serial.begin(9600);
  setupMotor();
  setupSonar();
}

void loop()
{
  setupPulseCounter();

  calibrateRS();

  // testBasicMovement();
  // moveSpeed(230, 230);

  // testPulses(20);
}