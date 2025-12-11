#include "reflective_sensor.h"

ReflectiveSensor rs(PINS_RS, PINS_RS_LENGTH, 225);

uint8_t getBlackLine()
{
  return rs.readBlackLine();
}

// void calibrate()
// {
//   static Timer t;

//   if (t.executeOnce(0))
//   {
//     rs.calibrationInit();
//   }
//   rs.calibrationBlack();
// }

// void readBlackLine()
// {
//   if (!rs.isBlackCalibrated)
//     return;

//   uint8_t currentBlackStatus = rs.getLineStatusMoreThan(rs.reflectiveReadBlack, 75);
//   Serial.println(currentBlackStatus, BIN);
// }

// =========================

// bool detectSquer()
// {
//   static Timer t;

//   // Serial.print("lineDif: ");
//   // Serial.println(rs.getLineDifference(rs.reflectiveReadBlack, 370));
//   // Serial.print("reflectiveReadBlack: ");
//   // Serial.print(rs.reflectiveReadBlack[0].mean);
//   // Serial.print(" ");
//   // Serial.print(rs.reflectiveReadBlack[1].mean);
//   // Serial.print(" ");
//   // Serial.print(rs.reflectiveReadBlack[2].mean);
//   // Serial.print(" ");
//   // Serial.print(rs.reflectiveReadBlack[3].mean);
//   // Serial.print(" ");
//   // Serial.print(rs.reflectiveReadBlack[4].mean);
//   // Serial.print(" ");
//   // Serial.print(rs.reflectiveReadBlack[5].mean);
//   // Serial.print(" ");
//   // Serial.print(rs.reflectiveReadBlack[6].mean);
//   // Serial.print(" ");
//   // Serial.print(rs.reflectiveReadBlack[7].mean);
//   // Serial.println(" ");

//   Serial.print("diff: ");
//   Serial.println(rs.getLineDifference(rs.reflectiveReadBlack, 370) == 255);
//   Serial.print("black set?: ");
//   Serial.println(rs.getIsBlackCalib());
//   Serial.print("time?: ");
//   Serial.println(t.timeout(105));

//   if (t.timeout(105) && rs.getIsBlackCalib() && rs.getLineDifference(rs.reflectiveReadBlack, 370) == 255)
//   {
//     return true;
//   }
//   else if (rs.getLineDifference(rs.reflectiveReadBlack, 370) != 255)
//   {
//     t.resetTimeout();
//   }
//   return false;
// }
