#include "follow_single_line.h"

ReflectiveSensor rs(PINS_RS, PINS_RS_LENGTH, 225);

void followLine(int speed)
{
  float pwmValue = getProcentValue(speed);
  uint8_t lineStatus = rs.readBlackLine();
  Serial.println(lineStatus, BIN);
  int leftIndex = 0;
  int rightIndex = PINS_RS_LENGTH - 1;
  int leftBlackCount = 0;
  int rightBlackCount = 0;
  float leftSum = 0;
  float rightSum = 0;

  int i = 0;
  while (i < (PINS_RS_LENGTH / 2))
  {
    i++;

    if (bitRead(lineStatus, leftIndex))
    {
      leftBlackCount++;
      leftSum += WEIGHT[leftIndex];
    }
    if (bitRead(lineStatus, rightIndex))
    {
      rightBlackCount++;
      rightSum += WEIGHT[rightIndex];
    }
    leftIndex++;
    rightIndex--;
  }

  float leftSpeed = pwmValue;
  float rightSpeed = pwmValue;
  if (leftBlackCount != 0)
  {
    float factor = leftSum / (float)leftBlackCount;
    leftSpeed = leftSpeed + leftSpeed * factor;
  }

  if (rightBlackCount != 0)
  {
    float factor = rightSum / (float)rightBlackCount;
    rightSpeed = rightSpeed + rightSpeed * factor;
  }
  Serial.println(leftSpeed);
  Serial.println(rightSpeed);
  moveSpeed(leftSpeed, rightSpeed);
}

float getProcentValue(int speed)
{
  speed = constrain(speed, 0, 100);
  float value = ((float)speed / (float)100) * 255;
  return constrain(value, 0, 255);
}