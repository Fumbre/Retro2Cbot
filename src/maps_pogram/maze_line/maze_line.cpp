#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsMaze(PINS_RS, PINS_RS_LENGTH, THRESHOLD, MARGIN_SURFACE);

float slightConf = 0.8;
float hardConf = 0.1;
bool isRotating = false;
int baseSpeed = 255;
unsigned long rotatingTime = 650;
int turnSpeed = 200;
LineState lastStatus = CENTER;
LineState dir = CENTER;

void mazeLineSetup()
{
  setupMotor();
  rsMaze.setup();
}

void mazeLine()
{
  LineState currentStatus = rsMaze.pattern();
  static Timer rotateTime;

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
  }

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
  case LEFT_TURN:
    lastStatus = LEFT_TURN;
    dir = LEFT_TURN;
    break;
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
    if (dir == LEFT_TURN)
    {
      if (!rotateTime.timeout(rotatingTime))
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
      isRotating = !didMoveRight(baseSpeed, 3);
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

int getPWMValue(int speed)
{
  speed = constrain(speed, 0, FULL_SPEED);
  int pwm = (float)speed / FULL_SPEED * FULL_PWM_VALUE;
  return constrain(pwm, 0, FULL_PWM_VALUE);
}

void mazeLineSetup()
{
  setupMotor();
  rsMaze.setup();
}
