#include "test_pulses.h"

Timer pulseStamp;

/**
 * @name testPulses
 * @author Fumbre (Vladyslav)
 * @date 21-11-2025
 * @details make test for pulses
 */
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