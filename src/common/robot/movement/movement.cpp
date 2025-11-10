/**
 * @name the basic functions of robots
 * @authors Sunny & Nicolo
 * @date 10-11-2025
 */
#include "../../constant/Robot.h"
#include <Arduino.h>

/**
 * @name set wheel pins in Arduino
 * @author Sunny
 */
void initWheelsPin(){
    int length = sizeof(WHEEL_PIN_ARRAY)/sizeof(WHEEL_PIN_ARRAY[0]);
    for (int i = 0; i < length; i++){
      pinMode(WHEEL_PIN_ARRAY[i],OUTPUT);
    }
    
}

// Move forward
void moveForward(int speed, int duration) {
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN, HIGH);
  digitalWrite(RIGHT_DIRECTIONL_FORWARD_PIN, HIGH);
  analogWrite(LEFT_SPEED_PIN, speed);
  analogWrite(RIGHT_SPEED_PIN, speed);
  delay(duration);
  stopMotors();
}

// Move backward
void moveBackward(int speed, int duration) {
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTIONL_FORWARD_PIN, LOW);
  analogWrite(LEFT_SPEED_PIN, speed);
  analogWrite(RIGHT_SPEED_PIN, speed);
  delay(duration);
  stopMotors();
}  



/**
 * @name switchDirection
 * @author Sunny
 * @date 10-11-2025
 * @param leftSpeed,rightSpeed
 */
void switchDirection(int leftSpeed ,int rightSpeed){
    //put left speed
    analogWrite(LEFT_SPEED_PIN,leftSpeed);
    //put right speed
    analogWrite(RIGHT_SPEED_PIN,rightSpeed);
    //put left wheel pin
    digitalWrite(LEFT_DIRECTION_FORWARD_PIN,HIGH);
    digitalWrite(LEFT_DIRECTION_BACKWARD_PIN,LOW);
    //put right wheel pin
    digitalWrite(RIGHT_DIRECTIONL_FORWARD_PIN,HIGH);
    digitalWrite(RIGHT_DIRECTIONL_BACKWARD_PIN,LOW);
}


void stopMotors(){
  
}