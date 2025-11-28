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
#include "common/tools/tests/test_pulses.h"

#include "common/robot/neopixel/neopixel.h"
#include "common/robot/movement/movementPID.h"
#include "maps_pogram/maze_line/maze_line.h"

const int SETTING_MODE = 2;

void setup()
{
  Serial.begin(9600);
  blueTooth.begin(9600);
  setupMotor();
  setupSonar();
  initNeopixelPins();
}

Timer test;

void loop()
{
  // moveStabilized(230, 230);
  testBasicMovement();

  // if (test.executeOnce(0))
  // {
  //   int index[] = {0, 1};
  //   turnOnSomeLeds(index, 2, 54, 154, 12);
  // }

  // if (test.timeout(10))
  // {
  //   moveForward(100);
  // }

  // if (!test.interval(500, 500))
  // {
  //   turnOnSomeLeds(index, 2, 54, 154, 12);
  // }
  // else
  // {
  //   turnOnSomeLeds(index, 2, 255, 175, 0);
  // }

  // testPulses(20);
}