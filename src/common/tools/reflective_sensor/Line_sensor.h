/**
 * @name LineReading
 * @author Aria
 * @date 01-12-2025
 */
#pragma once
#include <Arduino.h>
#include "common/tools/Welford.h"

struct LineReading
{
    uint8_t mask;
    int values[8];
};

class LineSensor
{

private:
    const int *pins;
    int count;
    Welford welford;

public:
    LineSensor(const int *pins, int count)
    {
        this->pins = pins;
        this->count = count;
    }

    void setup()
    {
        for (int i = 0; i < count; i++)
        {
            pinMode(pins[i], INPUT);
        }
    }
    LineReading read()
    {
        LineReading r;
        // caculate threshold
        for (int i = 0; i < count; i++)
        {
            int reading = analogRead(pins[i]);
            r.values[i] = reading;
            welford.update(reading);
        }
        float threshold = welford.getCurrrentAvgerageNumber() - welford.getStandardDeviation();
        Serial.print("Threshold: ");
        Serial.println(threshold);
        welford.reset();
        r.mask = 0;
        for (int i = 0; i < count; i++)
        {
            if (r.values[i] > 700)
            {
                // A0 = leftmost → highest bit
                r.mask |= (1 << (count - 1 - i));
                Serial.print("current value: ");
                Serial.println(r.values[i]);
            }
        }
        return r;
    }
};