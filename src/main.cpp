#include <Arduino.h>
#include "common/robot/movement/movement.h"

const int SETTING_MODE = 2;

void setup() {
  Serial.begin(9600);
  initWheelsPin();
  delay(2000);
}

void loop() {
  // switch (SETTING_MODE)
  // {
  // case 0:
  //   // to do followSingleLine
  //   break;
  // case 1:
  //   // to do mazeLine
  //   break;
  // case 2:
  //   // to do physicalMaze
  //   break;  

  // default:
  //   Serial.print("NO SUCH A PROGRAM");
  //   break;
  // }
  // unsigned long currentTime = millis();
  // //go forward
  // while(true){
  //   moveForward(80);
  //   if(millis() - currentTime > 5000){
  //     break;
  //   }
  // }
  // currentTime = millis();
  // //turn left
  //  while(true){
  //   switchDirection(20,80);
  //   if(millis() - currentTime > 1500){
  //     break;
  //   }
  // }
  // currentTime = millis();
  //  //go forward
  // while(true){
  //   moveForward(80);
  //   if(millis() - currentTime > 5000){
  //     break;
  //   }
  // }
  // currentTime = millis();
  // //turn right
  // while(true){
  //   switchDirection(80,20);
  //   if(millis() - currentTime > 1500){
  //     break;
  //   }
  // }
  // currentTime = millis();
  //  //go backward
  // while(true){
  //   moveBackward(80);
  //   if(millis() - currentTime > 5000){
  //     break;
  //   }
  // }
  delay(2000);
  rotate180(0,"left");
  delay(2000);
  rotate180(50,"right");

  // moveForward(80);
  //stopMotors();
  //delay(2000);
}
