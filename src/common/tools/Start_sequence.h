#pragma once
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/tools/Timer.h"
#include "common/robot/gripper/gripper.h"
#include "common/robot/movement/movement.h"
#include "common/robot/movement/movementPID.h"

/**
 * @name StartSequence
 * @author Fumbre (Vladyslav)
 * @date 16-12-2025
 * @details StartSequence class to start sequence
 */

class StartSequence
{
private:
  ReflectiveSensor *rsData;

  bool isRotated = false;
  bool catchObj = false;

public:
  StartSequence(ReflectiveSensor *rsData)
  {
    this->rsData = rsData;
  }

  void onPossition(int pos)
  {
    // the easiest approach to start sequence
    if (pos == 1)
    {
      // if everything is white - go forward
      if (this->rsData->readBlackLine() == 0)
      {
        moveSpeed(230, 230);
      }
    }
    // todo pos == 2
    // todo pos == 3
  }

  /**
   * @name isDetecetingBlackSquare
   * @author Fumbre (Vladyslav)
   * @date 16-12-2025
   * @param time int time 0-999
   * @details if black squeare (11111111) detected longer than @param time return true, otherwise false
   * @return bool
   */
  bool isDetecetingBlackSquare(int time)
  {
    static Timer t;

    if (t.timeout(time) && this->rsData->readBlackLine() == 255)
    {
      return true;
    }
    else if (this->rsData->readBlackLine() != 255)
    {
      // reset timeout if rsData recieve not black
      t.resetTimeout();
    }
    return false;
  }

  /**
   * @name pickUp
   * @author Fumbre (Vladyslav)
   * @date 16-12-2025
   * @details pick an object up and do a rotatation to the left
   * @return bool
   */
  bool pickUp()
  {
    static Timer t;
    static Timer t1;

    // if blackSquereDetected longer than 125ms return true
    bool blackSquereDetected = this->isDetecetingBlackSquare(125);
    if (blackSquereDetected)
    {
      catchObj = true; // object catched
    }
    if (catchObj)
    {
      gripperCatch();

      // after catch go forward
      if (t1.executeOnce(0))
      {
        moveSpeed(220, 220);
      }

      // stop going forward after timeout
      if (t1.timeout(300))
      {
        if (!isRotated)
        {
          isRotated = didMoveLeft(255, 11); // when rotation done returns true
        }
      }

      if (isRotated)
      {
        if (t.executeOnce(0))
        {
          // double check this idea
          stopMotors(); // improve??
          // moveSpeed(150, 150);
        }
      }
    }

    return isRotated;
  }
};
