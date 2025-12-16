// conclude the move forward t obe real in forward;
// check left and right sensor to calib between section;
// the same for 3 lines of black and white;
// check for 25 millist the black sequence use gripper then turn left, if recive 000 11 000 go to next map program;
#pragma once
#include "common/robot/reflective_sensor/Reflective_sensor.h"
#include "common/tools/Timer.h"
#include "common/robot/gripper/gripper.h"

class SequenceStart
{
private:
  ReflectiveSensor *rsData;

  bool isDetecetingBlackSquare()
  {
    static Timer t;

    Serial.println(this->rsData->readBlackLine());

    if (t.timeout(3000) && this->rsData->readBlackLine() == 255)
    {
      return true;
    }
    else if (this->rsData->readBlackLine() != 255)
    {
      t.resetTimeout();
    }
    return false;
  }

public:
  SequenceStart(ReflectiveSensor *rsData)
  {
    this->rsData = rsData;
  }

  void pickUp()
  {
    bool catchObj = false;
    bool test = this->isDetecetingBlackSquare();
    if (test)
    {
      catchObj = true;
    }
    if (catchObj)
    {
      gripperCatch();
    }
  }
};
