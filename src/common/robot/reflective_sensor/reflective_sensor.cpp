#include "reflective_sensor.h"

const unsigned int sampleIntervalMs = 10; // sample every 10 ms (~100 Hz)
                                          // adjust if you want fewer/more samples

// Stats per sensor using Welford's algorithm

Stats *getRSValue()
{
    static Stats stats[8];

    // Read and update stats
    for (int i = 0; i < PINS_RS_LENGTH; ++i)
    {
        int v = analogRead(PINS_RS[i]);
        stats[i].update(v);
    }

    return stats;
}
