#include "../test/motors/stability.h"

volatile long leftPulsesCountTest = 0;
volatile long rightPulsesCountTest = 0;

void countLeftRotationTest() { leftPulsesCountTest++; }
void countRightRotationTest() { rightPulsesCountTest++; }

void initRotationPins()
{
  pinMode(LEFT_ROTATION_PIN, INPUT_PULLUP);
  pinMode(RIGHT_ROTATION_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_ROTATION_PIN), countLeftRotationTest, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ROTATION_PIN), countRightRotationTest, RISING);

  analogWrite(LEFT_DIRECTION_FORWARD_PIN, 255);
  digitalWrite(LEFT_DIRECTION_BACKWARD_PIN, LOW);
  analogWrite(RIGHT_DIRECTION_BACKWARD_PIN, 249);
  digitalWrite(RIGHT_DIRECTION_FORWARD_PIN, LOW);
  Serial.println("start test---------------");
}

void testPulses()
{
  // print the number of pulses
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 500)
  {
    Serial.print("Left pulses: ");
    Serial.print(leftPulsesCountTest);
    Serial.print("  Right pulses: ");
    Serial.println(rightPulsesCountTest);
    lastPrint = millis();
  }
}