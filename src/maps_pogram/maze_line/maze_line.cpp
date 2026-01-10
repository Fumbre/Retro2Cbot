#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine2(PINS_RS, PINS_RS_LENGTH, 200, 35);
Sequence mazeSequence2(&rsLine2);

LineState lastStatus = CENTER;
LineState currentStatus;

// speed conf
int baseSpeed = 255;
float slightConf = 0.6;
float hardConf = 0.1;
float reverseConf = -1;

bool doRotationRight = false;
bool doRotationLeft = false;
bool rotated = false;

// maze variables
bool isMazeStarted2 = false;
bool isEndSequence2 = false;
bool mazePassed2 = false;

// maybe put it inside roatation function
static Timer t;

void mazeLine()
{
  // init timers
  static Timer t;

  // set poisition of robot
  if (!isMazeStarted2)
  {
    if (mazeSequence2.readyToStart(2))
    {
      isMazeStarted2 = true;
    }
    return;
  }

  if (t.executeOnce(0))
  {
    moveSpeed(230, 230);
  }

  if (!isEndSequence2)
  {
    if (!mazeSequence2.start(255))
      return;
  }

  currentStatus = rsLine2.pattern();

  // if rotation do only rotation
  if (doRotationRight)
  {
    rotate(0);
    return;
  }
  // left one
  if (doRotationLeft)
  {
    rotate(1);
    return;
  }

  if (!isEndSequence2)
  {

    float distance = getDistanceCM_Front();

    if (distance < 20)
    {
      // check if the object is still there after 30 millis
      if (t.timeout(30))
      {
        if (distance < 20)
        {
          doRotationRight = true;
          rotate(0);
          return;
        }
      }
    }
    else
    {
      t.resetTimeout();
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
      isEndSequence2 = mazeSequence2.isDetecetingBlackSquare(62);

      lastStatus = ALL_BLACK;
      moveSpeed(baseSpeed, baseSpeed);
      break;
    case ALL_WHITE:
      if (lastStatus == ALL_BLACK || lastStatus == RIGHT_TURN)
      {
        doRotationRight = true;
        rotate(0);
      }

      if (lastStatus == LEFT_TURN)
      {
        doRotationLeft = true;
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
      doRotationRight = true;
      rotate(0);
      break;
    }
  }

  if (isEndSequence2)
  {
    mazeSequence2.end(&mazePassed2, "BB016");
  }
}

// dir == 0 -right; dir == 1 -left
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

    doRotationRight = false;
    doRotationLeft = false;

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