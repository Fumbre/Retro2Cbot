#pragma once
#include <Arduino.h>
#include "common/constant/Robot.h"

void moveForward(float distance_m);                      // Move forward a certain distance
void moveBackward(float distance_m);                     // Move backward a certain distance
void moveRight();                        // Move forward and turn left
void moveLeft();                         // Move forward and turn right
void rotateLeft90();                     // Rotate 90º left in place
void rotateRight90();                    // Rotate 90º right in place
void rotate180();                                   // Rotate 180º in place
void moveStop();                                    // Stop all motors
void moveUntilObstacle(int stopDistance_cm);        // Move forward until obstacle at given distance


// startMotor for full speed than decline speed to regular one for easier enter

// put to function also a pin where to start