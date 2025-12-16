#include "common/constant/robot.h"
#include "common/tools/bluetooth.h"
#include <Arduino.h>
#include "common/robot/neopixel/neopixel.h"
#include "maps_pogram/maze_line/maze_line.h"

#include "maps_pogram/follow_single_line/follow_single_line.h"

int mapInit = 1;

void setup()
{
  Serial.begin(9600);
  blueTooth.begin(9600);
  // #ifdef BB046
  // TODO: followLineSetup()
  // #endif
  followLineSetup();
  initNeopixelPins();
}

void loop()
{
  switch (mapInit)
  {
  // case 0:
  //   if (startSequencePassed)
  //   {
  //     mapInit += SETTING_MODE;
  //   }
  //   break;
  case 1:
    followLineSequence();
    break;
  case 2:
    mazeLine();
    break;
  }
}