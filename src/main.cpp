#include "common/constant/robot.h"
#include "common/tools/bluetooth.h"
#include <Arduino.h>
#include "common/robot/neopixel/neopixel.h"
#include "maps_pogram/maze_line/maze_line.h"

#include "maps_pogram/follow_single_line/follow_single_line.h"

#include "maps_pogram/physical_maze/physical_maze.h"

#include "common/tools/tests/test_sonar/test_sonar.h"

int mapInit = 2;

void setup()
{
  Serial.begin(9600);
  blueTooth.begin(9600);
  initNeopixelPins();
  switch (mapInit)
  {
  case 1:
    followLineSetup();
    break;
  case 2:
    mazeLineSetup();
    break;
  case 3:
    physicalMazeSetup();
    break;
  }
}

void loop()
{
  switch (mapInit)
  {
  // case 0:
  //  for this case figure out something use define or variable
  //   if (startSequencePassed)
  //   {
  //     mapInit += SETTING_MODE;
  //   }
  //   break;
  case 1:
    followLine();
    break;
  case 2:
    mazeLine();
    break;
  case 3:
    physicalMaze();
    break;
  }
}