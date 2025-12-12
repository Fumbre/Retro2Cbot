#include "follow_single_line.h"

ReflectiveSensor rs(PINS_RS, PINS_RS_LENGTH, 225);

void followLine()
{
  switch (rs.pattern())
  {
  case CENTER:
  {
    Serial.println(rs.readBlackLine(), BIN);

    Serial.println("center");
    break;
  };
  case SLIGHT_LEFT:
  {
    Serial.println("SLIGHT_LEFT");
    break;
  };
  case SLIGHT_RIGHT:
  {
    Serial.println("SLIGHT_RIGHT");
    break;
  };
  case HARD_LEFT:
  {
    Serial.println("HARD_LEFT");
    break;
  };
  case HARD_RIGHT:
  {
    Serial.println("HARD_RIGHT");
    break;
  };
  case ALL_WHITE:
  {
    Serial.println("ALL_WHITE");
    break;
  };

  case ALL_BLACK:
  {
    Serial.println("ALL_BLACK");
    break;
  };

  default:
  {
    Serial.println(rs.readBlackLine(), BIN);
    break;
  }
  }
}