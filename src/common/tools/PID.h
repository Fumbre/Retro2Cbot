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
  float integral_limit = 100.0; // integral limitation
  float output_limit = 255.0; //correction limitation


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
   * @param integral_limit integral limitation
   * @param output_limit output limitation 
   */
  PID(float kp, float ki, float kd, float integral_limit, float output_limit)
  {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->integral_limit = integral_limit;
    this->output_limit = output_limit;
  }

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

  // TODO calculate not caculate
  float caculateCorrection(float v1, float v2)
  {
    // caculate error
    float error = v1 - v2;
    // plus error to integeral
    integral += error;
    integral =  constrain(integral,-fabs(integral_limit),fabs(integral_limit));
    // caculate derivative
    float derivative = (error - lastError);
    // caculate correction
    float correction = kp * error + ki * integral + kd * derivative;
    correction =  constrain(correction,-fabs(output_limit),fabs(output_limit));
    //update last error
    lastError = error;
    return correction;
  }
};