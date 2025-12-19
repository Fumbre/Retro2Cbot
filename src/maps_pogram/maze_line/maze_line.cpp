#include "maze_line.h"

// RS - reflective sensor
ReflectiveSensor rsMaze(PINS_RS, PINS_RS_LENGTH, THRESHOLD, MARGIN_SURFACE);

float slightConf = 0.7;
float hardConf = 0.3;

LineState prevStatus;

bool huj = false;
bool justNow = false;

void mazeLine()
{
  int speed = 220;

  static Timer t;
  LineState currentLineStatus = rsMaze.pattern();

  if (huj && !justNow)
  {
    if (!t.timeout(100))
    {
      moveSpeed(255, -150);
      return;
    }
    else
    {
      huj = false;
      justNow = true;
    }
  }

  switch (currentLineStatus)
  {
  case CENTER:

    moveSpeed(speed, speed);
    Serial.println("CENTER");
    break;
  case SLIGHT_LEFT:

    moveSpeed(speed * slightConf, speed);
    Serial.println("SLIGHT_LEFT");
    break;
  case SLIGHT_RIGHT:

    moveSpeed(speed, speed * slightConf);
    Serial.println("SLIGHT_RIGHT");
    break;

  case LEFT_TURN:
    moveSpeed(-150, speed);
    prevStatus = LEFT_TURN;
    Serial.println("LEFT_TURN");
    break;

  case RIGHT_TURN:
    moveSpeed(speed, -150);
    huj = true;
    justNow = false;
    t.resetTimeout();
    prevStatus = RIGHT_TURN;

    Serial.println("RIGHT_TURN");
    break;
  case ALL_WHITE:

    if (prevStatus == RIGHT_TURN)
    {
      moveSpeed(speed, -255);
    }

    if (prevStatus == LEFT_TURN)
    {
      moveSpeed(-255, speed);
    }

    Serial.println("ALL_WHITE");
    break;
  case ALL_BLACK:
    moveSpeed(speed, speed);
    prevStatus = RIGHT_TURN;

    Serial.println("ALL_BLACK");
    break;
  }
}

int getPWMValue(int speed)
{
  speed = constrain(speed, 0, FULL_SPEED);
  int pwm = (float)speed / FULL_SPEED * FULL_PWM_VALUE;
  return constrain(pwm, 0, FULL_PWM_VALUE);
}

void mazeLineSetup()
{
  setupMotor();
  rsMaze.setup();
}
