// #include "test_basic_movements.h"

// enum BasicMovementState {
//   MOVE_FORWARD,
//   MOVE_BACKWARD,
//   MOVE_FORWARD_SHORT,
//   TURN_RIGHT_1,
//   TURN_RIGHT_2,
//   TURN_LEFT_1,
//   TURN_LEFT_2,
//   MOVE_FORWARD_LONG,
//   ROTATE_LEFT,
//   STOP,
//   DONE
// };

// BasicMovementState currentState = MOVE_FORWARD;
// Timer stateTimer;

// void testBasicMovementAvoidence() {
//   switch (currentState) {
//     case MOVE_FORWARD:
//       moveSpeed(240, 240);

//       if (stateTimer.executeOnce(3000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = MOVE_BACKWARD;
//       }
//       break;

//     case MOVE_BACKWARD:
//       moveSpeed(-240, -240);

//       if (stateTimer.executeOnce(3000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = MOVE_FORWARD_SHORT;
//       }
//       break;

//     case MOVE_FORWARD_SHORT:
//       moveSpeed(240, 240);

//       if (stateTimer.executeOnce(500)) {
//         stateTimer.resetExecuteOnce();
//         currentState = TURN_RIGHT_1;
//       }
//       break;

//     case TURN_RIGHT_1:
//       switchDirection(240, 140);

//       if (stateTimer.executeOnce(1000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = TURN_RIGHT_2;
//       }
//       break;

//     case TURN_RIGHT_2:
//       switchDirection(240, 150);

//       if (stateTimer.executeOnce(1000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = TURN_LEFT_1;
//       }
//       break;

//     case TURN_LEFT_1:
//       switchDirection(140, 240);

//       if (stateTimer.executeOnce(300)) {
//         stateTimer.resetExecuteOnce();
//         currentState = TURN_LEFT_2;
//       }
//       break;

//     case TURN_LEFT_2:
//       switchDirection(150, 240);

//       if (stateTimer.executeOnce(300)) {
//         stateTimer.resetExecuteOnce();
//         currentState = MOVE_FORWARD_LONG;
//       }
//       break;

//     case MOVE_FORWARD_LONG:
//       moveSpeed(240, 240);

//       if (stateTimer.executeOnce(2000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = ROTATE_LEFT;
//       }
//       break;

//     case ROTATE_LEFT:
//       moveSpeed(240, -240);

//       if (stateTimer.executeOnce(1300)) {
//         stateTimer.resetExecuteOnce();
//         currentState = STOP;
//       }
//       break;

//     case STOP:
//       stopMotors();
//       currentState = DONE;
//       break;

//     case DONE:
//       break;
//   }
// }
