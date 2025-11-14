/**
 * @name the basic functions of robots
 * @authors Sunny & Nicolo
 * @date 10-11-2025
 */
#include "common/robot/movement/movement.h"

volatile long leftPulsesCount = 0;
volatile long rightPulsesCount = 0;

//PID factors
float Kp = 0.55;    // Proportional
float Ki = 0.005;    // Integral
float Kd = 0.45;    // Derivative

long lastError = 0;
float integral = 0;
unsigned long lastPIDTime = 0;
const unsigned long PID_INTERVAL = 10;
bool isMovingForward = true;

void countleftRotation()
{
  leftPulsesCount++;
  
}

void countRightRotation()
{
  rightPulsesCount++;
}

/**
 * @name set wheel pins in Arduino
 * @author Sunny
 * @date 10-11-2025
 */
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

/**
 * @name getPWMvalue
 * @author Sunny
 * @date 11-11-2025
 * @param speed
 *
 * @details  that function calclulate procantage of speed for analogWrite(255) is max speed is in procatage
 * so we will have correcrt procatage based on max value of PWM_VALUE
 *
 * @return PWM value
 */
int getPWMvalue(int speed)
{
  speed = constrain(speed, 0, FULL_SPEED); // if more than full speed put full speed variable [100%]
  float value = (float)speed / 100.0;
  return (int)round(value * FULL_PWM_VALUE); // 0.80 * 255 = 204 * 0.97
}

/**
 * @name moveForward
 * @author Nicolo
 * @date 10-11-2025
 * @param speed
 */
void moveForward(int speed)
{
  isMovingForward = true;
  int pwmValue = getPWMvalue(speed);
  // static int rightPWM = 0;
  // static int leftPWM = 0;
  // if (leftPWM == 0 && rightPWM == 0) {
  //     leftPWM  = round(pwmValue * MOTOR_LEFT_FACTOR);
  //     rightPWM = round(pwmValue * MOTOR_RIGHT_FACTOR);
  // }
  int leftPWM = pwmValue;
  int rightPWM = pwmValue;
 // adjustPWMvalueByPulse(leftPWM,rightPWM);
  analogWrite(LEFT_DIRECTION_FORWARD_PIN, leftPWM);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
  analogWrite(RIGHT_DIRECTION_FORWARD_PIN, rightPWM);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN, LOW);
}

/**
 * @name moveBackward
 * @author Nicolo
 * @date 10-11-2025
 * @param speed
 */
void moveBackward(int speed)
{
  isMovingForward = false;
  // get PWM value
  int pwmValue = getPWMvalue(speed);
  // static int rightPWM = 0;
  // static int leftPWM = 0;
  // if (leftPWM == 0 && rightPWM == 0) {
  //       leftPWM  = round(pwmValue * MOTOR_LEFT_FACTOR);
  //       rightPWM = round(pwmValue * MOTOR_RIGHT_FACTOR);
  //   }
  int leftPWM = pwmValue;
  int rightPWM = pwmValue;
 // adjustPWMvalueByPulse(leftPWM,rightPWM);
  leftPWM = constrain(leftPWM, 0, FULL_PWM_VALUE);
  rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
  analogWrite(LEFT_DIRECTION_BACKWARD_PIN, leftPWM);
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN, LOW);
  analogWrite(RIGHT_DIRECTION_BACKWARD_PIN, rightPWM);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, LOW);
}

/**
 * @name switchDirection
 * @author Sunny
 * @date 10-11-2025
 * @param leftSpeed
 * @param rightSpeed
 */
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

/**
 * @name stopMotors
 * @author Nicolo
 * @date 10-11-2025
 */
void stopMotors()
{
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN, LOW);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN, LOW);
}

/**
 * @name rotate
 * @author Sunny
 * @date 12-11-2025
 * @param speed (0-100%)
 * @param direction (left, right)
 * @param angle (0-360)
 */
void rotate(int speed, String direction,float angle)
{
  // reset encoder count
  leftPulsesCount = 0;
  rightPulsesCount = 0;
  // caculate the max number of rotation of wheels for rotate 180 degrees
  angle = constrain(angle,0.0,360.0);
  float turns = ((angle / 360.0)*(2.0*ROBOT_RADUIS * PI)) / (2.0 * PI * WHEEL_RADUIS);
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
  // waiting rotate finish
  while (leftPulsesCount <= targetPulses || rightPulsesCount <= targetPulses);
  stopMotors();
}

void adjustPWMvalueByPulse(int &leftPWMValue, int &rightPWMValue){
   unsigned long now = millis();
  if (now - lastPIDTime < PID_INTERVAL) return;

  // caculate diference
  long error = leftPulsesCount - rightPulsesCount;
   // adjust PWM values for backward or forward
  // caculate PID value
  integral += error;
  integral = constrain(integral,-50,50);
  long derivative = error - lastError;
  float correction = Kp * error + Ki * integral + Kd * derivative;

  if (isMovingForward) {
    leftPWMValue  = constrain(leftPWMValue  + correction / 4, 0, FULL_PWM_VALUE);
    rightPWMValue = constrain(rightPWMValue - correction / 4, 0, FULL_PWM_VALUE);
} else { // Moving backward
    leftPWMValue  = constrain(leftPWMValue  - correction / 4, 0, FULL_PWM_VALUE);
    rightPWMValue = constrain(rightPWMValue + correction / 4, 0, FULL_PWM_VALUE);
}

  // update variables
  lastError = error;
  leftPulsesCount = 0;
  rightPulsesCount = 0;
  lastPIDTime = now;
}