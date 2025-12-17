#include "follow_single_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine(PINS_RS, PINS_RS_LENGTH, 220, 35);
StartSequence entryPoint(&rsLine);

bool isSequenceStart = true;
bool isSequenceEnd = false;
bool mazePassed = false;
bool isSequenceProcessing = false;

/**
 * @name followLine
 * @authors Aria & Fumbre (Vladyslav)
 * @date 15-12-2025
 */
void followLine()
{

  if (!entryPoint.pickUp())
  {
    entryPoint.onPossition(1);
    return;
  }

  LineState prevPattern;

  int fullSpeed = 255;
  float slightConf = .6;
  float hardConf = -.7;

  LineState currnetPattern = rsLine.pattern();

  switch (currnetPattern)
  {
  case CENTER:
  {
    moveSpeed(fullSpeed, fullSpeed);
    prevPattern = CENTER;
    Serial.println("center");
    break;
  };
  case SLIGHT_LEFT:
  {
    moveSpeed(fullSpeed * slightConf, fullSpeed);
    prevPattern = SLIGHT_LEFT;
    Serial.println("SLIGHT_LEFT");
    break;
  };
  case SLIGHT_RIGHT:
  {
    moveSpeed(fullSpeed, fullSpeed * slightConf);
    prevPattern = SLIGHT_RIGHT;

    Serial.println("SLIGHT_RIGHT");
    break;
  };
  case HARD_LEFT:
  {
    moveSpeed(fullSpeed * hardConf, fullSpeed);
    prevPattern = HARD_LEFT;
    Serial.println("HARD_LEFT");
    break;
  };
  case HARD_RIGHT:
  {
    moveSpeed(fullSpeed, fullSpeed * hardConf);

    prevPattern = HARD_RIGHT;
    Serial.println("HARD_RIGHT");
    break;
  };

    // case ALL_WHITE:
    // {
    //   moveSpeed(fullSpeed * slightConf, fullSpeed * slightConf);

    //   Serial.println("ALL_WHITE");
    //   break;
    // };

  case ALL_BLACK:
  {
    moveSpeed(fullSpeed, fullSpeed);

    Serial.println("ALL_BLACK");
    break;
  };

  default:
  {
    currnetPattern = prevPattern;
    break;
  }
  }
}

/**
 * @name followLine
 * @authors Aria & Fumbre (Vladyslav)
 * @date 15-12-2025
 */
void followLineSetup()
{
  setupMotor();
  setupGripper();
  gripperUnCatch();
  setupSonar();
  rsLine.setup();
}

// void followLineSequence()
// {
// Serial.print("fsaf");
// entryPoint.pickUp();

// if (!isSequenceStart && isSequenceEnd) // false
// {
//   return;
// }
// if (isSequenceStart) // true
// {
//   entryPoint.pickUp();
//   return;
// }

// if (isSequenceProcessing)
// {
//   followLine();
// }

// if (mazePassed)
//   return;
// }