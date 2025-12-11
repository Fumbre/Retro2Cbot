
/**
 * @name ReflectiveSensor
 * @authors Sunny & Vlad
 * @date 08-12-2025
 */
#pragma once
#include <Arduino.h>
#include "Reflective_read.h"
#include "common/constant/reflective_sensor.h"

class ReflectiveSensor
{

private:
    const int *pins;    // reflective sensor pins
    int pins_rs_length; // length of pins array
    float threshold;    // white range
    uint8_t previousLineStatus = 0;
    uint8_t lineStatus = 0;
    int isBlackCalibArr[8] = {0, 0, 0, 0, 0, 0, 0, 0};

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

public:
    ReflectiveRead *currentSensors;
    ReflectiveRead *reflectiveRead;        // init surface
    ReflectiveRead reflectiveReadBlack[8]; // second surface
    int isBlackCalib = false;
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
     * @name calibration
     * @authors Sunny & Vlad
     * @date 10-12-2025
     * @details get first surface data to reflectiveRead property
     */
    void calibration()
    {
        // calibrate for first surface
        free(reflectiveRead);
        reflectiveRead = getRSValue();

        for (int i = 0; i < 8; i++)
        {
            Serial.println(reflectiveRead[i].mean);
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
                lineStatus |= (128 >> i);
                status |= (128 >> i);
            }
            else
            {
                lineStatus &= ~(128 >> i);
                status &= ~(128 >> i);
            }
        }
        return status;
    }

    void calibrationBlack()
    {
        // Serial.println(lineStatus, BIN);
        for (int i = 0; i < 8; i++)
        {
            if (!(lineStatus & (128 >> i)) && (int)isBlackCalibArr[i] == 0)
            {
                int value = analogRead(pins[i]);
                reflectiveReadBlack[i].update(value);
                isBlackCalibArr[i] = 1;
                // Serial.print("Sensor ");
                // Serial.print(i);
                // Serial.print(" ");
                // Serial.println(reflectiveReadBlack[i].mean);
            }
        }
        // Serial.println("");
    }

    bool getIsBlackCalib()
    {
        for (int i = 0; i < 8; i++)
        {
            if (isBlackCalibArr[i])
            {
                isBlackCalib = true;
            }
            else
            {
                isBlackCalib = false;
                break;
            }
        }
        return isBlackCalib;
    }
};