#include "lineMazeLogic.h"
#include "common/tools/Timer.h"

bool huj = false;


MazeLogic::MazeLogic(TurnPreference pref)
    : pref(pref),
      robotState(FOLLOW_LINE),
      lastStableState(CENTER),
      pendingFollowState(CENTER),
      pendingFollowCount(0)
{}

MazeMove MazeLogic::decide(LineState state) {

    static Timer t;

    if (huj){
        if (!t.timeout(80)) {
            return TURN_RIGHT;
        } else  {
            huj = false;
        }
    }


    switch (robotState) {

        // ================= FOLLOW LINE =================
        case FOLLOW_LINE:

        if (state == CENTER || state == ALL_BLACK ||
            state == LEFT_TURN || state == RIGHT_TURN) {

            if (state == pendingFollowState) {
                pendingFollowCount++;
            } else {
                pendingFollowState = state;
                pendingFollowCount = 0;
            }

            if (pendingFollowCount >= FOLLOW_CONFIRM_COUNT) {
                lastStableState = state;
                pendingFollowCount = FOLLOW_CONFIRM_COUNT;
            }
        }

        if (state == ALL_WHITE) {

            robotState = TURNING;

            if (lastStableState == RIGHT_TURN) {
                return TURN_RIGHT;
            }

            if (lastStableState == LEFT_TURN) {
                return TURN_LEFT;
            }

            if (lastStableState == ALL_BLACK) {
                return (pref == RIGHT_FIRST) ? TURN_RIGHT : TURN_LEFT;
            }
            
            return TURN_RIGHT;
        }

        // --- Normal line following ---
        //if (state == TEST_PATTERN && pref == RIGHT_FIRST) return TURN_RIGHT;
        //if (state == TEST_PATTERN && pref == LEFT_FIRST)  return TURN_LEFT;
        if (state == SLIGHT_LEFT)                         return SOFT_LEFT;
        if (state == SLIGHT_RIGHT)                        return SOFT_RIGHT;
        if (state == HARD_LEFT)                           return TURN_LEFT;
        if (state == HARD_RIGHT)                          return TURN_RIGHT;
        if (state == RIGHT_TURN && pref == RIGHT_FIRST)    {
            huj = true;
            t.resetTimeout();
            return TURN_RIGHT;
        };
        if (state == LEFT_TURN && pref == LEFT_FIRST)     return TURN_LEFT;
        return GO_FORWARD;

    // ================= UTURNING =================
    case UTURNING:

        if (state == CENTER) {
            robotState = FOLLOW_LINE;
            return GO_FORWARD;
        }
        return NO_ACTION;

    // ================= TURNING =================
    case TURNING:

        if (state == CENTER) {
            robotState = FOLLOW_LINE;
            return GO_FORWARD;
        }
        return NO_ACTION;
    }

    return NO_ACTION;
}
