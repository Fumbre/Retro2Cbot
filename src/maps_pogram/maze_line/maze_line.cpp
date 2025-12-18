// #include "maze_line.h"

// // RS - reflective sensor
// ReflectiveSensor rsMaze(PINS_RS, PINS_RS_LENGTH, THRESHOLD, MARGIN_SURFACE);

// float slightConf = 0.8;
// float hardConf = 0;
// bool isRotating = false;
// void mazeLineSetup()
// {
//     setupMotor();
//     rsMaze.setup();
// }

// LineState prevStatus = CENTER;

// void mazeLine(int speed)
// {
//     // LineState currentLineStatus = isRotating ? prevStatus : rsMaze.pattern();
//     LineState currentLineStatus = rsMaze.pattern();
//     if (isRotating)
//     {
//         if (currentLineStatus != ALL_WHITE)
//         {
//             isRotating = false;
//         }
//         else
//         {
//             currentLineStatus = prevStatus;
//         }
//     }
//     int pwmValue = getPWMValue(speed);
//     switch (currentLineStatus)
//     {
//     case CENTER:
//         moveSpeed(pwmValue, pwmValue);
//         Serial.println("CENTER");
//         break;
//     case SLIGHT_LEFT:
//         moveSpeed(pwmValue * slightConf, pwmValue);
//         Serial.println("SLIGHT_LEFT");
//         break;
//     case SLIGHT_RIGHT:
//         moveSpeed(pwmValue, pwmValue * slightConf);
//         Serial.println("SLIGHT_RIGHT");
//         break;
//     case LEFT_TURN:
//         moveSpeed(pwmValue * hardConf, pwmValue);
//         isRotating = true;
//         prevStatus = LEFT_TURN;
//         Serial.println("LEFT_TURN");
//         break;
//     case RIGHT_TURN:
//         moveSpeed(pwmValue, pwmValue * hardConf);
//         isRotating = true;
//         prevStatus = RIGHT_TURN;
//         Serial.println("RIGHT_TURN");
//         break;
//     case ALL_WHITE:
//         isRotating = !didMoveRight(pwmValue, PPR / 2);
//         isRotating ? (prevStatus = currentLineStatus) : resetMoveRight();
//         Serial.println("ALL_WHITE");
//         break;
//     case ALL_BLACK:
//         moveSpeed(pwmValue, pwmValue * hardConf);
//         isRotating = true;
//         prevStatus = ALL_WHITE;
//         Serial.println("ALL_BLACK");
//         break;
//     }
// }

// int getPWMValue(int speed)
// {
//     speed = constrain(speed, 0, FULL_SPEED);
//     int pwmValue = (float)speed / FULL_SPEED * FULL_PWM_VALUE;
//     return constrain(pwmValue, 0, FULL_PWM_VALUE);
// }