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

static Timer t;

static Timer t1;
static Timer t2;

void mazeLine()
{
  currentStatus = rsLine2.pattern();

  if (doRotationiRight)
  {
    rotate(0);
    return;
  }

  if (doRotationiLeft)
  {
    rotate(1);
    return;
  }

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
    // case OTHER:
    //   currentStatus = lastStatus;
    //   break;
  }
}

// dir == 0 -right dir == 1 -left
void rotate(int dir)
{
  bool end = false;

  if (!t.timeout(200)) // 200
  {
    moveSpeed(baseSpeed, baseSpeed);
  }
  else
  {

    if (dir == 0)
    {
      if (!rotated)
      {
        if (!t1.timeout(150))
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
        if (!t2.timeout(150))
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

    resetMoveLeft();
    resetMoveRight();
    t.resetTimeout();
    t1.resetTimeout();
    t2.resetTimeout();
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