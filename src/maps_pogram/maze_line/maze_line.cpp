#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsMaze(PINS_RS, PINS_RS_LENGTH, THRESHOLD, MARGIN_SURFACE);
StartSequence startPoint(&rsMaze);

float slightConf = 0.8;
float hardConf = 0.1;
bool isRotating = false;
int baseSpeed = 255;
unsigned long rotatingTime = 650;
LineState lastStatus = CENTER;
LineState dir = CENTER;
bool isEndSpace = false;
float avoidingDistance = 15; // unit: cm

void mazeLine()
{
  static Timer startPointTime;
  static Timer endPointTime;

  if (startPointTime.executeOnce(0))
  {
    startPoint.onPossition(1);
  }

  if (!isEndSpace)
  {
    if (!startPoint.pickUp())
      return;
  }

  if (!isEndSpace)
  {
    // get object distance
    float distance = getDistanceCM_Front();
    // if robot meet object, rotating 180 degree and go back
    if (distance <= avoidingDistance)
    {
      // rotate 180 degree
      if (!didMoveLeft(baseSpeed, PPR / 2))
      {
        return;
      }else{
        resetMoveLeft();
      }
    }

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
  }else{
    if (endPointTime.timeout(500))
    {
      gripperUnCatch();
    }
    if (!startPointTime.timeout(1000))
    {
      moveSpeed(baseSpeed * hardConf, baseSpeed * hardConf);
    }
    else
    {
      stopMotors();
    }
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
  setupGripper();
  setupSonar();
  rsMaze.setup();
  gripperUnCatch();
}