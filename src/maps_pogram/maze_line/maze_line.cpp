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
  lineWhiteStatus = getLineStatus(currenRstData, storedRsWhiteData, 30);

  for (int i = 0; i < 8; i++)
  {
    Serial.println("first index data: ");
    Serial.print(lineWhiteStatus[i]);
  }

  isAllNotWhite = 0;

  for (int i = 0; i < 8; i++)
  {
    isAllNotWhite += lineWhiteStatus[i];
  }

  if (isAllNotWhite == 0)
  {
    if (getRsStatusBlackT.executeOnce(0))
    {
      free(storedRsBlackData);
      storedRsBlackData = getRSValue();
    }
  }

  free(lineBlackStatus);
  lineBlackStatus = getLineStatus(currenRstData, storedRsBlackData, 20);

  for (int i = 0; i < 8; i++)
  {
    Serial.print("black ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(storedRsBlackData[i].mean);
    Serial.print("current: ");
    Serial.println(currenRstData[i].mean);
    Serial.println("black index: ");
    Serial.println(lineBlackStatus[i]);
  }
}
