#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsMaze(PINS_RS, PINS_RS_LENGTH, THRESHOLD, MARGIN_SURFACE);

int fullSpeed = 255;
float slightConf = .6;
float hardConf = -.7;

bool isRotating = false;

LineState prevStatus = CENTER;

void mazeLine()
{
  LineState currentStatus = rsMaze.pattern();
  static Timer t;

  if (prevStatus == RIGHT_TURN && isRotating)
  {
    if (!t.timeout(40))
    {
      moveSpeed(255, 255);
    }
    else
    {
      moveSpeed(255, -220);
      if (currentStatus == CENTER || currentStatus == SLIGHT_RIGHT)
      {
        isRotating = false;
        t.resetTimeout();
      }
    }
    return;
  }

  switch (currentStatus)
  {
  case CENTER:
  CENTER:
    moveSpeed(fullSpeed, fullSpeed);
    break;
  case SLIGHT_LEFT:
    moveSpeed(fullSpeed * slightConf, fullSpeed);
    break;
  case SLIGHT_RIGHT:
    moveSpeed(fullSpeed, fullSpeed * slightConf);
    break;
  case HARD_LEFT:
    moveSpeed(fullSpeed * hardConf, fullSpeed);
    break;
  case HARD_RIGHT:
    moveSpeed(fullSpeed, fullSpeed * hardConf);
    break;
  case LEFT_TURN:
    prevStatus = LEFT_TURN;
    goto CENTER;
    break;
  case RIGHT_TURN:
    prevStatus = RIGHT_TURN;
    isRotating = true;
    break;
  case ALL_WHITE:
    if (prevStatus == LEFT_TURN)
    {
      moveSpeed(fullSpeed * hardConf, fullSpeed);
    }
    if (prevStatus == RIGHT_TURN)
    {
      moveSpeed(fullSpeed, fullSpeed * hardConf);
    }
    if (prevStatus == ALL_BLACK)
    {
      moveSpeed(fullSpeed, fullSpeed * hardConf);
    }
    break;
  case ALL_BLACK:
    prevStatus = ALL_BLACK;
    goto CENTER;
    break;
  }
}

void mazeLineSetup()
{
  setupMotor();
  rsMaze.setup();
}
