class Rs_calibrate
{
private:
    /* data */
public:
    Rs_calibrate(/* args */);
    ~Rs_calibrate();
};

Rs_calibrate::Rs_calibrate(/* args */)
{
}

Rs_calibrate::~Rs_calibrate()
{
}

// Stats *getRSValue()
// {
//     Stats *s = new Stats[8];

//     // Read and update stats
//     for (int i = 0; i < PINS_RS_LENGTH; ++i)
//     {
//         int v = analogRead(PINS_RS[i]);
//         s[i].update(v);
//     }

//     return s;
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

// struct Stats
// {
//     unsigned long count = 0;
//     double mean = 0.0;
//     double m2 = 0.0; // sum of squares of differences for variance
//     int minimum = 1023;
//     int maximum = 0;
//     void update(int x)
//     {
//         count++;
//         double dx = x - mean;
//         mean += dx / count;
//         double dx2 = x - mean;
//         m2 += dx * dx2;
//         if (x < minimum)
//             minimum = x;
//         if (x > maximum)
//             maximum = x;
//     }
// };

// Stats *getRSValue();

// int *getLineStatus(Stats currenRstData[], Stats storedRsData[], int reflectiveDifference);

// ================================
// header

// struct Stats
// {
//   unsigned long count = 0;
//   double mean = 0.0;
//   double m2 = 0.0; // sum of squares of differences for variance
//   int minimum = 1023;
//   int maximum = 0;
//   void update(int x)
//   {
//     count++;
//     double dx = x - mean;
//     mean += dx / count;
//     double dx2 = x - mean;
//     m2 += dx * dx2;
//     if (x < minimum)
//       minimum = x;
//     if (x > maximum)
//       maximum = x;
//   }
// };

// Stats *getRSValue();

// int *getLineStatus(Stats currenRstData[], Stats storedRsData[], int reflectiveDifference);
