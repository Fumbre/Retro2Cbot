#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine2(PINS_RS, PINS_RS_LENGTH, 200, 35);
StartSequence entryPoint2(&rsLine2);

LineState lastStatus = CENTER;
LineState currentStatus;

// speed conf
int baseSpeed = 255;
float slightConf = 0.6;
float hardConf = 0.1;
float reverseConf = -1;

bool doRotationiRight = false;
bool doRotationiLeft = false;
bool rotated = false;

// maze variables
bool isMazeStarted2 = false;
bool isEndSequence2 = false;

static Timer t;

void mazeLine()
{

  if (!isMazeStarted2)
  {
    if (!entryPoint2.readyToStart(2))
    {
    }
    return;
  }
  else if (!entryPoint2.readyToStart(1))
  {
    isMazeStarted2 = true;
  }

  currentStatus = rsLine2.pattern();

  // if rotation do only rotation
  if (doRotationiRight)
  {
    rotate(0);
    return;
  }
  // left one
  if (doRotationiLeft)
  {
    rotate(1);
    return;
  }

  // main maze line code
  switch (currentStatus)
  {
  case CENTER:
    moveSpeed(baseSpeed, baseSpeed);
    break;
  case SLIGHT_LEFT:
    moveSpeed(baseSpeed * slightConf, baseSpeed);
    break;
  case SLIGHT_RIGHT:
    moveSpeed(baseSpeed, baseSpeed * slightConf);
    break;
  case ALL_BLACK:
    isEndSequence2 = entryPoint2.isDetecetingBlackSquare(62);

    lastStatus = ALL_BLACK;
    moveSpeed(baseSpeed, baseSpeed);
    break;
  case ALL_WHITE:
    if (lastStatus == ALL_BLACK || lastStatus == RIGHT_TURN)
    {
      doRotationiRight = true;
      rotate(0);
    }

    if (lastStatus == LEFT_TURN)
    {
      doRotationiLeft = true;
      rotate(1);
    }
    break;
  case HARD_LEFT:
    moveSpeed(baseSpeed * hardConf, baseSpeed);
  case LEFT_TURN:
    lastStatus = LEFT_TURN;
    moveSpeed(baseSpeed, baseSpeed);
    break;
  case HARD_RIGHT:
    moveSpeed(baseSpeed, baseSpeed * hardConf);
  case RIGHT_TURN:
    lastStatus = RIGHT_TURN;
    doRotationiRight = true;
    rotate(0);
    break;
  }
}

// dir == 0 -right dir == 1 -left
void rotate(int dir)
{
  bool end = false;

  if (!t.timeout(200)) // execute for 200 milliseconds
  {
    moveSpeed(baseSpeed, baseSpeed);
  }
  else
  {

    if (dir == 0)
    {
      if (!rotated)
      {
        if (t.executeOnce(0, 150))
        {
          moveSpeed(baseSpeed * .8, baseSpeed * .8 * reverseConf);
          return;
        }
        else
        {
          rotated = true;
        }
      }
    }

    if (dir == 1)
    {
      if (!rotated)
      {
        if (t.executeOnce(0, 150))
        {
          moveSpeed(baseSpeed * reverseConf * .8, baseSpeed * .8);
          return;
        }
        else
        {
          rotated = true;
        }
      }
    }

    if (rotated)
    {

      LineState pattern = rsLine2.pattern();

      if (pattern == CENTER || pattern == SLIGHT_LEFT || pattern == SLIGHT_RIGHT)
      {
        moveStopAll();
        end = true;
      }
    }
  }

  if (end)
  {
    rotated = false;

    doRotationiRight = false;
    doRotationiLeft = false;

    t.resetTimeout();
    t.resetExecuteOnce();
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