/**
 * @name the basic functions of robots
 * @authors Sunny & Nicolo
 * @date 10-11-2025
 */
#include "../../constant/Robot.h"
#include <Arduino.h>

float leftFactor = 1.0;
float rightFactor = 1.08;

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

/**
 * 
 */
int getPWMvalue(int speed){
  float value = (float)speed/100;
  return (int)round(value * 255);
}


// Move forward
void moveForward(int speed) {
   int pwmValue = getPWMvalue(speed);
   int leftPwmValue = round(pwmValue*leftFactor) > FULL_PWM_VALUE ? FULL_PWM_VALUE : round(pwmValue*leftFactor);
   int rightPwmValue = round(pwmValue*rightFactor) > FULL_PWM_VALUE ? FULL_PWM_VALUE : round(pwmValue*rightFactor);
   analogWrite(LEFT_DIRECTION_FORWARD_PIN,leftPwmValue);
   digitalWrite(LEFT_DIRECTION_BACKWARD_PIN,LOW);
   analogWrite(RIGHT_DIRECTION_FORWARD_PIN,rightPwmValue);
   digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN,LOW);
}

// Move backward
void moveBackward(int speed) {
   int pwmValue = getPWMvalue(speed);
   int leftPwmValue = round(pwmValue*leftFactor) > FULL_PWM_VALUE ? FULL_PWM_VALUE : round(pwmValue*leftFactor);
   int rightPwmValue = round(pwmValue*rightFactor) > FULL_PWM_VALUE ? FULL_PWM_VALUE : round(pwmValue*rightFactor);
   analogWrite(LEFT_DIRECTION_BACKWARD_PIN,leftPwmValue);
   digitalWrite(LEFT_DIRECTION_FORWARD_PIN,LOW);
   analogWrite(RIGHT_DIRECTION_BACKWARD_PIN,rightPwmValue);
   digitalWrite(RIGHT_DIRECTION_FORWARD_PIN,LOW);
}  



/**
 * @name switchDirection
 * @author Sunny
 * @date 10-11-2025
 * @param leftSpeed,rightSpeed
 */
void switchDirection(int leftSpeed ,int rightSpeed){
    int leftValue = getPWMvalue(leftSpeed);
    int rightValue = getPWMvalue(rightSpeed);
    int leftPWMValue = round(leftValue*leftFactor) > FULL_PWM_VALUE ? FULL_PWM_VALUE : round(leftValue*leftFactor);
    int rightPWMValue = round(rightValue*rightFactor) > FULL_PWM_VALUE ? FULL_PWM_VALUE : round(rightValue*rightFactor);
    //put left wheel pin
    analogWrite(LEFT_DIRECTION_FORWARD_PIN,leftPWMValue);
    digitalWrite(LEFT_DIRECTION_BACKWARD_PIN,LOW);
    //put right wheel pin
    analogWrite(RIGHT_DIRECTION_FORWARD_PIN,rightPWMValue);
    digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN,LOW);
}


void stopMotors(){
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN,LOW);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN,LOW);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN,LOW);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN,LOW);
}
