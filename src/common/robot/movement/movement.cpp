/**
 * @name the basic functions of robots
 * @authors Sunny & Nicolo
 * @date 10-11-2025
 */
#include "common/robot/movement/movement.h"

float lastError = 0;
float integral = 0;
unsigned long lastPIDTime = 0;
const unsigned long PID_INTERVAL = 10;
bool isMovingForward = true;
bool pidStarted = false;

float leftPWM = 0;
float rightPWM = 0;

float theta = 0.0;
float Ktheta = 2.0 * PI * WHEEL_RADUIS / (PPR * ROBOT_RADUIS);

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
float getPWMvalue(int speed)
{
  speed = constrain(speed, 0, FULL_SPEED); // if more than full speed put full speed variable [100%]
  float value = (float)speed / 100.0;
  return roundf(value * FULL_PWM_VALUE); // 0.80 * 255 = 204 * 0.97
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
  float pwmValue = getPWMvalue(speed);
  leftPWM = pwmValue * MOTOR_LEFT_FACTOR;
  rightPWM = pwmValue * MOTOR_RIGHT_FACTOR;
  adjustPWMvalueByPulse(leftPWM, rightPWM);
  leftPWM = constrain(leftPWM, 0, FULL_PWM_VALUE);
  rightPWM = constrain(rightPWM, 0, FULL_PWM_VALUE);
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
  leftPWM = pwmValue * MOTOR_LEFT_FACTOR;
  rightPWM = pwmValue * MOTOR_RIGHT_FACTOR;
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
  leftPWM = getPWMvalue(leftSpeed);
  rightPWM = getPWMvalue(rightSpeed);
  adjustPWMvalueByPulse(leftPWM, rightPWM);
  Serial.print("left: ");
  Serial.println(leftPWM);
  Serial.print("right: ");
  Serial.println(rightPWM);
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
 * @name rotateLeft
 * @author Fumbre (Vladyslav)
 * @date 19-11-2025
 * @param speed (0-255)
 */
void rotateLeft(int speed)
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    analogWrite(PINS_MOTOR[i], 0);
    if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_BACKWARD)
      analogWrite(PIN_MOTOR_LEFT_BACKWARD, speed);
    if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_FORWARD)
      analogWrite(PIN_MOTOR_RIGHT_FORWARD, speed);
  }
};

/**
 * @name rotateLeft
 * @author Fumbre (Vladyslav)
 * @date 19-11-2025
 * @param speed (0-255)
 */
void rotateRight(int speed)
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    analogWrite(PINS_MOTOR[i], 0);
    if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_FORWARD)
      analogWrite(PIN_MOTOR_LEFT_BACKWARD, speed);
    if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_BACKWARD)
      analogWrite(PIN_MOTOR_RIGHT_FORWARD, speed);
  }
};

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

/**
 * @name adjustPWMvalueByPulse
 * @author Sunny
 * @date 15-11-2025
 * @details use PID
 */
void adjustPWMvalueByPulse(float &leftPWMValue, float &rightPWMValue)
{
  unsigned long now = millis();
  unsigned long dt = now - lastPIDTime;

  // Ensure PID runs at a fixed interval
  if (dt < PID_INTERVAL)
    return;

  // 2. caculate angular velcoity increment
  float dTheta = Ktheta * (motor_left_pulses_counter - motor_right_pulses_counter);
  theta += dTheta;
  float error = dTheta;
  // 4. Integrate error (I term)
  integral += error * (dt / 1000.0);
  integral = constrain(integral, -20, 20); // -20, 20

  // 5. Derivative term (D term)
  float derivative = (error - lastError) / (dt / 1000.0);

  // 6. PID output value
  float correction;
  if (isMovingForward)
  {
    correction = Kp_f * error + Ki_f * integral + Kd_f * derivative;
  }
  else
  {
    correction = Kp_b * error + Ki_b * integral + Kd_b * derivative;
  }

  // 8. Apply correction to the PWM values
  if (isMovingForward)
  {
    leftPWMValue = constrain(leftPWMValue - correction * 2, 0, FULL_PWM_VALUE);
    rightPWMValue = constrain(rightPWMValue + correction * 2, 0, FULL_PWM_VALUE);
  }
  else
  {
    leftPWMValue = constrain(leftPWMValue + correction * 2, 0, FULL_PWM_VALUE);
    rightPWMValue = constrain(rightPWMValue - correction * 2, 0, FULL_PWM_VALUE);
  }
  lastError = error;
  motor_left_pulses_counter = 0;
  motor_right_pulses_counter = 0;
  lastPIDTime = now;
}