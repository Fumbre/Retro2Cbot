/**
 * @name constants for robot
 * @authors Sunny & Nicolo
 * @date 10-11-2025
 */
#include <Arduino.h>

 // the pin of directions of wheels
const int LEFT_DIRECTION_PIN1 = 5;
const int LEFT_DIRECTION_PIN2 = 6;
const int RIGHT_DIRECTIONL_PIN1 = 10;
const int RIGHT_DIRECTIONL_PIN2 = 11;

// pin of speed of wheels
const int LEFT_SPEED_PIN = 3;
const int RIGHT_SPEED_PIN = 9;

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
