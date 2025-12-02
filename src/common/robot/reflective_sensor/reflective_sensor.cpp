#include "reflective_sensor.h"

// Stats per sensor using Welford's algorithm

Stats *getRSValue()
{
    Stats *s = new Stats[8];

    // Read and update stats
    for (int i = 0; i < PINS_RS_LENGTH; ++i)
    {
        int v = analogRead(PINS_RS[i]);
        s[i].update(v);
    }

    return s;
}

int *getLineStatus(Stats currenRstData[], Stats storedRsData[], int reflectiveDifference)
{

    int *lineStatus = new int[PINS_RS_LENGTH];
    for (int i = 0; i < PINS_RS_LENGTH; i++)
    {
        if ((
                (storedRsData[i].mean <= currenRstData[i].mean && currenRstData[i].mean - reflectiveDifference <= storedRsData[i].mean) ||
                (storedRsData[i].mean >= currenRstData[i].mean && currenRstData[i].mean + reflectiveDifference >= storedRsData[i].mean)))
        {
            lineStatus[i] = 1;
        }
        else
        {
            lineStatus[i] = 0;
        }
    }

    return lineStatus;
}