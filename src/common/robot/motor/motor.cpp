#include "motor.h"

void setupMotor()
{
  for (int i = 0; i < WHEEL_ARRAY_LENGTH; i++)
  {
    pinMode(WHEEL_ARRAY[i].PIN, OUTPUT);
    digitalWrite(WHEEL_ARRAY[i].PIN, LOW);
  }
};
