#include "movement.h"

void moveForward(bool isPure)
{
  if (isPure)
  {
    digitalWrite(WHEEL_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, LOW);

    digitalWrite(WHEEL_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_LEFT_BACKWARD_PIN, LOW);

    digitalWrite(WHEEL_LEFT_ROTATION_PIN, LOW);
    digitalWrite(WHEEL_RIGHT_ROTATION_PIN, LOW);
  }
  else
  {
    digitalWrite(WHEEL_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_LEFT_FORWARD_PIN, HIGH);
  }
};

void moveBackward(bool isPure) {

};

void moveRight(bool isPure) {

};

void moveLeft(bool isPure) {

};

void rotateLeft(bool isPure) {

};

void rotateRight(bool isPure) {

};

void moveStop() {

};
