#pragma once

void moveForward(int speed, int PIN);
void moveBackward(int speed, int PIN);
void moveLeft(int speed, int PIN);
void moveRight(int speed, int PIN);
void rotateLeft(int PIN);
void rotateRight(int PIN);
void moveStop();   // stop car


// startMotor for full speed than decline speed to regular one for easier enter

// put to function also a pin where to start