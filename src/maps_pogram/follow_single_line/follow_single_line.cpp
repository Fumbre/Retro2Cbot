#include "follow_single_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine(PINS_RS, PINS_RS_LENGTH, 220, 35);
StartSequence entryPoint(&rsLine);

// variable to send data to next robot when maze is passed
bool mazePassed = false;

// end sequence variable
bool isEndSequence = false;

// variable for avoiding
bool safeZone = true;

/**
 * @name followLine
 * @authors Fumbre (Vladyslav) & Aria & Francisco
 * @date 15-12-2025
 */
void followLine()
{
  // init timers
  static Timer t;
  static Timer t1;

  // set poisition of robot
  if (t.executeOnce(0))
  {
    entryPoint.onPossition(1); // this is first robot so it will go immediately
  }

  if (!isEndSequence)
  {
    if (!entryPoint.pickUp())
      return;
  }

  // previous pattern | if robot is too fast keep going with previous status |
  LineState prevPattern;

  // for future possible to make it argument of function
  int fullSpeed = 255;
  float slightConf = .6;
  float hardConf = -.7;

  // current patter
  LineState currnetPattern = rsLine.pattern();

  // if it's not end of sequence do it
  if (!isEndSequence)
  {

    float distance = getDistanceCM_Front();

    if (!avoiding)
    {

      if (safeZone && distance <= 20 && distance >= 2)
      {
        safeZone = false;       // exiting safe zone
        obstacleAvoidance(255); // first step to avoid
      }
      else
      {
        if (distance > 20)
          safeZone = true; // no objects ahead

        // main code
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
          // we don't need case for all white
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
          // if no match go to previous action
          currnetPattern = prevPattern;
          break;
        }
        }
      }
    }
    else
    {
      obstacleAvoidance(255); // continue avoiding
    }
  }
  else
  {
    // this is end of sequence (black square)
    if (t1.timeout(500)) // after 500ms uncatch an object
    {
      gripperUnCatch();
    }
    if (!t.timeout(1000)) // go back during 1s
    {
      moveSpeed(fullSpeed * hardConf, fullSpeed * hardConf);
    }
    else // after 1s stop all motors
    {
      stopMotors();
    }
  }
}

/**
 * @name followLineSetup
 * @authors Fumbre (Vladyslav)
 * @date 15-12-2025
 * @details makes setup functions for Follow Line maze
 */
void followLineSetup()
{
  buildHC12Connection();
  setupMotor();
  setupGripper();
  gripperUnCatch();
  setupSonar();
  rsLine.setup();
}
