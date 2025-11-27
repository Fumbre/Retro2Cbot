/**
 * @name PID class
 * @author Sunny
 * @date 27-11-2025
 */

class PID
{
private:
  float kp;            // Proportional factor
  float ki;            // Integral factor
  float kd;            // Derivative factor
  float lastError = 0; // error in last time

public:
  float integral = 0; // record total error
  /**
   * @name PID
   * @name Sunny
   * @date 27-11-2025
   * @details constructure functions of PID
   * @param kp Proportional factor
   * @param ki Integral factor
   * @param kd Derivative factor
   */
  PID(float kp, float ki, float kd)
  {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
  }

  /**
   * @name caculateCorrection
   * @author Sunny
   * @date 27-11-2025
   * @param v1 first value
   * @param v2 second value
   * @return correction
   */
  float caculateCorrection(float v1, float v2)
  {
    // caculate error
    float error = v1 - v2;
    // plus error to integeral
    integral += error;
    // caculate derivative
    float derivative = (error - lastError);
    // caculate correction
    float correction = kp * error + ki * integral + kd * derivative;
    return correction;
  }
};