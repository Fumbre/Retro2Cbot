#pragma once
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/tools/Timer.h"
#include "common/robot/gripper/gripper.h"
#include "common/robot/movement/movement.h"
#include "common/robot/movement/movementPID.h"

#include "common/robot/sonar/sonar.h"

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

  bool readyToStart(int pos)
  {
    static Timer t;
    // the easiest approach to start sequence
    if (pos == 1)
    {
      if (t.intervalStart(100))
      {
        Serial.print(getDistanceCM_Front());
        if (getDistanceCM_Front() > 20)
        {
          return true;
        }
      }

      return false;
    }
    if (pos == 2)
    {
      // recieved data return true
      return false;
    }
    // todo pos == 2
    // todo pos == 3

    return false;
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
  bool startWithPickUp(int robotSpeed, int rotatePulses)
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
        moveSpeed(robotSpeed, robotSpeed);
      }

      // stop going forward after timeout
      if (t1.timeout(300))
      {
        if (!isRotated)
        {
          // try to use
          moveSpeed(-255, 255);
          LineState pattern = rsData->pattern();
          if (pattern == CENTER || pattern == SLIGHT_LEFT || pattern == SLIGHT_RIGHT)
          {
            moveStopAll();
            isRotated = true;
          }

          // isRotated = didMoveLeft(255, rotatePulses); // when rotation done returns true
        }
      }

      // delte this if prev thing works
      // if (isRotated)
      // {
      //   if (t.executeOnce(0))
      //   {
      //     // double check this idea
      //     if (this->rsData->readBlackLine() == 0)
      //     {
      //       moveSpeed(robotSpeed, robotSpeed * -0.5);
      //     }
      //     // stopMotors(); // improve??
      //     // moveSpeed(150, 150);
      //   }
      // }
    }

    return isRotated;
  }
};
