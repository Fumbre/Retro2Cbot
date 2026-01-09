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
  // Taking a deep breath before screaming
  digitalWrite(PIN_SONAR_TRIG, LOW);
  delayMicroseconds(2);
  // Letting out a quick scream
  // P.s HIGH = 5V
  digitalWrite(PIN_SONAR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_SONAR_TRIG, LOW);

  // Read and listen to the echo
  unsigned long duration = pulseIn(echo, HIGH, 25000);
  // not HABIBI BUT ALL robots that use SONAR!
  // the habibi waits for 25ms for an echo

  // If no echo (0) or out of range, return 400
  if (duration == 0 || duration > 23200)
    return 400.0;

  // sound travels to wall AND back, so divide by 2
  return duration * 0.034 / 2;
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
  float distance = measureDistance(PIN_SONAR_ECHO_FRONT);
  // record right sonar distance
  sonarSendDataRightDistance = distance;
  return distance;
#else
  return 0;
#endif
}

float getDistanceCM_Left()
{
#if defined(BB011)
  float distance = measureDistance(PIN_SONAR_ECHO_FRONT);
  // record left sonar distance
  sonarSendDataLeftDistance = distance;
  return distance;
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