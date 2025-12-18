// conclude the move forward t obe real in forward;
// check left and right sensor to calib between section;
// the same for 3 lines of black and white;
// check for 25 millist the black sequence use gripper then turn left, if recive 000 11 000 go to next map program;
#pragma once
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/tools/Timer.h"
#include "common/robot/gripper/gripper.h"
#include "common/robot/movement/movement.h"
#include "common/robot/movement/movementPID.h"

class StartSequence
{
private:
  ReflectiveSensor *rsData;

  bool isRotated = false;
  bool catchObj = false;

  /**
   *@param time int how black should be detected to return true
   *@return bool
   */

public:
  StartSequence(ReflectiveSensor *rsData)
  {
    this->rsData = rsData;
  }

  void onPossition(int pos)
  {
    if (pos == 1)
    {
      if (this->rsData->readBlackLine() == 0)
      {
        moveSpeed(230, 230);
      }
    }
  }

  bool isDetecetingBlackSquare(int time)
  {
    static Timer t;

    if (t.timeout(time) && this->rsData->readBlackLine() == 255)
    {
      return true;
    }
    else if (this->rsData->readBlackLine() != 255)
    {
      t.resetTimeout();
    }
    return false;
  }

  bool pickUp()
  {
    static Timer t;
    static Timer t1;
    bool blackSquereDetected = this->isDetecetingBlackSquare(125);
    if (blackSquereDetected)
    {
      catchObj = true;
    }
    if (catchObj)
    {
      gripperCatch();

      if (t1.executeOnce(0))
      {
        moveSpeed(220, 220);
      }

      if (t1.timeout(300))
      {
        if (!isRotated)
        {
          isRotated = didMoveLeft(255, 11);
        }
      }

      if (isRotated)
      {
        if (t.executeOnce(0))
        {
          stopMotors();
          // moveSpeed(150, 150);
        }
      }
    }

    return isRotated;
  }
};
