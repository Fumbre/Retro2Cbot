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