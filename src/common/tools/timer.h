#pragma once
#include <Arduino.h>

const unsigned long APP_START_STAMP = millis();

// & is a reference. It works like pointer for C, but clearer for C++
// it means that the variable timestamp will be changed!!
bool isTimePassedOnce(unsigned long *timestamp, unsigned long pass)
{
  Serial.print(*timestamp);
  if (millis() - *timestamp >= pass)
  {
    *timestamp = millis();
    return true;
  }
  return false;
}

bool isTimeInterval(unsigned long *timestamp, unsigned long shouldPass, unsigned long doFor)
{
  if (millis() - *timestamp >= shouldPass)
  {
    if (millis() - *timestamp >= shouldPass + doFor)
    {
      *timestamp = millis();
    }
    return true;
  }
  return false;
}

// convert to
// long lightStamp = millis(); // millis();

// if (isTimePassedFrom(lightStamp, 2000))
// {
//   // do something
//   doABackFlip();
//   // ando
// }

// if (isTimePassedBetween(lightStamp, 1000, 500)) // show LED for one second

//  or
// long lightStamp = getTime();

// if (timeSince(lightStamp) > 2000) {
//     lightStamp = getTime();
// }

// from

// long lightStamp = millis();

// if(millis() - lightStamp > 2000) {
//     lightStamp = millis();
// }

// if(millis() - lightStamp > 2000) {
//  to do
// if (millis() - lightStamp > 3000) {
//     lightStamp = millis();
//
//}
// }

class Timer
{
private:
  unsigned long lastTime;
  bool triggered;

public:
  Timer() : lastTime(0), triggered(false) {}

  bool interval(unsigned long shouldPass, unsigned long doFor = 0)
  {
    unsigned long now = millis();
    if (now - lastTime >= shouldPass)
    {
      if (now - lastTime >= shouldPass + doFor)
      {
        lastTime = now;
      }
      return true;
    }
    return false;
  }

  bool once(unsigned long shouldPass)
  {
    if (triggered)
      return false;

    unsigned long now = millis();
    if (millis() - lastTime >= shouldPass)
    {
      return true;
    }
    return false;
  }

  bool timeout(unsigned long shouldPass)
  {
    unsigned long now = millis();
    if (millis() - lastTime >= shouldPass)
    {
      return true;
    }
    return false;
  }

  void hardReset()
  {
    lastTime = millis();
    triggered = false;
  }
};
