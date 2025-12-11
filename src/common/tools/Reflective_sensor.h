/**
 * @name ReflectiveSensor
 * @authors Sunny & Vlad & Aria
 * @date 08-12-2025
 */
#pragma once
#include <Arduino.h>
#include "common/constant/reflective_sensor.h"
#include "common/tools/Timer.h"

// --- bitmask tables ---
const uint8_t centerPatterns[] = {0b00011000, 0b00111100};
const uint8_t slightLeftPatterns[] = {
    0b00110000,
    0b01110000,
    0b00111000,
};
const uint8_t slightRightPatterns[] = {0b00001100, 0b00001110, 0b00011100};

const uint8_t hardLeftPatterns[] = {
    0b11111000,
    0b11110000,
    0b11100000,
    0b11000000,
    0b10000000,
};
const uint8_t hardRightPatterns[] = {
    0b00011111,
    0b00001111,
    0b00000111,
    0b00000011,
    0b00000001,
};

const uint8_t allWhite[] = {0b00000000};
const uint8_t allBlack[] = {0b11111111};

// const uint8_t leftTurn[] = {0b11111000, 0b11110000, 0b11111100, 0b11111110};
// const uint8_t rightTurn[] = {0b00011111, 0b00001111, 0b00111111, 0b01111111};

enum LineState
{
    CENTER,
    SLIGHT_LEFT,
    SLIGHT_RIGHT,
    HARD_LEFT,
    HARD_RIGHT,

    ALL_WHITE,
    ALL_BLACK,

    LEFT_TURN,
    RIGHT_TURN
};

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

    bool match(const uint8_t *patterns, int elementCount)
    {
        for (int i = 0; i < elementCount; i++)
        {
            if (this->readBlackLine() == patterns[i])
                return true;
        }
        return false;
    }

    LineState pattern()
    {

        if (match(centerPatterns, sizeof(centerPatterns) / sizeof(centerPatterns[0])))
            return CENTER;

        if (match(slightLeftPatterns, sizeof(slightLeftPatterns) / sizeof(slightLeftPatterns[0])))
            return SLIGHT_LEFT;
        if (match(slightRightPatterns, sizeof(slightRightPatterns) / sizeof(slightRightPatterns[0])))
            return SLIGHT_RIGHT;

        if (match(hardLeftPatterns, sizeof(hardLeftPatterns) / sizeof(hardLeftPatterns[0])))
            return HARD_LEFT;
        if (match(hardRightPatterns, sizeof(hardRightPatterns) / sizeof(hardRightPatterns[0])))
            return HARD_RIGHT;

        // if (match(leftTurn, sizeof(leftTurn) / sizeof(leftTurn[0])))
        //     return LEFT_TURN;
        // if (match(rightTurn, sizeof(rightTurn) / sizeof(rightTurn[0])))
        //     return RIGHT_TURN;

        if (match(allWhite, sizeof(allWhite) / sizeof(allWhite[0])))
            return ALL_WHITE;
        if (match(allBlack, sizeof(allBlack) / sizeof(allBlack[0])))
            return ALL_BLACK;

        return CENTER;
    }
};