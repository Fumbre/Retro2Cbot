/**
 * @name the basic functions of robots
 * @authors Sunny & Nicolo
 * @date 10-11-2025
 */
#include "../../constant/Robot.h"
#include <Arduino.h>

float leftFactor = 1.00;
float rightFactor = 1.00;

volatile long leftRotationCount = 0;
volatile long rightRotationCount = 0;

void countleftRotation(){
  leftRotationCount++;
}

void countRightRotation(){
  rightRotationCount++;
}

/**
 * @name set wheel pins in Arduino
 * @author Sunny
 * @date 10-11-2025
 */
void initWheelsPin(){
    //initialize wheels pin
    int length = sizeof(WHEEL_PIN_ARRAY)/sizeof(WHEEL_PIN_ARRAY[0]);
    for (int i = 0; i < length; i++){
      pinMode(WHEEL_PIN_ARRAY[i],OUTPUT);
    }
    //initialize rotation sensor pins
    pinMode(LEFT_ROTATION_PIN,INPUT_PULLUP);
    pinMode(RIGHT_ROTATION_PIN,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(LEFT_ROTATION_PIN),countleftRotation,RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_ROTATION_PIN),countRightRotation,RISING);
}

/**
 * @name getPWMvalue
 * @author Sunny
 * @date 11-11-2025
 * @param speed
 * @return PWM value
 */
int getPWMvalue(int speed){
  speed = constrain(speed, 0, FULL_SPEED);
  float value = (float)speed / 100.0;
  return (int)round(value * FULL_PWM_VALUE);
}

float getLeftFactor(int speed){
  return leftFactor;
}

/**
 * 
 */
float getRightFactor(int speed){
  return map(speed,0,FULL_PWM_VALUE,98,99) / 100.0;
}


// Move forward
void moveForward(int speed) {
   int pwmValue = getPWMvalue(speed);
   int leftPWM  = round(pwmValue * getLeftFactor(speed));
   int rightPWM = round(pwmValue * getRightFactor(speed));
   leftPWM  = constrain(leftPWM, 0, FULL_PWM_VALUE);
   rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
   analogWrite(LEFT_DIRECTION_FORWARD_PIN,leftPWM);
   digitalWrite(LEFT_DIRECTION_BACKWARD_PIN,LOW);
   analogWrite(RIGHT_DIRECTION_FORWARD_PIN,rightPWM);
   digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN,LOW);
}

// Move backward
void moveBackward(int speed) {
   int pwmValue = getPWMvalue(speed);
   int leftPWM  = round(pwmValue * getLeftFactor(speed));
   int rightPWM = round(pwmValue * getRightFactor(speed));
   leftPWM  = constrain(leftPWM, 0, FULL_PWM_VALUE);
   rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
   analogWrite(LEFT_DIRECTION_BACKWARD_PIN,leftPWM);
   digitalWrite(LEFT_DIRECTION_FORWARD_PIN,LOW);
   analogWrite(RIGHT_DIRECTION_BACKWARD_PIN,rightPWM);
   digitalWrite(RIGHT_DIRECTION_FORWARD_PIN,LOW);
}  



/**
 * @name switchDirection
 * @author Sunny
 * @date 10-11-2025
 * @param leftSpeed
 * @param rightSpeed
 */
void switchDirection(int leftSpeed ,int rightSpeed){
    int leftValue = getPWMvalue(leftSpeed);
    int rightValue = getPWMvalue(rightSpeed);
    int leftPWM  = round(leftValue * getLeftFactor(leftSpeed));
    int rightPWM = round(rightValue * getRightFactor(rightSpeed));
    leftPWM  = constrain(leftPWM, 0, FULL_PWM_VALUE);
    rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
    //put left wheel pin
    analogWrite(LEFT_DIRECTION_FORWARD_PIN,leftPWM);
    digitalWrite(LEFT_DIRECTION_BACKWARD_PIN,LOW);
    //put right wheel pin
    analogWrite(RIGHT_DIRECTION_FORWARD_PIN,rightPWM);
    digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN,LOW);
}

/**
 * @name stopMotors
 * @author Nicolo
 * @date 10-11-2025
 */
void stopMotors(){
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN,LOW);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN,LOW);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN,LOW);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN,LOW);
}

void rotateLeft180(int speed){
  leftRotationCount = 0;
  rightRotationCount = 0;
}
