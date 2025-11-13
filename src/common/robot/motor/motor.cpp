#include "motor.h"
#include "../../constant/Robot.h"
#include <Arduino.h>

void Motor() {
  // pinMode
  pinMode(LEFT_DIRECTION_FORWARD_PIN,  OUTPUT);
  pinMode(LEFT_DIRECTION_BACKWARD_PIN, OUTPUT);
  pinMode(RIGHT_DIRECTION_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_DIRECTION_BACKWARD_PIN,OUTPUT);
  pinMode(LEFT_ROTATION_PIN,  OUTPUT);   // se for saída (servo/steer). Se forem encoders, muda para INPUT_PULLUP e tira daqui.
  pinMode(RIGHT_ROTATION_PIN, OUTPUT);   // idem ^

  // estado inicial
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN,  LOW);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN,LOW);
  digitalWrite(LEFT_ROTATION_PIN,  LOW);
  digitalWrite(RIGHT_ROTATION_PIN, LOW);
}
