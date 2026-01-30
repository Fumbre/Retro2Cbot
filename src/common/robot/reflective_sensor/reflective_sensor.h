/**
 * @name ReflectiveSensor
 * @authors Fumbre (Vladyslav) & Aria & Sunny & Uraib
 * @date 08-12-2025
*/

#pragma once

#include <Arduino.h>
#include "common/tools/ARRAY_SIZE.h"
#include "common/constant/reflective_sensor.h"
#include "common/tools/Timer.h"

// Bitmask tables
const uint8_t centerPatterns[] = {
    0b00011000,
    0b00111100};

const uint8_t slightLeftPatterns[] = {
    0b01100000,
    0b00110000,
    0b01110000,
    0b0011100,
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

const uint8_t leftTurn[] = {0b11111000, 0b11110000, 0b11111100};

const uint8_t rightTurn[] = {0b00011111, 0b00001111, 0b00111111};

enum LineState {
    CENTER,
    SLIGHT_LEFT,
    SLIGHT_RIGHT,
    HARD_LEFT,
    HARD_RIGHT,
    ALL_WHITE,
    ALL_BLACK,
    LEFT_TURN,
    RIGHT_TURN,
    OTHER
};

/**
 * @name ReflectiveRead
 * @authors Uraib
 * @date 04-12-2025
 * @details Structure to maintain running statistics for reflective sensor readings.
 * @details Tracks the number of readings, the mean, variance (using Welford's algorithm),
 * and the minimum and maximum values observed.
 * @details The update() method incorporates a new sensor reading into the statistics efficiently,
 * updating mean, variance, minimum, and maximum without storing all previous values.
*/

struct ReflectiveRead {

    unsigned long count = 0;                // Number of readings processed
    double mean = 0.0;                      // Current mean of the readings
    double m2 = 0.0;                        // Sum of squares of differences from the current mean 
    int minimum = 1023;                     // Minimum value observed
    int maximum = 0;                        // Maximum value observed

    /**
     * @name update
     * @param x New sensor reading to incorporate
     * @details Updates the running statistics (mean, variance, min, max) with the new value x.
    */

    void update(int x) {
        count = 1;
        double dx = x - mean;

        mean += dx / count;
        double dx2 = x - mean;

        m2 += dx * dx2;

        if (x < minimum) {
            minimum = x;
        }

        if (x > maximum) {
            maximum = x;
        }
    }
};


/**
 * @name ReflectiveSensor
 * @authors Sunny & Vlad
 * @date 08-12-2025
 * @details Class to manage reflective sensors for line detection.
 * @details Handles calibration, reading of surfaces, and comparison to predefined patterns.
 * @details Supports two-surface detection (first and second surface) 
 * and provides bitmask status for black line detection.
*/

class ReflectiveSensor {

private:
    const int *pins;                                // Array of reflective sensor pins
    int pins_rs_length;                             // Number of reflective sensor pins
    float threshold;                                // Threshold for detecting second surface
    int marginError;                                // Margin to ignore small differences in surface detection

    ReflectiveRead *reflectiveReadInit;             // Initial surface data
    ReflectiveRead reflectiveReadBlack[8];          // Calibrated second surface data
    uint8_t blackCalibration;                       // Bitmask of calibrated sensors for black surface
    int blackCalibratedLength = 0;                  // Number of sensors calibrated for black
    bool isBlackCalibrated = false;                 // True if black calibration completed

    ReflectiveRead *currentSensors;                 // Current sensor readings

    /**
     * @name getRSValue
     * @authors Fumbre
     * @date 04-12-2025
     * @details Reads analog values from reflective sensors and updates running statistics.
     * @return Pointer to an array of 8 ReflectiveRead objects containing current statistics.
    */

    ReflectiveRead *getRSValue() {

        ReflectiveRead *stats = new ReflectiveRead[8];

        for (int i = 0; i < PINS_RS_LENGTH; ++i) {
            int v = analogRead(PINS_RS[i]);
            *RS_SEND_DATA_RAW_ARRAY[i] = v;
            stats[i].update(v);
        }
        return stats;
    }

    /**
     * @name calibrationInit
     * @authors Sunny & Vlad
     * @date 10-12-2025
     * @details Performs initial calibration for the first surface 
     * and stores it in reflectiveReadInit.
    */

    void calibrationInit() {
        free(this->reflectiveReadInit);
        this->reflectiveReadInit = getRSValue();
    }

    /**
     * @name calibrationBlack
     * @authors Fumbre
     * @date 10-12-2025
     * @details Performs calibration for the black surface, updating reflectiveReadBlack and calibration status.
    */

    void calibrationBlack() {

        if (this->blackCalibratedLength < this->pins_rs_length) {
            uint8_t reflectiveReadChange = this->getLineDifference(this->reflectiveReadInit, this->threshold);

            for (int i = 0; i < pins_rs_length; i++) {

                if (!(reflectiveReadChange & (128 >> i)) && !(this->blackCalibration & (128 >> i))) {
                    this->reflectiveReadBlack[i].mean = analogRead(PINS_RS[i]);
                    this->blackCalibration |= (128 >> i);
                    this->blackCalibratedLength++;
                }
            }
        } else {
            this->isBlackCalibrated = true;
        }
    }

    /**
     * @name getLineStatusMoreThan
     * @authors Fumbre & Sunny
     * @date 04-12-2025
     * @param compare Pointer to array of ReflectiveRead objects to compare against
     * @param reflectiveDifferenceMargin Margin to ignore small differences
     * @details Compares current sensor readings to 'compare' and returns bitmask status.
     * @return uint8_t Bitmask where 1 indicates current reading >= compare + margin.
    */

    uint8_t getLineStatusMoreThan(ReflectiveRead *compare, int reflectiveDifferenceMargin) {
        uint8_t status = 0;
        free(this->currentSensors);
        this->currentSensors = getRSValue();
        
        for (int i = 0; i < pins_rs_length; i++) {
            if (currentSensors[i].mean + reflectiveDifferenceMargin >= compare[i].mean) {
                status |= (128 >> i);
            } else {
                status &= ~(128 >> i);
            }
        }
        return status;
    }

    /**
     * @name getLineDifference
     * @authors Fumbre & Sunny
     * @date 10-12-2025
     * @param compare Pointer to array of ReflectiveRead objects to compare against
     * @param reflectiveDifference Allowed difference to consider readings equal
     * @details Compares current sensor readings to 'compare' within a tolerance and returns a bitmask.
     * @return uint8_t Bitmask where 1 indicates current reading within difference range of compare.
    */

    uint8_t getLineDifference(ReflectiveRead *compare, int reflectiveDifference) {
        uint8_t status = 0;
        free(this->currentSensors);
        this->currentSensors = getRSValue();
        
        for (int i = 0; i < pins_rs_length; i++) {
            if ((currentSensors[i].mean - reflectiveDifference <= compare[i].mean) &&
                (currentSensors[i].mean + reflectiveDifference >= compare[i].mean)) {
                status |= (128 >> i);
            } else {
                status &= ~(128 >> i);
            }
        }
        return status;
    }

public:
    /**
     * @name ReflectiveSensor
     * @authors Sunny & Vlad
     * @date 08-12-2025
     * @details Constructor for ReflectiveSensor class.
     * @param pins Array of sensor pins
     * @param pins_rs_length Length of pins array
     * @param threshold Threshold for second surface detection
     * @param marginError Margin to ignore minor differences in detection
    */

    ReflectiveSensor(const int *pins, const int pins_rs_length, const float threshold, const int marginError) {
        this->pins = pins;
        this->pins_rs_length = pins_rs_length;
        this->threshold = threshold;
        this->marginError = marginError;
    }

    /**
     * @name setup
     * @authors Sunny & Vlad
     * @date 08-12-2025
     * @details Initializes the reflective sensor pins as INPUT.
    */

    void setup() {
        for (int i = 0; i < pins_rs_length; i++) {
            pinMode(pins[i], INPUT);
        }
    }

    /**
     * @name readBlackLine
     * @authors Fumbre
     * @date 08-12-2025
     * @details Reads the black line using the calibrated second surface.
     * @details If black surface is not fully calibrated, returns 0. Updates RSSendDataStatus.
     * @return uint8_t Bitmask representing current black line status.
    */

    uint8_t readBlackLine() {
        static Timer t;

        if (t.executeOnce(0)) {
            this->calibrationInit();
        }

        this->calibrationBlack();

        if (!this->isBlackCalibrated) {
            return 0;
        }

        uint8_t currentBlackStatus = this->getLineStatusMoreThan(this->reflectiveReadBlack, this->marginError);
        String statusStr = "";

        for (int i = 7; i >= 0; i--) {
            statusStr += (currentBlackStatus & (1 << i)) ? '1' : '0';
        }

        RSSendDataStatus = statusStr;
        return currentBlackStatus;
    }

    /**
     * @name match
     * @authors Aria & Fumbre
     * @date 12-12-2025
     * @param patterns Array of patterns to match
     * @param elementCount Length of the patterns array
     * @details Compares current black line status against a list of patterns.
     * @return bool True if any pattern matches, otherwise false
    */

    bool match(const uint8_t *patterns, int elementCount) {

        for (int i = 0; i < elementCount; i++) {

            if (this->readBlackLine() == patterns[i]) {
                return true;
            }
        }
        return false;
    }

    /**
     * @name pattern
     * @authors Aria
     * @date 12-12-2025
     * @details Determines the line state based on current black line pattern.
     * @return LineState Enum indicating position (CENTER, SLIGHT_LEFT, SLIGHT_RIGHT, etc.)
    */

    LineState pattern() {
        if (match(centerPatterns, ARRAY_SIZE(centerPatterns))) return CENTER;
        if (match(slightLeftPatterns, ARRAY_SIZE(slightLeftPatterns))) return SLIGHT_LEFT;
        if (match(slightRightPatterns, ARRAY_SIZE(slightRightPatterns))) return SLIGHT_RIGHT;
        if (match(hardLeftPatterns, ARRAY_SIZE(hardLeftPatterns))) return HARD_LEFT;
        if (match(hardRightPatterns, ARRAY_SIZE(hardRightPatterns))) return HARD_RIGHT;
        if (match(leftTurn, ARRAY_SIZE(leftTurn))) return LEFT_TURN;
        if (match(rightTurn, ARRAY_SIZE(rightTurn))) return RIGHT_TURN;
        if (match(allWhite, ARRAY_SIZE(allWhite))) return ALL_WHITE;
        if (match(allBlack, ARRAY_SIZE(allBlack))) return ALL_BLACK;
        return OTHER;
    }
};
