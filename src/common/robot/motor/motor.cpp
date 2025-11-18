#include "motor.h"
#include "common/constant/motor.h"

volatile long motor_left_pulses_counter = 0;
volatile long motor_right_pulses_counter = 0;

// MotorSpeed correctSpeed = {255, 255};

Timer timestamp;
Timer timestampRight;
Timer timestampLeft;

// count pulses
void countLeftPulses()
{
  if (timestamp.interval(20))
  {
    timestampRight.resetExecuteOnce();
    timestampLeft.resetExecuteOnce();
  }
  if (timestampLeft.executeOnce(0))
  {
    motor_left_pulses_counter++;
  }
}
void countRightPulses()
{
  if (timestamp.interval(20))
  {
    timestampRight.resetExecuteOnce();
    timestampLeft.resetExecuteOnce();
  }
  if (timestampRight.executeOnce(0))
  {
    motor_right_pulses_counter++;
  }
}

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

// Timer time;
// Stability correctSpeed = {255, 255};

// Stability motorStability(int speed)
// {
//   if (motor_left_pulses_counter > motor_right_pulses_counter)
//   {
//     if (time.intervalStart(20))
//     {
//       correctSpeed.speedLeft--;
//     }
//   }
//   if (motor_right_pulses_counter > motor_left_pulses_counter)
//   {
//     if (time.intervalStart(20))
//     {
//       correctSpeed.speedRight--;
//     }
//   }
//   return correctSpeed;
// }
