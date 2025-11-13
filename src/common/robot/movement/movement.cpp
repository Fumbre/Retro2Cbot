#include "common/robot/movement/movement.h"

volatile long leftPulsesCount = 0;
volatile long rightPulsesCount = 0;

void countleftRotation()
{
  leftPulsesCount++;
}

void countRightRotation()
{
  rightPulsesCount++;
}

void initWheelsPin()
{
  // initialize wheels pin
  int length = sizeof(WHEEL_PIN_ARRAY) / sizeof(WHEEL_PIN_ARRAY[0]);
  for (int i = 0; i < length; i++)
  {
    pinMode(WHEEL_PIN_ARRAY[i], OUTPUT);
  }
  // initialize rotation sensor pins
  pinMode(LEFT_ROTATION_PIN, INPUT_PULLUP);
  pinMode(RIGHT_ROTATION_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_ROTATION_PIN), countleftRotation, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ROTATION_PIN), countRightRotation, RISING);
}

int getPWMvalue(int speed)
{
  speed = constrain(speed, 0, FULL_SPEED); // if more than full speed put full speed variable [100%]
  float value = (float)speed / 100.0;
  return (int)round(value * FULL_PWM_VALUE); // 0.80 * 255 = 204 * 0.97
}

void moveForward(int speed)
{
  // int pwmValue = getPWMvalue(speed);
  // int leftPWM = round(pwmValue * MOTOR_LEFT_FACTOR);
  // int rightPWM = round(pwmValue * MOTOR_RIGHT_FACTOR);
  // leftPWM = constrain(leftPWM, 0, FULL_PWM_VALUE);
  // rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
  analogWrite(LEFT_DIRECTION_FORWARD_PIN, 255);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
  analogWrite(RIGHT_DIRECTION_FORWARD_PIN, 245);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN, LOW);
}

// Move backward
void moveBackward(int speed)
{
  // get PWM value
  int pwmValue = getPWMvalue(speed);
  int rightPWM = round(pwmValue * MOTOR_LEFT_FACTOR);
  int leftPWM = round(pwmValue * MOTOR_RIGHT_FACTOR);
  leftPWM = constrain(leftPWM, 0, FULL_PWM_VALUE);
  rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
  analogWrite(LEFT_DIRECTION_BACKWARD_PIN, leftPWM);
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN, LOW);
  analogWrite(RIGHT_DIRECTION_BACKWARD_PIN, rightPWM);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, LOW);
}

void switchDirection(int leftSpeed, int rightSpeed)
{
  int leftValue = getPWMvalue(leftSpeed);
  int rightValue = getPWMvalue(rightSpeed);
  int leftPWM = round(leftValue * MOTOR_LEFT_FACTOR);
  int rightPWM = round(rightValue * MOTOR_RIGHT_FACTOR);
  leftPWM = constrain(leftPWM, 0, FULL_PWM_VALUE);
  rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
  // put left wheel pin
  analogWrite(LEFT_DIRECTION_FORWARD_PIN, leftPWM);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
  // put right wheel pin
  analogWrite(RIGHT_DIRECTION_FORWARD_PIN, rightPWM);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN, LOW);
}

void stopMotors()
{
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN, LOW);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN, LOW);
}

void rotate180(int speed, String direction)
{
  // reset encoder count
  leftPulsesCount = 0;
  rightPulsesCount = 0;
  // caculate the max number of rotation of wheels for rotate 180 degrees
  float turns = (ROBOT_RADUIS * PI) / (2.0 * PI * WHEEL_RADUIS);
  // caculate the max number of pulses for rotating 180 degrees
  int targetPulses = round(turns * PPR);
  // get PWM value
  int pwmValue = getPWMvalue(speed);
  if (direction.equalsIgnoreCase("right"))
  {
    // let right wheel go forward, let left wheel go backward
    analogWrite(LEFT_DIRECTION_FORWARD_PIN, pwmValue);
    digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
    analogWrite(RIGHT_DIRECTION_BACKWARD_PIN, pwmValue);
    digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, LOW);
  }
  else if (direction.equalsIgnoreCase("left"))
  {
    // let right wheel go forward, let left wheel go backward
    analogWrite(RIGHT_DIRECTION_FORWARD_PIN, pwmValue);
    digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN, LOW);
    analogWrite(LEFT_DIRECTION_BACKWARD_PIN, pwmValue);
    digitalWrite(LEFT_DIRECTION_FORWARD_PIN, LOW);
  }
  Serial.println(targetPulses);
  // waiting rotate finish
  while (leftPulsesCount <= targetPulses || rightPulsesCount <= targetPulses)
    ;
  stopMotors();
}