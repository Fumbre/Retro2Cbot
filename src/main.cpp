#include "common/constant/robot.h"
#include "common/tools/bluetooth.h"
#include <Arduino.h>
#include "common/robot/neopixel/neopixel.h"
#include "maps_pogram/maze_line/maze_line.h"

#include "maps_pogram/follow_single_line/follow_single_line.h"

#include "common/tools/tests/test_sonar/test_sonar.h"

int mapInit = 1;

void setup()
{
  Serial.begin(9600);
  // blueTooth.begin(9600);
  // #ifdef BB046
  // TODO: followLineSetup()
  // #endif
  // setupMotor();
  // setupSonar();
  // initNeopixelPins();
  // mazeLineSetup();
  followLineSetup();
}

void loop()
{
  testSonar();
  switch (mapInit)
  {
  // case 0:
  //   if (startSequencePassed)
  //   {
  //     mapInit += SETTING_MODE;
  //   }
  //   break;
  case 1:
    followLine();
    break;
  case 2:
    // mazeLine();
    break;
  }
}