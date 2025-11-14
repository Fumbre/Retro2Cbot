#pragma once
#include <Arduino.h>

/**
 * @name Timer
 * @author Fumbre (Vladyslav)
 * @date 14-11-2025
 * @details Timer class for easier access to millis calculation
 */

class Timer
{
private:
  unsigned long stampEvery = 0;
  unsigned long stampOnce = 0;
  bool triggered = false;
  unsigned long stampTimeout = 0;

public:
  /**
   * @name Timer().every
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @param waitTime(>=0)miliseconds  how much timer should wait until true
   * @param workTime(>=0)miliseconds  how long timer should return true
   * @details Timer.every(500) will return True every 500 miliseconds
   * @details Timer.every(200, 500) will return true after 200 miliseconds continiously for 500 miliseconds, after 500 will return False.
   * @details Timer.every(0, 500) WRONG!!! will be returning true all the time
   * @return bool
   */
  bool every(unsigned long waitTime, unsigned long workTime = 0)
  {
    if (stampEvery == 0)
      stampEvery = millis();

    unsigned long now = millis();
    if (now - stampEvery >= waitTime)
    {
      if (now - stampEvery >= waitTime + workTime)
      {
        stampEvery = now;
      }
      return true;
    }
    return false;
  }

  /**
   * @name Timer().once
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @param shouldPass(>=0)miliseconds  after this time return True once
   * @details Timer.once(500) will return True once and only once! even in a loop it will be executed once after shouldPass time!!
   * @return bool
   */
  bool once(unsigned long shouldPass)
  {
    if (triggered)
      return false;

    if (stampOnce == 0)
      stampOnce = millis();

    unsigned long now = millis();
    if (now - stampOnce >= shouldPass)
    {
      triggered = true;
      return true;
    }
    return false;
  }

  /**
   * @name Timer().timeout
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @param shouldPass(>=0)miliseconds  after this time return True all the time
   * @details Timer.timeout(300) will return True after timeout and keep returning True
   * @return bool
   */
  bool timeout(unsigned long shouldPass)
  {
    if (stampTimeout == 0)
      stampTimeout = millis();

    unsigned long now = millis();
    if (now - stampTimeout >= shouldPass)
    {
      return true;
    }
    return false;
  }

  /**
   * @name Timer().hardReset
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @details RESET ALL TIMERS
   */
  void hardReset()
  {
    unsigned long now = millis();

    stampEvery = now;
    stampOnce = now;
    stampTimeout = now;

    triggered = false;
  }

  /**
   * @name Timer().resetEvery
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @details reset Timer().every timer
   */
  void resetEvery()
  {
    stampEvery = millis();
  }

  /**
   * @name Timer().resetOnce
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @details reset Timer().once timer
   */
  void resetOnce()
  {
    stampOnce = millis();
    triggered = false;
  }

  /**
   * @name Timer().resetTimeout
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @details reset Timer().timeout timer
   */
  void resetTimeout()
  {
    stampTimeout = millis();
  }
};