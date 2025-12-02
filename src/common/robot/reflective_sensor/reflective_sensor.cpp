#include "reflective_sensor.h"

Welford welford;
float sensorValue[PINS_RS_LENGTH];
bool isLine[PINS_RS_LENGTH];
unsigned long last_left_pulses = 0;
unsigned long last_right_pulses = 0;

PID linePID(0.75, 0.02, 0.02, 100, fabs(FULL_PWM_VALUE));
Timer check;

void initReflectiveSensorPins()
{
    for (int i = 0; i < PINS_RS_LENGTH; i++)
    {
        pinMode(PINS_RS[i], INPUT);
    }
}

WheelSpeed checkLine(int baseSpeed)
{ // set variables
    int blackLineCount = 0;
    float weightedSum = 0;
    // get current reflective sensor value
    for (int i = 0; i < PINS_RS_LENGTH; i++)
    {
        // read current value from line sensor
        float value = analogRead(PINS_RS[i]);
        // put value into sensorValue
        sensorValue[i] = value;
        // caculating thresold
        welford.update(value);
    }
    // get global thresold
    float thresold = welford.getCurrrentAvgerageNumber() - welford.getStandardDeviation();
    // reset properties in Welford
    welford.reset();
    // check black line
    for (int i = 0; i < PINS_RS_LENGTH; i++)
    {
        isLine[i] = sensorValue[i] < thresold ? true : false;
    }
    // get base pwm value
    float basePwmValue = getPWMvalue(baseSpeed);
    // caculate error
    for (int i = 0; i < PINS_RS_LENGTH; i++)
    {
        if (isLine[i])
        {
            blackLineCount++;
            weightedSum += WEIGHT[i] * fabs(WEIGHT[i]);
        }
    }
    float error = (blackLineCount) > 0 ? (weightedSum / (float)blackLineCount) : 0;
    float maxCorrection = baseSpeed / 3.0 + fabs(error) * (baseSpeed / 2.0);
    // according to proportion, error should be converted to pwm value
    error = error / WEIGHT[PINS_RS_LENGTH - 1] * maxCorrection;
    // get line correction
    float lineCorrection = linePID.caculateCorrection(0, error);
    // get left and right targeted pwm value
    float pwmCorrection = constrain(lineCorrection, -maxCorrection, maxCorrection);
    float leftTargetPwmValue = basePwmValue - pwmCorrection;
    float rightTargetPwmValue = basePwmValue + pwmCorrection;
    if (check.interval(500))
    {
        Serial.print("left speed: ");
        Serial.println(leftTargetPwmValue);
        Serial.print("right speed: ");
        Serial.println(rightTargetPwmValue);
    }
    WheelSpeed speed;
    speed.leftPWM = leftTargetPwmValue;
    speed.rightPWM = rightTargetPwmValue;
    return speed;
}
