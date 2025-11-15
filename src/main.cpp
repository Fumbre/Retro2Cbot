#include <Arduino.h>
#include "common/robot/movement/movement.h"
#include "motors/stability.h"
#include "common/tools/timer.h" 

const int SETTING_MODE = 2;

Timer rotateTimer;
Timer time;
Timer IDEA;
Timer IDEA2;

void setup()
{
  Serial.begin(9600);
  initWheelsPin();
  //initRotationPins();
  delay(2000);
}

void loop()
{
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
  // delay(3000);



// ==================================================================

// if (!IDEA2.every(1500, 3000)) {
  
// }
  
 
//     if(rotateTimer.every(20)) {
//     rotate(100,"left",20);
//   }
//   if(!rotateTimer.every(20)) {
//     rotate(100,"right",20);
//   }


  // if(rotateTimer.timeout(600)) {
  //   stopMotors();
  //   // rotateTimer.resetEvery();
  // }

  // if (rotateTimer.timeout(600) && time.once(600) ) {
  //   rotate(100,"right",90);
  // }

  //   if (rotateTimer.timeout(600) && time.every(20) && !IDEA.timeout(1200)) {
  //   rotate(100,"right",90);
  // }

  // if(time.timeout(1200)) {
  //   stopMotors();
  //   IDEA.resetTimeout();
  // }



  // =================================================================


  rotate(100,"left",90);
  delay(2000);


  // moveBackward(100);
}
