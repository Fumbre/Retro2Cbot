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
    pinMode(LEFT_SPEED_PIN,OUTPUT);
    pinMode(RIGHT_SPEED_PIN,OUTPUT);
    pinMode(LEFT_DIRECTION_PIN1,OUTPUT);
    pinMode(LEFT_DIRECTION_PIN2,OUTPUT);
    pinMode(RIGHT_DIRECTIONL_PIN1,OUTPUT);
    pinMode(RIGHT_DIRECTIONL_PIN2,OUTPUT);
}

// Move forward
void moveForward(int speed, int duration) {
  digitalWrite(LEFT_DIRECTION_PIN1, HIGH);
  digitalWrite(RIGHT_DIRECTIONL_PIN1, HIGH);
  analogWrite(LEFT_SPEED_PIN, speed);
  analogWrite(RIGHT_SPEED_PIN, speed);
  delay(duration);
  stopMotors();
}

// Move backward
void moveBackward(int speed, int duration) {
  digitalWrite(LEFT_DIRECTION_PIN1, LOW);
  digitalWrite(RIGHT_DIRECTIONL_PIN1, LOW);
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
    digitalWrite(LEFT_DIRECTION_PIN1,HIGH);
    digitalWrite(LEFT_DIRECTION_PIN2,LOW);
    //put right wheel pin
    digitalWrite(RIGHT_DIRECTIONL_PIN1,HIGH);
    digitalWrite(RIGHT_DIRECTIONL_PIN2,LOW);
}


void stopMotors(){
  
}