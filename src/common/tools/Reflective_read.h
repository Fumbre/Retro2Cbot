/**
 * @name Welford
 * @author Sunny
 * @date 30-11-2025
 * @details Welford is an algorithm, which can caculate avgerage value and variance.
 * This algorithm can monitoring data changing immediately. It can used in big data,
 * streaming data processing and real-time monitoring and alarm system
 */
#pragma once
#include <math.h>
struct SampleData
{
    float *data;
    int dataLength;
};

class ReflectiveRead
{
private:
    unsigned long count; // sample count
    float avg;           // avgerage number of sample count
    float M2;            // square difference

public:
    /**
     * @name Constructor function
     * @author Sunny
     * @date 30-11-2025
     */
    ReflectiveRead()
    {
        this->count = 0;
        this->avg = 0;
        this->M2 = 0;
    }
    /**
     * @name update
     * @author Sunny
     * @date 30-11-2025
     * @details update squared difference
     */
    void update(float value)
    {
        // update count
        count++;
        // caculate the difference between value and old avgerage number
        float delta = value - avg;
        // update average number
        avg += delta / (float)count;
        // caculate the difference between value and new average number
        float delta2 = value - avg;
        // update squared differnce (M2)
        M2 += (delta * delta2);
    }

    /**
     * @name update
     * @author Sunny
     * @date 30-11-2025
     * @details update squared difference
     * @return SampleData
     */
    void update(SampleData data)
    {
        int length = data.dataLength;
        float *value = data.data;
        for (int i = 0; i < length; i++)
        {
            update(value[i]);
        }
    }

    /**
     * @name getCurrentCount
     * @author Sunny
     * @date 30-11-2025
     */
    int getCurrentCount()
    {
        return count;
    }

    /**
     * @name getCurrrentAvgerageNumber
     * @author Sunny
     * @date 30-11-2025
     * @return avgerage value
     */
    float getCurrrentAvgerageNumber()
    {
        return avg;
    }

    /**
     * @name getSampleVariance
     * @author Sunny
     * @date 30-11-2025
     * @return sample variance
     */
    float getSampleVariance()
    {
        return (count < 2) ? 0.0f : (M2 / (float)(count - 1));
    }

    /**
     * @name getSampleVariance
     * @author Sunny
     * @date 30-11-2025
     * @return population variance
     */
    float getPopulationVariance()
    {
        return (count < 2) ? 0.0f : (M2 / (float)count);
    }

    /**
     * @name getStandardDeviation
     * @author Sunny
     * @date 30-11-2025
     * @return Standard Deviation
     */
    float getStandardDeviation()
    {
        return (count < 2) ? 0.0f : sqrt((M2 / (float)count));
    }

    /**
     * @name reset
     * @author Sunny
     * @date 30-11-2025
     */
    void reset()
    {
        this->count = 0;
        this->avg = 0;
        this->M2 = 0;
    }
};