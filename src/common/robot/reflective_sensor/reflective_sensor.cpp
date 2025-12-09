// #include "reflective_sensor.h"

// // Stats per sensor using Welford's algorithm

// Stats *getRSValue()
// {
//     static Stats stats[8];

//     // Read and update stats
//     for (int i = 0; i < PINS_RS_LENGTH; ++i)
//     {
//         int v = analogRead(PINS_RS[i]);
//         stats[i].update(v);
//     }

//     return stats;
// }

// int *getLineStatus(Stats currenRstData[], Stats storedRsData[], int reflectiveDifference)
// {

//     int *lineStatus = new int[PINS_RS_LENGTH];
//     for (int i = 0; i < PINS_RS_LENGTH; i++)
//     {
//         if ((
//                 (currenRstData[i].mean - reflectiveDifference <= storedRsData[i].mean) &&
//                 (currenRstData[i].mean + reflectiveDifference >= storedRsData[i].mean)))
//         {
//             lineStatus[i] = 1;
//         }
//         else
//         {
//             lineStatus[i] = 0;
//         }
//     }

//     return lineStatus;
// }