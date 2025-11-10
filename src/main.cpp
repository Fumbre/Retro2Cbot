#include <Arduino.h>
#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"

const int SETTING_MODE = 2;

void setup()
{
  Serial.begin(9600);
  setupMotor();

  moveForward(true);
}

void loop()
{
  switch (SETTING_MODE)
  {
  case 0:
    // to do followSingleLine
    break;
  case 1:
    // to do mazeLine
    break;
  case 2:
    // to do physicalMaze
    break;

  default:
    Serial.print("NO SUCH A PROGRAM");
    break;
  }
}
