#include "follow_single_line.h"

// RS - reflective sensor
ReflectiveSensor rsLine(PINS_RS, PINS_RS_LENGTH, THRESHOLD);

void followLine()
{

  int fullSpeed = 255;
  float slightConf = .8;
  float hardConf = -.8;

  switch (rsLine.pattern())
  {
  case CENTER:
  {
    moveSpeed(fullSpeed, fullSpeed);
    Serial.println("center");
    break;
  };
  case SLIGHT_LEFT:
  {
    moveSpeed(fullSpeed * slightConf, fullSpeed);

    Serial.println("SLIGHT_LEFT");
    break;
  };
  case SLIGHT_RIGHT:
  {
    moveSpeed(fullSpeed, fullSpeed * slightConf);

    Serial.println("SLIGHT_RIGHT");
    break;
  };
  case HARD_LEFT:
  {
    moveSpeed(fullSpeed * hardConf, fullSpeed);
    Serial.println("HARD_LEFT");
    break;
  };
  case HARD_RIGHT:
  {
    moveSpeed(fullSpeed, fullSpeed * hardConf);

    Serial.println("HARD_RIGHT");
    break;
  };
  case ALL_WHITE:
  {
    moveSpeed(fullSpeed * slightConf, fullSpeed * slightConf);

    Serial.println("ALL_WHITE");
    break;
  };

  case ALL_BLACK:
  {
    moveSpeed(fullSpeed, fullSpeed);

    Serial.println("ALL_BLACK");
    break;
  };

  default:
  {
    moveSpeed(fullSpeed, fullSpeed);

    Serial.println(rsLine.readBlackLine(), BIN);
    break;
  }
  }
}