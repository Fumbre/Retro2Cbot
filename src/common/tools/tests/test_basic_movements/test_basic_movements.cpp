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
//   ROTATE_LEFT_CHECK,
//   DONE
// };

// BasicMovementState currentState = MOVE_FORWARD;
// Timer stateTimer;

// void testBasicMovement() {

//   switch (currentState) {

//     case MOVE_FORWARD:
//       moveStabilized(240, 240);

//       if (stateTimer.executeOnce(3000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = MOVE_BACKWARD;
//       }
//       break;

//     case MOVE_BACKWARD:
//       moveStabilized(-240, -240);

//       if (stateTimer.executeOnce(3000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = MOVE_FORWARD_SHORT;
//       }
//       break;

//     case MOVE_FORWARD_SHORT:
//       moveStabilized(240, 240);

//       if (stateTimer.executeOnce(500)) {
//         stateTimer.resetExecuteOnce();
//         currentState = TURN_RIGHT_1;
//       }
//       break;

//     case TURN_RIGHT_1:
//       moveStabilized(240, 120);

//       if (stateTimer.executeOnce(1000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = TURN_RIGHT_2;
//       }
//       break;

//     case TURN_RIGHT_2:
//       moveStabilized(240, 130);

//       if (stateTimer.executeOnce(1000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = TURN_LEFT_1;
//       }
//       break;

//     case TURN_LEFT_1:
//       moveStabilized(120, 240);

//       if (stateTimer.executeOnce(300)) {
//         stateTimer.resetExecuteOnce();
//         currentState = TURN_LEFT_2;
//       }
//       break;

//     case TURN_LEFT_2:
//       moveStabilized(125, 240);

//       if (stateTimer.executeOnce(300)) {
//         stateTimer.resetExecuteOnce();
//         currentState = MOVE_FORWARD_LONG;
//       }
//       break;

//     case MOVE_FORWARD_LONG:
//       moveStabilized(240, 240);

//       if (stateTimer.executeOnce(2000)) {
//         stateTimer.resetExecuteOnce();
//         currentState = ROTATE_LEFT_CHECK;
//       }
//       break;

//     case ROTATE_LEFT_CHECK:

//       if (didMoveLeft(255, 22)) {
//         moveStopAll();
//         currentState = DONE;
//       }
//       break;

//     case DONE:
//       break;
//   }
// }
