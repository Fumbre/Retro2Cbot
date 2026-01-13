#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine2(PINS_RS, PINS_RS_LENGTH, 200, 35);
Sequence mazeSequence2(&rsLine2);

LineState lastStatus = CENTER;
LineState currentStatus;

// speed conf
int baseSpeed2 = 230;
float slightConf2 = 0.6;
float hardConf2 = 0.1;
float reverseConf2 = -1;

bool doRotationRight = false;
bool doRotationLeft = false;
bool rotated = false;

// maze variables
bool isMazeStarted2 = false;
bool isEndSequence2 = false;
bool mazePassed2 = false;

// maybe put it inside roatation function
// init timers
static Timer t;
static Timer t1;
static Timer rotationT;

void mazeLine()
{

  // set poisition of robot
  if (!isMazeStarted2)
  {
    if (mazeSequence2.readyToStart(1)) // !!!change it to 2!!
    {
      isMazeStarted2 = true;
    }
    return;
  }

  if (t1.executeOnce(0))
  {
    moveSpeed(255, 255);
    turnOnAllLeds(0, 255, 0);
  }

  if (!isEndSequence2)
  {
    dataSend();

    if (!mazeSequence2.start(baseSpeed2, 10)) // 230
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
    if (t.interval(35, 70))
    {

      float distance = getDistanceCM_Front();

      if (distance < 18)
      {
        doRotationLeft = true;
        rotate(1);
        return;
      }
    }

    // main maze line code
    switch (currentStatus)
    {
    case CENTER:
      if (lastStatus == ALL_BLACK)
      {
        doRotationRight = true;
        rotate(0);

        return;
      }

      moveSpeed(baseSpeed2, baseSpeed2);
      lastStatus = CENTER;
      break;
    case SLIGHT_LEFT:
      moveSpeed(baseSpeed2 * slightConf2, baseSpeed2);
      break;
    case SLIGHT_RIGHT:
      moveSpeed(baseSpeed2, baseSpeed2 * slightConf2);
      break;
    case ALL_BLACK:
      isEndSequence2 = mazeSequence2.isDetecetingBlackSquare(150);
      lastStatus = ALL_BLACK;
      moveSpeed(baseSpeed2, baseSpeed2);
      break;
    case ALL_WHITE:
      // because Lady Maria has problems with right wheel
      if (lastStatus == CENTER)
      {
        doRotationRight = true;
        rotate(0);
      }

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
      moveSpeed(baseSpeed2 * hardConf2, baseSpeed2);
    case LEFT_TURN:
      lastStatus = LEFT_TURN;
      moveSpeed(baseSpeed2, baseSpeed2);
      break;
    case HARD_RIGHT:
      moveSpeed(baseSpeed2, baseSpeed2 * hardConf2);
    case RIGHT_TURN:
      lastStatus = RIGHT_TURN;
      doRotationRight = true;
      rotate(0);
      break;
    }
  }
  // send start command to BB011
  if (isEndSequence2)
  {
    if (!t1.timeout(1000))
    {
      dataSend();
    }
    mazeSequence2.end(&mazePassed2, "BB046");
  }
}

// dir == 0 -right; dir == 1 -left
void rotate(int dir)
{
  bool end = false;

  if (!t.timeout(200)) // execute for 200 milliseconds
  {
    moveSpeed(baseSpeed2, baseSpeed2);
  }
  else
  {
    if (dir == 0)
    {
      if (!rotated)
      {
        if (t.executeOnce(0, 300)) // 150
        {
          moveSpeed(baseSpeed2 * .8, baseSpeed2 * .8 * reverseConf2);
          // return;
        }
        else
        {
          rotated = true;
        }

        if (rotationT.executeOnce(0))
        {
          int index[2] = {1, 2};
          turnOnSomeLeds(index, 2, 255, 255, 0);
        }
      }
    }

    if (dir == 1)
    {
      if (!rotated)
      {

        if (t.executeOnce(0, 300))
        {
          moveSpeed(baseSpeed2 * reverseConf2 * .8, baseSpeed2 * .8);
          // return;
        }
        else
        {
          rotated = true;
        }

        if (rotationT.executeOnce(0))
        {
          int index[2] = {0, 3};
          turnOnSomeLeds(index, 2, 255, 255, 0);
        }
      }
    }

    if (rotated)
    {

      LineState pattern = rsLine2.pattern();

      if (pattern == CENTER || pattern == SLIGHT_LEFT || pattern == SLIGHT_RIGHT)
      {
        lastStatus = pattern;
        moveStopAll();
        end = true;
        moveSpeed(baseSpeed2, baseSpeed2);

        turnOnAllLeds(0, 255, 0);
      }
    }
  }

  if (end)
  {
    rotated = false;

    doRotationRight = false;
    doRotationLeft = false;

    rotationT.resetExecuteOnce();
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