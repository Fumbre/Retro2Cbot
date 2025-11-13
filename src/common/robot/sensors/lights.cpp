#include <Arduino.h>
#include "lights.h"

// Inicialização (nada especial, só garante LOW no arranque)
void initLEDs() {
  pinMode(LEFT_DIRECTION_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_DIRECTION_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_DIRECTION_BACKWARD_PIN, OUTPUT);
  pinMode(RIGHT_DIRECTION_BACKWARD_PIN, OUTPUT);

  setLEDsStopped();
}

// Liga LEDs (são os mesmos pinos dos motores)
void setLEDsMoving() {
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN, HIGH);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, HIGH);
}

// Desliga LEDs (todos LOW)
void setLEDsStopped() {
  digitalWrite(LEFT_DIRECTION_FORWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, LOW);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_BACKWARD_PIN, LOW);
}
