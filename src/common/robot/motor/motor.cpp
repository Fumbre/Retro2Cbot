#include "motor.h"
#include "common/constant/motor.h"

volatile long motor_left_pulses_counter = 0;
volatile long motor_right_pulses_counter = 0;

// count pulses
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
    pinMode(PINS_MOTOR[i], OUTPUT);
    digitalWrite(PINS_MOTOR[i], LOW);
  }
  pinMode(PIN_MOTOR_LEFT_PULSE, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTOR_LEFT_PULSE), countLeftPulses, RISING);

  pinMode(PIN_MOTOR_RIGHT_PULSE, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTOR_RIGHT_PULSE), countRightPulses, RISING);
};

void motorStability()
{
}