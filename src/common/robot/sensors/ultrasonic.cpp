/*
#include <Arduino.h>
#include "../../constant/Robot.h"
#include "ultrasonic.h"

// Initialize ultrasonic pins
void initUltrasonic() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

// Measure distance in cm
float getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;  // cm
  return distance;
}

// Return true if obstacle detected (within threshold)
bool isObstacleDetected(float threshold_cm) {
  float distance = getDistanceCM();
  return (distance <= threshold_cm && distance > 0);
}
*/