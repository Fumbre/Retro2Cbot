#include "maze_line.h"

Stats *storedRsWhiteData;
Stats *currenRstData;
Stats *storedRsBlackData;

Timer getRsStatusT;
Timer getRsStatusBlackT;

int *lineWhiteStatus;
int *lineBlackStatus;

int isAllNotWhite = 0;

void followLine()
{
  if (getRsStatusT.executeOnce(0))
  {
    storedRsWhiteData = getRSValue();
  }

  free(currenRstData);
  currenRstData = getRSValue();

  free(lineWhiteStatus);
  lineWhiteStatus = getLineStatus(currenRstData, storedRsWhiteData, 15);

  for (int i = 0; i < 8; i++)
  {
    Serial.println("first index data: ");
    Serial.print(lineWhiteStatus[i]);
  }

  // isAllNotWhite = 0;

  // for (int i = 0; i < 8; i++)
  // {
  //   isAllNotWhite += lineWhiteStatus[i];
  // }

  // Serial.print("change");
  // delay(2000);

  // if (isAllNotWhite == 0)
  // {
  //   if (getRsStatusBlackT.executeOnce(0))
  //   {
  //     free(storedRsBlackData);
  //     storedRsBlackData = getRSValue();
  //   }
  // }

  // free(lineBlackStatus);
  // lineBlackStatus = getLineStatus(currenRstData, storedRsBlackData, 20);

  // for (int i = 0; i < 8; i++)
  // {
  //   Serial.print("black ");
  //   Serial.print(i);
  //   Serial.print(": ");
  //   Serial.println(storedRsBlackData[i].mean);
  //   Serial.println(currenRstData[i].mean);
  //   Serial.println("black index: ");
  //   Serial.println(lineWhiteStatus[i]);
  // }
}
