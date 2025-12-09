
/**
 * @name ReflectiveSensor
 * @authors Sunny & Vlad
 * @date 08-12-2025
 */
#pragma once
#include <Arduino.h>
#include "Reflective_read.h"

class ReflectiveSensor
{

private:
    int *pins;          // reflective sensor pins
    int pins_rs_length; // length of pins array
    float threshold;    // white range
    ReflectiveRead *reflectiveReadBlack;
    ReflectiveRead *reflectiveRead;
    uint8_t previousLineStatus = 0;
    uint8_t lineStatus = 0;

public:
    /**
     * @name ReflectiveSensor
     * @authors Sunny & Vlad
     * @date 08-12-2025
     * @details construction function
     * @param pins pins of reflective sensor
     * @param pins_rs_length length of pins array
     * @param threshold  white range
     */
    ReflectiveSensor(int *pins, int pins_rs_length, float threshold)
    {
        this->pins = pins;
        this->pins_rs_length = pins_rs_length;
        this->threshold = threshold;
    }

    /**
     * @name setup
     * @authors Sunny & Vlad
     * @date 08-12-2025
     */
    void setup()
    {
        for (int i = 0; i < pins_rs_length; i++)
        {
            pinMode(pins[i], INPUT);
        }
    }

    void calibration()
    {
        // calibrate for first surface
        for (int i = 0; i < pins_rs_length; i++)
        {
            int value = analogRead(pins[i]);
            reflectiveRead[i].update(value);
        }
    }

    void getDifference(ReflectiveRead *compare, int reflectiveDifference)
    {
        static ReflectiveRead sensor;
        for (int i = 0; i < pins_rs_length; i++)
        {
            int value = analogRead(pins[i]);
            sensor.update(value);

            if ((
                    (sensor.getCurrrentAvgerageNumber() - reflectiveDifference <= compare[i].getCurrrentAvgerageNumber()) &&
                    (sensor.getCurrrentAvgerageNumber() + reflectiveDifference >= compare[i].getCurrrentAvgerageNumber())))
            {
                lineStatus |= (1 << i);
            }
            else
            {
                lineStatus &= (1 << i);
            }
        }
    }

    void calibrationBlack()
    {
        for (int i = 0; i < 8; i++)
        {
            if ((lineStatus & (1 << i)) != 0 && reflectiveReadBlack[i].getCurrrentAvgerageNumber() != 0)
            {
                int value = analogRead(pins[i]);
                reflectiveReadBlack[i].update(value);
            }
        }
    }
};