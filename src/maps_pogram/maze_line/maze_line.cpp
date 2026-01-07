#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine2(PINS_RS, PINS_RS_LENGTH, 200, 35);
StartSequence entryPoint2(&rsLine2);

LineState lastStatus = CENTER;
LineState currentStatus;

// speed conf
int baseSpeed = 255;
float slightConf = 0.7;
float hardConf = 0.1;
float reverseConf = -1;

// timing
unsigned long turningTime = 200;

bool doRightRotation = false;
bool doRightRotationLeft = false;

static Timer t;

void mazeLine()
{
  currentStatus = rsLine2.pattern();

  if (doRightRotation)
  {
    rotate(0);
    return;
  }

  if (doRightRotationLeft)
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
      doRightRotation = true;
      rotate(0);
    }

    if (lastStatus == LEFT_TURN)
    {
      doRightRotationLeft = true;
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
    doRightRotation = true;
    rotate(0);
    break;
  }
}

// dir == 0 -right dir == 1 -left
void rotate(int dir)
{
  bool end = false;

  if (t.executeOnce(0, 100))
  {
    moveSpeed(baseSpeed, baseSpeed);
    return;
  }

  if (dir == 0)
  {

    // to do do move left until reach center
    if (didMoveRight(baseSpeed, 12))
    {
      end = true;
    }
  }

  if (dir == 1)
  {
    if (didMoveLeft(baseSpeed, 12))
    {
      end = true;
    }
  }

  if (end)
  {
    doRightRotation = false;
    doRightRotationLeft = false;

    resetMoveLeft();
    resetMoveRight();
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