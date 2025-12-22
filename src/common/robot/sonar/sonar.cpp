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
  pinMode(PIN_SONAR_TRIG, OUTPUT);
  pinMode(PIN_SONAR_ECHO, INPUT);
#endif
}

float measureDistance(int trig, int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH, 25000); // timeout 25ms

  if (duration == 0)
  {
    return 400;
  }

  return duration * 0.034 / 2;
}

float getDistanceCM_Front()
{
  return measureDistance(PIN_SONAR_TRIG, PIN_SONAR_ECHO);
}

#if defined(BB011)

float getDistanceCM_Right()
{
  return measureDistance(PIN_SONAR_TRIG_2, PIN_SONAR_ECHO_2);
}

float getDistanceCM_Left()
{
  return measureDistance(PIN_SONAR_TRIG_3, PIN_SONAR_ECHO_3);
}

#endif

bool isObstacleFront(float limit)
{
  float d = getDistanceCM_Front();

  if (d == 400)
  {
    return true;
  }
  if (d < 2)
  {
    return true;
  }
  return (d > 2 && d <= limit);
}

// bool isObstacleRight(float limit)
// {
//   float d = getDistanceCM_Right();

//   if (d == 400)
//   {
//     return true;
//   }
//   if (d < 2)
//   {
//     return true;
//   }
//   return (d > 2 && d <= limit);
// }

// bool isObstacleLeft(float limit)
// {
//   float d = getDistanceCM_Left();

//   if (d == 400)
//   {
//     return true;
//   }
//   if (d < 2)
//   {
//     return true;
//   }
//   return (d > 2 && d <= limit);
// }
