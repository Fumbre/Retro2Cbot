#include <Arduino.h>
#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"
#include "common/time/TimeApp.h"

const int SETTING_MODE = 2;

void setup()
{
  Serial.begin(9600);
  setupMotor();

  // moveForward(255);
}
unsigned long Rotatestamp = millis();
unsigned long Forwardstamp = millis();
unsigned long stopStamp = millis();

void loop()
{
  bool rotate = isTimeInterval(&Rotatestamp, 1500, 500);
  bool goForward = isTimeInterval(&Forwardstamp, 500, 1000);

  if (goForward)
  {
    moveForward(255, true);
  }
  if (rotate)
  {
    rotateLeft(255, true);
  }

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
