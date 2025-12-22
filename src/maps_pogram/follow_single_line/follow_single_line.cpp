#include "follow_single_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine(PINS_RS, PINS_RS_LENGTH, 220, 35);
StartSequence entryPoint(&rsLine);

bool isSequenceStart = true;
bool isSequenceEnd = false;
bool mazePassed = false;
bool isSequenceProcessing = false;

bool isEndSequence = false;

bool safeZone = true;

/**
 * @name followLine
 * @authors Fumbre (Vladyslav) & Aria & Francisco
 * @date 15-12-2025
 */
void followLine()
{

  static Timer t;
  static Timer t1;

  if (t.executeOnce(0))
  {
    entryPoint.onPossition(1);
  }

  if (!isEndSequence)
  {
    if (!entryPoint.pickUp())
      return;
  }

  LineState prevPattern;

  int fullSpeed = 255;
  float slightConf = .6;
  float hardConf = -.7;

  LineState currnetPattern = rsLine.pattern();

  if (!isEndSequence)
  {

    float distance = getDistanceCM_Front();

    if (!avoiding)
    {

      if (safeZone && distance <= 20 && distance >= 2)
      {
        safeZone = false; // exiting safe zone
        obstacleAvoidance(255);
      }
      else
      {
        if (distance > 20)
        {
          safeZone = true;
        }

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
          isEndSequence = entryPoint.isDetecetingBlackSquare(62);

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
    }
    else
    {
      obstacleAvoidance(255);
    }
  }
  else
  {
    if (t1.timeout(500))
    {
      gripperUnCatch();
    }
    if (!t.timeout(1000))
    {
      moveSpeed(fullSpeed * hardConf, fullSpeed * hardConf);
    }
    else
    {
      stopMotors();
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
