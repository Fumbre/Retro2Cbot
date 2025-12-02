#include "maze_line.h"

Stats *storedRsWhiteData;
Stats *currenRstData;
Stats *storedRsBlackData;

Timer getRsStatusT;
Timer getRsStatusBlackT;

int *lineWhiteStatus;
int *lineBlackStatus;

int isAllwhite = 0;

void followLine()
{
  if (getRsStatusT.executeOnce(0))
  {
    storedRsWhiteData = getRSValue();
    Serial.println(storedRsWhiteData[0].mean);
  }

  free(currenRstData);
  currenRstData = getRSValue();

  Serial.println(currenRstData[0].mean);

  free(lineWhiteStatus);
  lineWhiteStatus = getLineStatus(currenRstData, storedRsWhiteData, 20);

  isAllwhite = 0;

  for (int i = 0; i < 8; i++)
  {
    isAllwhite += lineWhiteStatus[i];
  }

  // Serial.print(lineWhiteStatus[0]);

  // if (isAllwhite == 7)
  // {
  //   if (getRsStatusBlackT.executeOnce(0))
  //   {
  //     free(storedRsBlackData);
  //     storedRsBlackData = getRSValue();
  //   }
  // }

  // free(lineBlackStatus);
  // lineBlackStatus = getLineStatus(storedRsWhiteData, storedRsBlackData, 20);

  // for (int i = 0; i < 8; i++)
  // {

  //   Serial.print("black ");
  //   Serial.print(i);
  //   Serial.print(": ");
  //   Serial.println(lineBlackStatus[i]);
  // }
}
