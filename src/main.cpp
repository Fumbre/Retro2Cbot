#include <Arduino.h>
#include "common/robot/movement/movement.h"
#include "motors/stability.h"
#include "common/robot/sensors/ultrasonic.h"

const int SETTING_MODE = 2;

void setup()
{
  Serial.begin(9600);

    initWheelsPin();                  // (se estiver a ser usado)
    initRotationPins();               // encoders
    StartSpeedControl();      // controlo PID simples
    initUltrasonic();                 

    delay(2000);
}

void loop()
{
  // Checks if an obstacle is detected within 30 cm
  if (isObstacleDetected(30.0)) {  

    Serial.println("Obstacle! Retreat...");     // Prints a warning message to the serial monitor
    stopMotors();                               // Immediately stops both motors
    delay(200);                                 // Waits 200 ms to stabilize the robot

    // Move backward for 500 ms
    unsigned long t = millis();                 // Saves the current time (start of the backward motion)
    while (millis() - t < 500) {                // Loops until 500 ms have passed
      moveBackward(80);                         // Moves the robot backward at 80% speed
    }

    stopMotors();                               // Stops motors after reversing
    delay(200);                                 // Short pause before turning

    // Turn right for 600 ms
    Serial.println("Turning...");               // Prints a message indicating a turn
    t = millis();                               // Resets the timer for the turning action
    while (millis() - t < 600) {                // Loops until 600 ms have passed
      switchDirection(80, 20);                  // Makes the robot turn right (left wheel faster than right)
    }

    stopMotors();                               // Stops motors after turning
    delay(200);                                 // Final stabilization pause
}

    // seguir em frente com correcção pelos encoders
    MoveFrontControlled(80);
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
  // delay(2000);
  testPulses();
  MoveFrontControlled(80);  // 80% de velocidade
  // delay(2000);
  // moveBackward(100);

  // moveForward(80);
  // stopMotors();
  // delay(2000);
}