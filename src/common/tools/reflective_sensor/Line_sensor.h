/**
 * @name LineReading
 * @author Aria
 * @date 01-12-2025
 */
#pragma once
#include <Arduino.h>

struct LineReading
{
    uint8_t mask;
    int values[8];
};

class LineSensor
{

private:
    int *pins;
    int count;
    int threshold;

public:
    LineSensor(int *pins, int count, int threshold)
    {
        this->pins = pins;
        this->count = count;
        this->threshold = threshold;
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
        r.mask = 0;

        for (int i = 0; i < count; i++)
        {
            int reading = analogRead(pins[i]);
            r.values[i] = reading;
            Serial.println(reading);
            if (reading > threshold)
            {
                // A0 = leftmost → highest bit
                r.mask |= (1 << (count - 1 - i));
            }
        }
        return r;
    }
};