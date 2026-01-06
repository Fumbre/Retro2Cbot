#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine2(PINS_RS, PINS_RS_LENGTH, 220, 35);
StartSequence entryPoint2(&rsLine2);
// Josn document class
StaticJsonDocument<256> followingLineDoc2;

// variable to send data to next robot when maze is passed
bool mazePassed2 = false;

// end sequence variable
bool isEndSequence2 = false;

bool isGoing2 = false;

bool isHC12SentForPM = false;
float slightConf = 0.8;
float hardConf = 0.1;
bool isRotating = false;
int baseSpeed = 255;

unsigned long rotatingTime = 650;
unsigned long directingTime = 1000;
LineState lastStatus = CENTER;
LineState dir = CENTER;
bool isEndSpace = false;
float avoidingDistance = 15; // unit: cm

void mazeLine()
{
  // init timers
  static Timer t;
  static Timer t1;
  // set poisition of robot
  if (!entryPoint2.readyToStart(1) && !isGoing2)
  {
    return;
  }
  else if (!entryPoint2.readyToStart(1))
  {
    isGoing2 = true;
  }

  if (t.executeOnce(0))
  {
    moveSpeed(230, 230);
  }

  if (!isEndSequence2)
  {
    if (!entryPoint2.startWithPickUp(255, 11))
      return;
  }

  if (!isEndSequence2)
  {
    // get object distance
    float distance = getDistanceCM_Front();
    // if robot meet object, rotating 180 degree and go back
    if (distance <= avoidingDistance)
    {
      // rotate 180 degree
      if (!didMoveRight(baseSpeed, PPR / 2))
      {
        return;
      }
      else
      {
        resetMoveRight();
      }
    }

    LineState currentStatus = rsLine2.pattern();
    static Timer rotateTime;
    static Timer directingTimer;

    if (isRotating)
    {
      if (currentStatus != ALL_WHITE && lastStatus == ALL_WHITE)
      {
        isRotating = false;
        resetMoveRight();
      }
      else
      {
        currentStatus = lastStatus;
      }
    }
    else
    {
      // lastStatus = currentStatus;
      resetMoveRight();
      rotateTime.resetTimeout();
      directingTimer.resetTimeout();
    }

    // todo include HARD _LEFT and _RIGHT to put robot in the center of line!!
    switch (currentStatus)
    {
    case CENTER:
      moveSpeed(baseSpeed, baseSpeed);
      lastStatus = CENTER;
      break;
    case SLIGHT_LEFT:
      lastStatus = SLIGHT_LEFT;
      moveSpeed(baseSpeed * slightConf, baseSpeed);
      break;
    case SLIGHT_RIGHT:
      lastStatus = SLIGHT_RIGHT;
      moveSpeed(baseSpeed, baseSpeed * slightConf);
      break;
    case HARD_LEFT:
      lastStatus = HARD_LEFT;
      dir = HARD_LEFT;
      break;  
    case LEFT_TURN:
      lastStatus = LEFT_TURN;
      dir = LEFT_TURN;
      break;
    case HARD_RIGHT:  
    case RIGHT_TURN:
      lastStatus = RIGHT_TURN;
      if (!rotateTime.timeout(rotatingTime))
      {
        isRotating = true;
        moveSpeed(baseSpeed, baseSpeed * hardConf);
      }
      else
      {
        isRotating = false;
      }
      break;
    case ALL_WHITE:
      if (dir == LEFT_TURN || dir == HARD_LEFT)
      {
        if (!directingTimer.timeout(directingTime))
        {
          isRotating = true;
          moveSpeed(baseSpeed * hardConf, baseSpeed);
          lastStatus = ALL_WHITE;
        }
        else
        {
          isRotating = false;
          dir = CENTER;
        }
      }
      else
      {
        lastStatus = ALL_WHITE;
        // isRotating = !didMoveRight(baseSpeed, 3);
        didMoveRight(baseSpeed,3);
        isRotating = true;
      }
      break;
    case ALL_BLACK:
      lastStatus = ALL_BLACK;
      if (!rotateTime.timeout(rotatingTime))
      {
        isRotating = true;
        moveSpeed(baseSpeed, baseSpeed * hardConf);
      }
      else
      {
        isRotating = false;
      }
      break;
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
      moveSpeed(baseSpeed * hardConf, baseSpeed * hardConf);
    }
    else
    {
      stopMotors();
    }
  }
}

void mazeLineSetup()
{
  buildHC12Connection();
  setupMotor();
  setupGripper();
  setupSonar();
  rsLine2.setup();
  gripperUnCatch();
}