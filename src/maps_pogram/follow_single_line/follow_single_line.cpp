#include "follow_single_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine(PINS_RS, PINS_RS_LENGTH, 220, 35);
Sequence mazeSequence(&rsLine);

// maze variables
bool mazePassed = false; // send data to next robot when maze is passed
// end sequence variable
bool isEndSequence = false;
bool isMazeStarted = false;

// variable for avoiding
bool safeZone = true;

/**
 * @name followLine
 * @authors Fumbre (Vladyslav) & Aria & Francisco
 * @date 15-12-2025
 */

static Timer t;

void followLine()
{
  // set poisition of robot
  if (!isMazeStarted)
  {
    if (mazeSequence.readyToStart(1))
    {
      isMazeStarted = true;
    }
    return;
  }

  if (t.executeOnce(0))
  {
    moveSpeed(255, 255);
  }

  if (!isEndSequence)
  {
    // dataSend();

    if (!mazeSequence.start(235))
      return;
  }

  // previous pattern | if robot is too fast keep going with previous status |
  // LineState prevPattern;

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
        // dobule check if object is still there
        if (t.timeout(35))
        {
          safeZone = false;       // exiting safe zone
          obstacleAvoidance(255); // first step to avoid
        }
      }
      else
      {
        if (distance > 20)
        {
          safeZone = true;  // no objects ahead
          t.resetTimeout(); // reset timeout
        }

        // main code
        solvingFollowSingleLine(currnetPattern, fullSpeed, slightConf, hardConf);
      }
    }
    else
    {
      obstacleAvoidance(255); // continue avoiding
    }
  }

  if (isEndSequence)
  {
    if (!t.timeout(1000))
    {
      dataSend();
    }
    mazeSequence.end(&mazePassed, "BB046");
  }
}

void solvingFollowSingleLine(LineState currnetPattern, int fullSpeed, float slightConf, float hardConf)
{
  switch (currnetPattern)
  {
  case CENTER:
  {
    moveSpeed(fullSpeed, fullSpeed);

    // prevPattern = CENTER;

    break;
  };
  case SLIGHT_LEFT:
  {
    moveSpeed(fullSpeed * slightConf, fullSpeed);

    // prevPattern = SLIGHT_LEFT;

    break;
  };
  case SLIGHT_RIGHT:
  {
    moveSpeed(fullSpeed, fullSpeed * slightConf);

    // prevPattern = SLIGHT_RIGHT;

    break;
  };
  case HARD_LEFT:
  {
    moveSpeed(fullSpeed * hardConf, fullSpeed);

    // prevPattern = HARD_LEFT;

    break;
  };
  case HARD_RIGHT:
  {
    moveSpeed(fullSpeed, fullSpeed * hardConf);

    // prevPattern = HARD_RIGHT;

    break;
  };
  case ALL_BLACK:
  {
    isEndSequence = mazeSequence.isDetecetingBlackSquare(100);

    moveSpeed(fullSpeed, fullSpeed);

    break;
  };

  default:
  {
    // if no match go to previous action

    // currnetPattern = prevPattern;

    // this doesn't make sense because of the looop you can just put break;
    break;
  };
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
