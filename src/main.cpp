#include <Arduino.h>
#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"

const int SETTING_MODE = 2;

void setup() {
  Serial.begin(9600);
  Motor();
  delay(1000);

  // Sequence of movements
  moveForward(1.0);         // move forward 1 meter
  moveBackward(1.0);        // move backward 1 meter
  moveRight();              // move forward turning right
  moveLeft();               // move forward turning left
  rotateRight90();          // rotate 90° right
  rotateLeft90();           // rotate 90° left
  rotate180();              // rotate 180°
  moveUntilObstacle(30);    // move forward until 30 cm from obstacle
  moveStop();               // stop completely
}

void loop() {
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
