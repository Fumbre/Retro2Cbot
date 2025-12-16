
// conclude the move forward t obe real in forward;
// check left and right sensor to calib between section;
// the same for 3 lines of black and white;
// check for 25 millist the black sequence use gripper then turn left, if recive 000 11 000 go to next map program;
#pragma once
#include "common/robot/reflective_sensor/Reflective_sensor.h"
#include "common/tools/Timer.h"
#include "common/robot/gripper/gripper.h"

class sequenceStart
{
private:
  ReflectiveSensor *rsData;

public:
  sequenceStart(ReflectiveSensor *rsData)
  {
    this->rsData = rsData;
  }

  bool isDetecetingBlackSquare()
  {
    static Timer t;

    if (!t.timeout(30) && this->rsData->readBlackLine() == 255)
    {
      return true;
    }
    else
    {
      t.resetTimeout();
    }
    return false;
  }
};
