#include "test_pulses.h"

Timer pulseStamp;

void testPulses(int updateTime)
{
  if (pulseStamp.intervalStart(updateTime))
  {
    Serial.print("Left pulses: ");
    Serial.print(motor_left_pulses_counter);
    Serial.print(" Right pulses: ");
    Serial.println(motor_right_pulses_counter);
  }
}
