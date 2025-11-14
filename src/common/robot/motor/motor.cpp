#include "motor.h"

void countLeftPulses() { motor_left_pulses_counter++; }
void countRightPulses() { motor_right_pulses_counter++; }

/**
 * @name setupMotor
 * @author Fumbre (Vladyslav)
 * @date 13-11-2025
 * @details configurate pins for motor
 */

void setupMotor()
{
  for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
  {
    if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_PULSE)
    {
      pinMode(PIN_MOTOR_LEFT_PULSE, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(PIN_MOTOR_LEFT_PULSE), countLeftPulses, RISING);
      continue;
    }
    if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_PULSE)
    {
      pinMode(PIN_MOTOR_RIGHT_PULSE, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(PIN_MOTOR_RIGHT_PULSE), countRightPulses, RISING);
      continue;
    }
    pinMode(PINS_MOTOR[i], OUTPUT);
    digitalWrite(PINS_MOTOR[i], LOW);
  }
};
