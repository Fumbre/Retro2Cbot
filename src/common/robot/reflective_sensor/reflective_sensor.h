/**
 * @name ReflectiveSensor
 * @authors Fumbre (Vladyslav) & Aria & Sunny & Uraib
 * @date 08-12-2025
 */
#pragma once
#include <Arduino.h>
#include "common/constant/reflective_sensor.h"
#include "common/tools/Timer.h"

// --- bitmask tables ---
const uint8_t centerPatterns[] = {0b00011000, 0b00111100};
const uint8_t slightLeftPatterns[] = {
    0b01100000,
    0b00110000,
    0b01110000,
    0b00111000,
};
const uint8_t slightRightPatterns[] = {
    0b00000110,
    0b00001100,
    0b00001110,
    0b00011100,
};

const uint8_t hardLeftPatterns[] = {
    0b11100000,
    0b11000000,
    0b10000000,
};
const uint8_t hardRightPatterns[] = {
    0b00000111,
    0b00000011,
    0b00000001,
};

const uint8_t allWhite[] = {0b00000000};
const uint8_t allBlack[] = {0b11111111};

// 0b11111110
const uint8_t leftTurn[] = {0b11111000, 0b11110000, 0b11111100};

// 0b01111111
const uint8_t rightTurn[] = {0b00011111, 0b00001111, 0b00111111};

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

/**
 * @name ReflectiveRead
 * @authors Uraib
 * @date 04-12-2025
 */
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
    float threshold;    // range to consider as a second value for reflective sensor
    int marginError;    // margin surface THRESHOLD

    ReflectiveRead *reflectiveReadInit;    // init surface
    ReflectiveRead reflectiveReadBlack[8]; // second surface
    uint8_t blackCalibration;              // check how much pins are calibrated
    int blackCalibratedLength = 0;         // how much sensor are calibreted for black color
    bool isBlackCalibrated = false;        // is Black collor fully calibrated

    /**
     * @name ReflectiveRead
     * @authors Fumbre (Vladyslav)
     * @date 04-12-2025
     * @return ReflectiveRead array (analog read data of reflective sensor)
     */
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

    /**
     * @name calibrationInit
     * @authors Sunny & Vlad
     * @date 10-12-2025
     * @details get first surface data to reflectiveRead property
     */
    void calibrationInit()
    {
        // calibrate for first surface
        free(this->reflectiveReadInit);
        this->reflectiveReadInit = getRSValue();
    }

    /**
     * @name calibrationBlack
     * @authors Fumbre (Vladyslav)
     * @date 10-12-2025
     * @details calibration for second surface data
     */
    void calibrationBlack()
    {
        if (this->blackCalibratedLength < this->pins_rs_length)
        {
            uint8_t reflectiveReadChange = this->getLineDifference(this->reflectiveReadInit, this->threshold);

            for (int i = 0; i < pins_rs_length; i++)
            {
                if (!(reflectiveReadChange & (128 >> i)) && !(this->blackCalibration & (128 >> i)))
                {
                    this->reflectiveReadBlack[i].mean = analogRead(PINS_RS[i]);

                    this->blackCalibration |= (128 >> i);

                    this->blackCalibratedLength++;
                }
            }
        }
        else
        {
            this->isBlackCalibrated = true;
        }
    }

    /**
     * @name getLineStatusMoreThan
     * @authors Fumbre (Vladyslav)
     * @date 04-12-2025
     * @param compare use ReflectiveRead pointer (array) and compare it with current data
     * @param reflectiveDifferenceMinus use this value to not consider small difference, currentRS is 700 + reflectiveDifferenceMinus > compare
     * @return uint8_t as 1 for true 0 for false
     * @details return line status as BIN
     */
    uint8_t getLineStatusMoreThan(ReflectiveRead *compare, int reflectiveDifferenceMinus)
    {
        uint8_t status = 0;

        free(this->currentSensors);
        this->currentSensors = getRSValue();
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

    /**
     * @name getLineDifference
     * @authors Fumbre (Vladyslav)
     * @date 10-12-2025
     * @details get first line status with difference
     * @param compare (ReflectiveRead instecnce, to compare with current surface data)
     * @param reflectiveDifference(how much difference will be okay as the same data)
     * @return uint8_t if there's some difference return 1 otherwise 0
     */
    uint8_t getLineDifference(ReflectiveRead *compare, int reflectiveDifference)
    {
        uint8_t status = 0;

        free(this->currentSensors);
        this->currentSensors = getRSValue();
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

public:
    ReflectiveRead *currentSensors; // current Reflective Sensors data

    /**
     * @name ReflectiveSensor
     * @authors Sunny & Vlad
     * @date 08-12-2025
     * @details construction function
     * @param pins pins of reflective sensor
     * @param pins_rs_length length of pins array
     * @param threshold after what value second surface will be read
     */
    ReflectiveSensor(const int *pins, const int pins_rs_length, const float threshold, const int marginError)
    {
        this->pins = pins;
        this->pins_rs_length = pins_rs_length;
        this->threshold = threshold;
        this->marginError = marginError;
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
     * @name readBlackLine
     * @authors Fumbre (Vladyslav)
     * @date 08-12-2025
     * @return uint8_t if black is detecter return 1 otherwise 0 as bit mask
     * @details first surface is written than we calibrate second one, and return uint8_t based on second surface data and current rs data
     */
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

        uint8_t currentBlackStatus = this->getLineStatusMoreThan(this->reflectiveReadBlack, this->marginError);

        return currentBlackStatus; // 0b00011000
    }

    /**
     * @name match
     * @authors Aria & Fumbre (Vladyslav)
     * @date 12-12-2025
     * @param patterns uint8_t
     * @param elementCount int Length of pattern array
     * @return bool
     * @details compare pattern list with current uint8_t Black line read (second surface)
     */
    bool match(const uint8_t *patterns, int elementCount)
    {
        for (int i = 0; i < elementCount; i++)
        {
            if (this->readBlackLine() == patterns[i])
                return true;
        }
        return false;
    }

    /**
     * @name pattern
     * @authors Aria & Fumbre (Vladyslav)
     * @date 12-12-2025
     * @return LineState
     * @details return enum position if current pattern match array list of patterns, if no patterns found return CENTER
     */
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

        if (match(leftTurn, sizeof(leftTurn) / sizeof(leftTurn[0])))
            return LEFT_TURN;
        if (match(rightTurn, sizeof(rightTurn) / sizeof(rightTurn[0])))
            return RIGHT_TURN;

        if (match(allWhite, sizeof(allWhite) / sizeof(allWhite[0])))
            return ALL_WHITE;
        if (match(allBlack, sizeof(allBlack) / sizeof(allBlack[0])))
            return ALL_BLACK;

        return CENTER;
    }
};