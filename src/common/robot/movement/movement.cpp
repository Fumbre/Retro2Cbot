/**
 * @name the basic functions of robots
 * @authors Sunny & Nicolo
 * @date 10-11-2025
 */
#include "common/robot/movement/movement.h"

// PID factors
float Kp = 0.02;  // Proportional
float Ki = 0.009; // Integral
float Kd = 0.05;  // Derivative

float lastError = 0;
float integral = 0;
unsigned long lastPIDTime = 0;
const unsigned long PID_INTERVAL = 10;
bool isMovingForward = true;
bool pidStarted = false;

int leftPWM = 0;
int rightPWM = 0;

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
 * @author Sunny
 * @date 10-11-2025
 * @param speed
 */
void moveForward(int speed)
{
  isMovingForward = true;
  int pwmValue = getPWMvalue(speed);

  leftPWM = pwmValue;
  rightPWM = pwmValue;
  adjustPWMvalueByPulse(leftPWM, rightPWM);
  analogWrite(PIN_MOTOR_LEFT_FORWARD, leftPWM);
  digitalWrite(PIN_MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD, rightPWM);
  digitalWrite(PIN_MOTOR_RIGHT_BACKWARD, LOW);
}

/**
 * @name moveBackward
 * @author Sunny
 * @date 10-11-2025
 * @param speed
 */
void moveBackward(int speed)
{
  isMovingForward = false;

  // get PWM value
  int pwmValue = getPWMvalue(speed);

  leftPWM = pwmValue;
  rightPWM = pwmValue;
  adjustPWMvalueByPulse(leftPWM, rightPWM);
  leftPWM = constrain(leftPWM, 0, FULL_PWM_VALUE);
  rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
  analogWrite(PIN_MOTOR_LEFT_BACKWARD, leftPWM);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD, LOW);
  analogWrite(PIN_MOTOR_RIGHT_BACKWARD, rightPWM);
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD, LOW);
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
  leftPWM = constrain(leftValue, 0, FULL_PWM_VALUE);
  rightPWM = constrain(rightValue, 0, FULL_PWM_VALUE);
  // put left wheel pin
  analogWrite(PIN_MOTOR_LEFT_FORWARD, leftPWM);
  digitalWrite(PIN_MOTOR_LEFT_BACKWARD, LOW);
  // put right wheel pin
  analogWrite(PIN_MOTOR_RIGHT_FORWARD, rightPWM);
  digitalWrite(PIN_MOTOR_RIGHT_BACKWARD, LOW);
}

/**
 * @name stopMotors
 * @author Fumbre (Vladyslav)
 * @date 10-11-2025
 */
void stopMotors()
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    digitalWrite(PINS_MOTOR[i], LOW);
  }
}

/**
 * @name rotate
 * @author Sunny
 * @date 12-11-2025
 * @param speed (0-100%)
 * @param direction (left, right)
 * @param angle (0-360)
 */
void rotate(int speed, String direction, float angle)
{
  isMovingForward = true;
  // reset encoder count
  motor_left_pulses_counter = 0;
  motor_right_pulses_counter = 0;
  // caculate the max number of rotation of wheels for rotate 180 degrees
  angle = constrain(angle, 0.0, 360.0);
  float rotateDistance = (angle / 360.0) * (2 * PI * ROBOT_RADUIS);
  float wheelTurns = rotateDistance / (2 * PI * WHEEL_RADUIS);
  int targetPulses = wheelTurns * PPR;
  // get PWM value
  int pwmValue = getPWMvalue(speed);
  leftPWM = pwmValue;
  rightPWM = pwmValue;
  adjustPWMvalueByPulse(leftPWM, rightPWM);
  if (direction.equalsIgnoreCase("right"))
  {
    // let right wheel go forward, let left wheel go backward
    analogWrite(PIN_MOTOR_LEFT_FORWARD, pwmValue);
    digitalWrite(PIN_MOTOR_LEFT_BACKWARD, LOW);
    analogWrite(PIN_MOTOR_RIGHT_BACKWARD, pwmValue);
    digitalWrite(PIN_MOTOR_RIGHT_FORWARD, LOW);
  }
  else if (direction.equalsIgnoreCase("left"))
  {
    // let right wheel go forward, let left wheel go backward
    analogWrite(PIN_MOTOR_RIGHT_FORWARD, pwmValue);
    digitalWrite(PIN_MOTOR_RIGHT_BACKWARD, LOW);
    analogWrite(PIN_MOTOR_LEFT_BACKWARD, pwmValue);
    digitalWrite(PIN_MOTOR_LEFT_FORWARD, LOW);
  }
  // waiting rotate finish
  while (motor_left_pulses_counter <= targetPulses && motor_right_pulses_counter <= targetPulses)
  {
  };
  stopMotors();
}

void adjustPWMvalueByPulse(int &leftPWMValue, int &rightPWMValue)
{
  unsigned long now = millis();
  unsigned long dt = now - lastPIDTime;

  // Ensure PID runs at a fixed interval
  if (dt < PID_INTERVAL)
    return;

  // 1. Calculate wheel speeds from encoder pulses
  float leftSpeed = (float)motor_left_pulses_counter / dt * 1000.0;
  float rightSpeed = (float)motor_right_pulses_counter / dt * 1000.0;

  // 2. Calculate speed error (same formula for forward/backward)
  float error = leftSpeed - rightSpeed;

  // 3. Handle first PID update (initialize state)
  if (!pidStarted)
  {
    lastError = error;
    pidStarted = true;
    lastPIDTime = now;
    motor_left_pulses_counter = 0;
    motor_right_pulses_counter = 0;
    return;
  }

  // 4. Integrate error (I term)
  integral += error * (dt / 1000.0);
  integral = constrain(integral, -20, 20);

  // 5. Derivative term (D term)
  float derivative = (error - lastError) / (dt / 1000.0);

  // 6. PID output value
  float correction = Kp * error + Ki * integral + Kd * derivative;

  // 8. Apply correction to the PWM values
  leftPWMValue = constrain(leftPWMValue - correction, 0, FULL_PWM_VALUE);
  rightPWMValue = constrain(rightPWMValue + correction, 0, FULL_PWM_VALUE);

  // 9. Update PID state
  lastError = error;
  motor_left_pulses_counter = 0;
  motor_right_pulses_counter = 0;
  lastPIDTime = now;
}