#include "common/constant/robot.h"
#include "common/robot/motor/motor.h"
#include "common/tools/bluetooth.h"
#include <Arduino.h>
#include "common/robot/neopixel/neopixel.h"
#include "maps_pogram/maze_line/maze_line.h"

#include "maps_pogram/follow_single_line/follow_single_line.h"

int mapInit = 2;

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
  switch (SETTING_MODE)
  {
  case 2:
    followLineSequence();
    break;
  }

  // if (detectSquer())
  // {
  //   detected = true;
  //   if (test.executeOnce(0))
  //   {
  //     resetMoveLeft();
  //   }
  // }

  // if (detected)
  // {
  //   if (didMoveLeft(200, 9))
  //   {
  //     detected = false;
  //     test.resetExecuteOnce();
  //       }
  // }
  // else
  // {
  //   moveForward(75);
  // }

  // moveStabilized(230, 230);
  // testBasicMovement();

  // huj.getDifference(huj.reflectiveRead, 20);

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