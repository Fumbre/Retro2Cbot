// #include "movement.h"

// void moveForward(int speed)
// {
//   for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
//   {
//     analogWrite(PINS_MOTOR[i], 0);
//     if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_FORWARD)
//       analogWrite(PIN_MOTOR_RIGHT_FORWARD, 255);
//     if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_FORWARD)
//       analogWrite(PIN_MOTOR_LEFT_FORWARD, 255);
//   }
// };

// void moveBackward(int speed)
// {
//   for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
//   {
//     analogWrite(PINS_MOTOR[i], 0);
//     if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_BACKWARD)
//       analogWrite(PIN_MOTOR_LEFT_BACKWARD, speed);
//     if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_BACKWARD)
//       analogWrite(PIN_MOTOR_RIGHT_BACKWARD, speed);
//   }
// };

// void moveRight(int speed) {

// };

// void moveLeft(int speed) {

// };

// void rotateLeft(int speed)
// {
//   for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
//   {
//     analogWrite(PINS_MOTOR[i], 0);
//     if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_BACKWARD)
//       analogWrite(PIN_MOTOR_LEFT_BACKWARD, speed);
//     if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_FORWARD)
//       analogWrite(PIN_MOTOR_RIGHT_FORWARD, speed);
//   }
// };

// void rotateRight(int speed)
// {
//   for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
//   {
//     analogWrite(PINS_MOTOR[i], 0);
//     if (PINS_MOTOR[i] == PIN_MOTOR_RIGHT_BACKWARD)
//       analogWrite(PIN_MOTOR_RIGHT_BACKWARD, speed);
//     if (PINS_MOTOR[i] == PIN_MOTOR_LEFT_FORWARD)
//       analogWrite(PIN_MOTOR_LEFT_FORWARD, speed);
//   }
// };

// void moveStop(int motor_pin) { digitalWrite(motor_pin, 0); };

// void moveStopAll()
// {
//   for (int i = 0; i < PINS_MOTOR_LENGTH; i++)
//   {
//     digitalWrite(PINS_MOTOR[i], 0);
//   }
// };

// // == == == == == == == = MAIN TESTS == == == == == == == =

// // ------------some test------------------

// // if (sadness.executeOnce(0))
// // {
// //   moveForward(100);
// // }

// // if (sadness1.executeOnce(2000))
// // {
// //   // rotate(100, "left", 180);
// //   // rotate(100, "right", 180);
// //   sadness.resetExecuteOnce();
// //   sadness1.resetExecuteOnce();

// //   // stopMotors();
// // }

// // ------------first test------------------
// // if (stampForward.interval(1000, 1500))
// // {
// //   moveBackward(255);
// // }
// // else
// // {
// //   moveForward(255);
// // }

// // ------------second test------------------
// // if (stampForward.interval(4500))
// // {
// //   stampForward.hardReset();
// //   stampBackward.hardReset();
// //   stampRotateLeft.hardReset();
// // }

// // if (stampForward.executeOnce(0))
// // {
// //   moveForward(255);
// // }

// // if (stampBackward.executeOnce(1000))
// // {
// //   moveBackward(255);
// // }

// // if (stampRotateLeft.executeOnce(2000))
// // {
// //   rotateLeft(255);
// // }

// // if (stampRotateLeft.executeOnce(3500))
// // {
// //   rotateRight(255);
// // }

// // ------------three test------------------

// // if (!doCoolRotation.timeout(32000))
// // {
// //   if (test.interval(25))
// //   {

// //     if (stampRotateLeft.interval(20, 20))
// //     {
// //       rotateLeft(250);
// //     }
// //     else
// //     {
// //       rotateRight(255);
// //     }
// //     moveBackward(255);
// //   }
// // }

// // if (doCoolRotation.executeOnce(32000))
// // {
// //   stopMotors();
// // }

// // ------------four test------------------

// // if (!doCoolRotation.timeout(32000))
// // {
// //   // if (test.interval(20))
// //   // {
// //   if (test.executeOnce(0))
// //   {
// //     moveForward(255);
// //   }
// //   if (stampRotateLeft.interval(25, 15))
// //   {
// //     analogWrite(PIN_MOTOR_LEFT_BACKWARD, 0);
// //     // rotateLeft(255);
// //   }
// //   // else
// //   // {
// //   //   // rotateRight(255);
// //   // }
// //   moveForward(255);
// //   // }
// // }

// // if (doCoolRotation.executeOnce(32000))
// // {
// //   moveStopAll();
// // }
