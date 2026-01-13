/**
 * @name Sequence
 * @author Fumbre (Vladyslav)
 * @date 16-12-2025
 * @details Sequence class to start and end sequence
 */

#pragma once

#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/tools/Timer.h"
#include "common/robot/gripper/gripper.h"
#include "common/robot/movement/movement.h"
#include "common/robot/sonar/sonar.h"

#include "common/robot/hc12/hc12.h"

class Sequence
{
private:
  ReflectiveSensor *rsData;

  bool isRotated = false;
  bool catchObj = false;

  bool firstPulsesPassed = false;

public:
  /**
   * @name construct function
   * @author Fumbre (Vladyslav)
   * @date 16-12-2025
   * @param rsData ReflectiveSensor pointer
   * @result Sequence instance
   */
  Sequence(ReflectiveSensor *rsData)
  {
    this->rsData = rsData;
  }

  /**
   * @name readyToStart
   * @author Fumbre (Vladyslav)
   * @date 16-12-2025
   * @param pos 0=>BB016, 1=>BB046, 2=>BB011
   *
   */
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
      String data = receiveDataFromHC12();
      if (data.length() != 0)
      {
        data.trim();
        return data == String("i,BB016");
      }

      return false;
    }

    if (pos == 3)
    {
      // recieved data return true
      String data = receiveDataFromHC12();
      if (data.length() != 0)
      {
        return data == "i,BB046";
      }

      return true;
    }

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
   * @name start
   * @author Fumbre (Vladyslav)
   * @date 16-12-2025
   * @details pick an object up and do a rotatation to the left
   * @return bool
   */
  bool start(int robotSpeed, int robotPulses, int goStraightTime = 300)
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
      if (t1.timeout(goStraightTime))
      {
        if (!isRotated)
        {
          if (didMoveLeft(robotSpeed, robotPulses) || firstPulsesPassed)
          {
            resetMoveLeft();

            firstPulsesPassed = true;

            LineState pattern = rsData->pattern();
            if (pattern == CENTER || pattern == SLIGHT_LEFT || pattern == SLIGHT_RIGHT)
            {
              moveStopAll();
              isRotated = true;
            }
          }
        }
      }
    }
    return isRotated;
  }

  void end(bool *mazePassed, String robotCode)
  {
    static Timer t;

    static Timer sendDataTimer;

    if (!t.timeout(1000)) // go back during 1s
    {
      moveSpeed(-255, -255);
    }
    else // after 1s stop all motors
    {
      moveStopAll();
      if (!mazePassed)
      {
        *mazePassed = true;
      }

      if (sendDataTimer.executeOnce(0, 2000))
      {
        sendDataFromHC12("i," + robotCode);
      }
      return;
    }

    // this is end of sequence (black square)
    if (t.executeOnce(250))
    {
      gripperUnCatch();
    }
  }
};
