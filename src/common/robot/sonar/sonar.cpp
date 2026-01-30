/**
 * @name Sonar Module
 * @author Francisco & Uraib
 * @date 11-12-2025
 */

#include "sonar.h"

// Basically screaming & listening analogy for distance measurement

void setupSonar()
{
#if defined(BB011)
  pinMode(PIN_SONAR_TRIG, OUTPUT);      // Shared Trigger
  pinMode(PIN_SONAR_ECHO_FRONT, INPUT); // Front Echo
  pinMode(PIN_SONAR_ECHO_RIGHT, INPUT); // Right Echo
  pinMode(PIN_SONAR_ECHO_LEFT, INPUT);  // Left
#else
  pinMode(PIN_SONAR_TRIG, OUTPUT);      // Trigger
  pinMode(PIN_SONAR_ECHO_FRONT, INPUT); // Echo
#endif
}

float measureDistance(int echo)
{
  #if defined(BB011)
  delay(35);
  #endif
  digitalWrite(PIN_SONAR_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SONAR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_SONAR_TRIG, LOW);

  // Reduced timeout to 15000us (~250cm range) for faster decision making
  unsigned long duration = pulseIn(echo, HIGH, 15000);

  if (duration == 0)
    return 400.0;

  return duration * 0.0343 / 2;
}

float getDistanceCM_Front()
{
  float distance = measureDistance(PIN_SONAR_ECHO_FRONT);
  // record front sonar distance
  sonarSendDatafrontDistance = distance;
  return distance;
}

// two additional sonar for BB011 robot
float getDistanceCM_Right()
{
#if defined(BB011)
  float distance = measureDistance(PIN_SONAR_ECHO_RIGHT);
  sonarSendDataRightDistance = distance;
  return distance;
#else
  return 400.0;
#endif
}

float getDistanceCM_Left() {
#if defined(BB011)
  float distance = measureDistance(PIN_SONAR_ECHO_LEFT);
  sonarSendDataLeftDistance = distance;
  return distance;
#else
  return 400.0;
#endif
}

// Obstacle Logic
bool isObstacleFront(float limit) {
  float d = getDistanceCM_Front();
  return (d > 2.0 && d <= limit);
}

bool isObstacleRight(float limit) {
  float d = getDistanceCM_Right();
  return (d > 2.0 && d <= limit);
}

bool isObstacleLeft(float limit) {
  float d = getDistanceCM_Left();
  return (d > 2.0 && d <= limit);
}