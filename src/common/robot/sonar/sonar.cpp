#include "sonar.h"

/**
 * @name setupSonar
 * @author Francisco
 * @date 15-11-2025
 * @details Initializes the ultrasonic sensor (HC-SR04) by configuring the TRIG
 * pin as OUTPUT and the ECHO pin as INPUT. This setup enables the robot to send
 * ultrasonic pulses and detect their reflections for distance measurement.
 */

void setupSonar()
{

#if defined(BB011)
  pinMode(PIN_SONAR_TRIG, OUTPUT);      // Shared Trigger
  pinMode(PIN_SONAR_ECHO, INPUT);       // Front Echo
  pinMode(PIN_SONAR_ECHO_RIGHT, INPUT); // Right Echo
  pinMode(PIN_SONAR_ECHO_LEFT, INPUT);  // Left
#else
  pinMode(PIN_SONAR_TRIG, OUTPUT); // Trigger
  pinMode(PIN_SONAR_ECHO, INPUT);  // Echo
#endif
}

float measureDistance(int echo)
{

  // Clean trigger pulse
  digitalWrite(PIN_SONAR_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SONAR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_SONAR_TRIG, LOW);

  // Read the bounce back
  unsigned long duration = pulseIn(echo, HIGH, 25000); // timeout 25ms

  // If no echo (0) or out of range, return 400
  if (duration == 0 || duration > 23200)
    return 400.0;

  return duration * 0.034 / 2;
}

float getDistanceCM_Front()
{
  return measureDistance(PIN_SONAR_ECHO);
}

// two additional sonar for BB011 robot
float getDistanceCM_Right()
{
#if defined(BB011)
  return measureDistance(PIN_SONAR_ECHO_RIGHT);
#else
  return 0;
#endif
}

float getDistanceCM_Left()
{
#if defined(BB011)
  return measureDistance(PIN_SONAR_ECHO_LEFT);
#else
  return 0;
#endif
}

// Obstacle Logic
bool isObstacleFront(float limit)
{
  float d = getDistanceCM_Front();
  return (d > 1.0 && d <= limit);
}

bool isObstacleRight(float limit)
{
  float d = getDistanceCM_Right();
  return (d > 1.0 && d <= limit);
}

bool isObstacleLeft(float limit)
{
  float d = getDistanceCM_Left();
  return (d > 1.0 && d <= limit);
}
