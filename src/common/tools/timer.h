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
  // timestamp for timer methods
  unsigned long timestampInterval = 0;
  unsigned long timestampIntervalStart = 0;
  unsigned long timestampExecuteOnce = 0;
  bool isTriggeredExecuteOnce = false;
  unsigned long timestampTimeout = 0;

public:
  /**
   * @name interval
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @param milliseconds how much time should pass to return true
   * @param executionTime how long it returns true
   * @details Timer.interval(500) returns True every 500 milliseconds, otherwise False
   * @details Timer.interval(200, 500) wait 200 milliseconds and return True for 500 milliseconds
   * @details Timer.interval(0, 500) WRONG!!! RETURNS FOREVER TRUE
   * @details !Timer.interval(500) use ! to start immidiately
   * @return bool
   */
  bool interval(unsigned long milliseconds, unsigned long executionTime = 0)
  {
    if (timestampInterval == 0)
      timestampInterval = millis();

    unsigned long now = millis();
    if (now - timestampInterval >= milliseconds)
    {
      if (now - timestampInterval >= milliseconds + executionTime)
      {
        timestampInterval = now;
      }
      return true;
    }
    return false;
  }

  /**
   * @name intervalStart
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @param milliseconds how much time should pass to return true
   * @param executionTime how long it returns true
   * @details When executed for first time returns True immidiately
   * @details Timer.interval(500) returns True every 500 milliseconds, otherwise False
   * @details Timer.interval(200, 500) wait 200 milliseconds and return True for 500 milliseconds
   * @details Timer.interval(0, 500) WRONG!!! RETURNS FOREVER TRUE
   * @details !Timer.interval(500) use ! to start immidiately
   * @return bool
   */
  bool intervalStart(unsigned long milliseconds, unsigned long executionTime = 0)
  {
    if (timestampIntervalStart == 0)
    {
      timestampIntervalStart = millis();
      Serial.print("ts");
      return true;
    }

    unsigned long now = millis();

    if (now - timestampIntervalStart >= milliseconds)
    {
      if (now - timestampIntervalStart >= milliseconds + executionTime)
      {
        timestampIntervalStart = now;
      }
      return true;
    }
    return false;
  }

  /**
   * @name executeOnce
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @param milliseconds returns true after milliseconds only once
   * @details Timer.executeOnce(500) will return True once and only once! even in a loop it will be executed once after n milliseconds!!
   * @return bool
   */
  bool executeOnce(unsigned long milliseconds)
  {
    if (isTriggeredExecuteOnce)
      return false;

    unsigned long now = millis();

    if (timestampExecuteOnce == 0)
      timestampExecuteOnce = now;

    if (now - timestampExecuteOnce >= milliseconds)
    {
      isTriggeredExecuteOnce = true;
      return true;
    }
    return false;
  }

  /**
   * @name timeout
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @param milliseconds returns true after specific time forever
   * @details Timer.timeout(300) will return True after timeout and keep returning True
   * @return bool
   */
  bool timeout(unsigned long shouldPass)
  {
    if (timestampTimeout == 0)
      timestampTimeout = millis();

    unsigned long now = millis();
    if (now - timestampTimeout >= shouldPass)
    {
      return true;
    }
    return false;
  }

  /**
   * @name hardReset
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @details RESET ALL TIMERS
   */
  void hardReset()
  {
    timestampInterval = 0;
    timestampExecuteOnce = 0;
    timestampTimeout = 0;

    isTriggeredExecuteOnce = false;
  }

  /**
   * @name resetInterval
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @details reset interval timer
   */
  void resetInterval()
  {
    timestampInterval = 0;
  }

  void resetIntervalStart()
  {
    timestampIntervalStart = 0;
  }
  /**
   * @name resetExecuteOnce
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @details reset executeOnce timer
   */
  void resetExecuteOnce()
  {
    timestampExecuteOnce = 0;
    isTriggeredExecuteOnce = false;
  }

  /**
   * @name resetTimeout
   * @author Fumbre (Vladyslav)
   * @date 14-11-2025
   * @details reset timeout timer
   */
  void resetTimeout()
  {
    timestampTimeout = 0;
  }
};