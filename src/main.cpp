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
  // initNeopixelPins();
}

Timer test;

void loop()
{
  followLine();

  // moveStabilized(230, 230);

  // Serial.println(currenRstData[3].mean);

  // double current = currenRstData[3].mean - storedRsData[3].mean < 0 ? (currenRstData[3].mean - storedRsData[3].mean) * -1 : currenRstData[3].mean - storedRsData[3].mean;
  // Serial.println(current);

  // Serial.println(storedRsData[3].mean + reflectiveDifference > currenRstData[3].mean && currenRstData[3].mean - reflectiveDifference < storedRsData[3].mean);

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