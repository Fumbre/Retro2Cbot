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
#include "common/robot/reflective_sensor/reflective_sensor.h"

const int SETTING_MODE = 2;

void setup()
{
  Serial.begin(9600);
  blueTooth.begin(9600);
  setupMotor();
  setupSonar();
  initNeopixelPins();
  initReflectiveSensorPins();
}

int test[] = {1, 2, 3};

Timer t;
void loop()
{
  // if (t.interval(1000, 1000))
  // {
  //   turnOnSomeLeds(test, 3, 255, 0, 0);
  // }
  // else
  // {
  //   turnOnSomeLeds(test, 3, 0, 255, 0);
  // }
  // moveForward(100);
  WheelSpeed speed = checkLine(100);
  switchDirection(speed.leftPWM, speed.rightPWM);
}