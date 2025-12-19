#include "sonar.h"
#include "common/robot/movement/movement.h"

void setupSonar() {
  pinMode(12, OUTPUT); // Shared Trigger
  pinMode(8, INPUT);   // Front Echo
  pinMode(7, INPUT);   // Right Echo
  pinMode(5, INPUT);   // Left Echo
}

float measureDistance(int echo) {
  int sharedTrig = 12; 

  // Clean trigger pulse
  digitalWrite(sharedTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(sharedTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sharedTrig, LOW);

  // Read the bounce back
  unsigned long duration = pulseIn(echo, HIGH, 25000);
  
  // If no echo (0) or out of range, return 400
  if (duration == 0 || duration > 23200) return 400.0;
  
  return duration * 0.034 / 2;
}

// Added delays below to stop the "400" glitching
float getDistanceCM_Front() {
  delay(35); // Quiet time for sound waves to clear
  return measureDistance(8);
}

float getDistanceCM_Right() {
  delay(35); 
  return measureDistance(7);
}

float getDistanceCM_Left() {
  delay(35);
  return measureDistance(5);
}

// Obstacle Logic
bool isObstacleFront(float limit) {
  float d = getDistanceCM_Front();
  return (d > 1.0 && d <= limit);
}

bool isObstacleRight(float limit) {
  float d = getDistanceCM_Right();
  return (d > 1.0 && d <= limit);
}

bool isObstacleLeft(float limit) {
  float d = getDistanceCM_Left();
  return (d > 1.0 && d <= limit);
}