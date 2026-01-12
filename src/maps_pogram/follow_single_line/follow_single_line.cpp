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

// for future possible to make it argument of function
int fullSpeed = 255;
float slightConf = .65; // try .8
float hardConf = -.45;

/**
 * @name followLine
 * @authors Fumbre (Vladyslav) & Aria & Francisco
 * @date 15-12-2025
 */

static Timer t;

void followLine()
{
  // wait until recieve a signal to start a maze
  if (!isMazeStarted)
  {
    // set poisition of robot to start properly in order
    if (mazeSequence.readyToStart(1))
    {
      isMazeStarted = true;
    }
    return;
  }

  // go only once after signal
  if (t.executeOnce(0))
  {
    moveSpeed(255, 255);
  }

  // current reflective sensor patter
  LineState currnetPattern = rsLine.pattern();

  // if it's not end of maze
  if (!isEndSequence)
  {
    dataSend();

    // wait until robot rotate after black square
    if (!mazeSequence.start(235))
      return;
  }

  // if it's not end of sequence do it
  if (!isEndSequence)
  {
    float distance = getDistanceCM_Front();

    if (!avoiding)
    {

      if (safeZone && distance <= 15 && distance >= 2)
      {
        // dobule check if object is still there
        if (t.interval(35))
        {
          safeZone = false;       // exiting safe zone
          obstacleAvoidance(255); // first step to avoid
        }
      }
      else
      {
        if (distance > 15)
        {
          safeZone = true;   // no objects ahead
          t.resetInterval(); // reset timeout
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
    mazeSequence.end(&mazePassed, "BB016");
  }
}

// the buisness logic of follow single line
void solvingFollowSingleLine(LineState currnetPattern, int fullSpeed, float slightConf, float hardConf)
{
  // depending on current pattern use logic
  switch (currnetPattern)
  {
  case CENTER:
  {
    moveSpeed(fullSpeed, fullSpeed);

    break;
  };
  case SLIGHT_LEFT:
  {
    moveSpeed(fullSpeed * slightConf, fullSpeed);

    break;
  };
  case SLIGHT_RIGHT:
  {
    moveSpeed(fullSpeed, fullSpeed * slightConf);

    break;
  };
  case HARD_LEFT:
  {
    moveSpeed(fullSpeed * hardConf, fullSpeed);

    break;
  };
  case HARD_RIGHT:
  {
    moveSpeed(fullSpeed, fullSpeed * hardConf);

    break;
  };
  case ALL_BLACK:
  {
    isEndSequence = mazeSequence.isDetecetingBlackSquare(100);

    moveSpeed(fullSpeed, fullSpeed);

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
