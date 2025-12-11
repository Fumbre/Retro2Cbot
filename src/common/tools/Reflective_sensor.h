#include "common/tools/Timer.h"

/**
 * @name ReflectiveSensor
 * @authors Sunny & Vlad
 * @date 08-12-2025
 */
#pragma once
#include <Arduino.h>
#include "common/constant/reflective_sensor.h"

struct ReflectiveRead
{
    unsigned long count = 0;
    double mean = 0.0;
    double m2 = 0.0; // sum of squares of differences for variance
    int minimum = 1023;
    int maximum = 0;
    void update(int x)
    {
        count = 1;
        double dx = x - mean;
        mean += dx / count;
        double dx2 = x - mean;
        m2 += dx * dx2;
        if (x < minimum)
            minimum = x;
        if (x > maximum)
            maximum = x;
    }
};

class ReflectiveSensor
{

private:
    const int *pins;    // reflective sensor pins
    int pins_rs_length; // length of pins array
    float threshold;    // white range

    ReflectiveRead *getRSValue()
    {
        ReflectiveRead *stats = new ReflectiveRead[8];

        // Read and update stats
        for (int i = 0; i < PINS_RS_LENGTH; ++i)
        {
            int v = analogRead(PINS_RS[i]);
            stats[i].update(v);
        }

        return stats;
    }

    uint8_t blackCalibration;
    int isBlackCalib = 0;

public:
    ReflectiveRead *currentSensors;
    ReflectiveRead *reflectiveReadInit;    // init surface
    ReflectiveRead reflectiveReadBlack[8]; // second surface

    uint8_t currentLineStatus = 0;
    uint8_t previousLineStatus = 0;

    bool isBlackCalibrated = false;

    /**
     * @name ReflectiveSensor
     * @authors Sunny & Vlad
     * @date 08-12-2025
     * @details construction function
     * @param pins pins of reflective sensor
     * @param pins_rs_length length of pins array
     * @param threshold  white range
     */
    ReflectiveSensor(const int *pins, const int pins_rs_length, const float threshold)
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

    /**
     * @name calibrationInit
     * @authors Sunny & Vlad
     * @date 10-12-2025
     * @details get first surface data to reflectiveRead property
     */
    void calibrationInit()
    {
        // calibrate for first surface
        free(reflectiveReadInit);
        reflectiveReadInit = getRSValue();
    }

    void calibrationBlack()
    {
        if (isBlackCalib < pins_rs_length)
        {
            uint8_t reflectiveReadChange = this->getLineDifference(this->reflectiveReadInit, threshold);

            for (int i = 0; i < pins_rs_length; i++)
            {
                if (!(reflectiveReadChange & (128 >> i)) && !(blackCalibration & (128 >> i)))
                {
                    this->reflectiveReadBlack[i].mean = analogRead(PINS_RS[i]);

                    blackCalibration |= (128 >> i);

                    isBlackCalib++;
                }
            }
        }
        else
        {
            isBlackCalibrated = true;
        }
    }

    /**
     * @name getLineDifference
     * @authors Sunny & Vlad
     * @date 10-12-2025
     * @details get first line status with difference
     * @param compare (ReflectiveRead instecnce, to compare with current surface data)
     * @param reflectiveDifference(how much difference will be okay as the same data)
     * @return uint8_t
     */
    uint8_t getLineDifference(ReflectiveRead *compare, int reflectiveDifference)
    {
        uint8_t status = 0;

        free(currentSensors);
        currentSensors = getRSValue();
        for (int i = 0; i < pins_rs_length; i++)
        {
            if ((
                    (currentSensors[i].mean - reflectiveDifference <= compare[i].mean) &&
                    (currentSensors[i].mean + reflectiveDifference >= compare[i].mean)))
            {
                status |= (128 >> i);
            }
            else
            {
                status &= ~(128 >> i);
            }
        }
        return status;
    }

    uint8_t getLineStatusMoreThan(ReflectiveRead *compare, int reflectiveDifferenceMinus)
    {
        uint8_t status = 0;

        free(currentSensors);
        currentSensors = getRSValue();
        for (int i = 0; i < pins_rs_length; i++)
        {
            if (currentSensors[i].mean + reflectiveDifferenceMinus >= compare[i].mean)
            {
                status |= (128 >> i);
            }
            else
            {
                status &= ~(128 >> i);
            }
        }
        return status;
    }

    uint8_t readBlackLine()
    {
        static Timer t;

        if (t.executeOnce(0))
        {
            this->calibrationInit();
        }
        this->calibrationBlack();

        if (!this->isBlackCalibrated)
            return 0;

        uint8_t currentBlackStatus = this->getLineStatusMoreThan(this->reflectiveReadBlack, 75);

        return currentBlackStatus;
        // Serial.println(currentBlackStatus, BIN);
    }
};