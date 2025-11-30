#include "maze_line.h"

Stats *storedRsData;
Stats *currenRstData;

Timer getRsStatusT;

int *lineStatus;

void followLine()
{
  if (getRsStatusT.executeOnce(0))
  {
    storedRsData = getRSValue();
  }

  free(currenRstData);
  currenRstData = getRSValue();

  free(lineStatus);
  lineStatus = getLineStatus(currenRstData, storedRsData, 20);

  for (int i = 0; i < 8; i++)
  {
    Serial.print("now ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(lineStatus[i]);
  }
}
