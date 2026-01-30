#include "datasend.h"

int interval = 2000;
String type = "o";

Timer timer;
Timer timer2;

/**
 * @name dataSend
 * @author Sunny
 * @date 10-12-2025
 * @details Calls all the data sending functions sequentially:
 *  - sendGripperData()
 *  - sendNeopixelData()
 *  - sendReflectiveSensorData()
 *  - sendSonarData()
*/

void dataSend() {
    sendGripperData();
    sendNeopixelData();
    sendReflectiveSensorData();
    sendSonarData();
}

/**
 * @name sendSonarData
 * @author Sunny
 * @date 10-12-2025
 * @details Sends sonar sensor data (front, right, left) via HC12 every 'interval' milliseconds.
 * @details Builds a message: "o,so,<robotCode>,0,<frontDistance>,1,<rightDistance>,2,<leftDistance>"
 * @details Resets the timer after sending.
*/

void sendSonarData() {
    if (timer.interval(interval)) {
        String robotCode = getCurrentRobotCode();
        String msg = "o,so,";

        msg += (robotCode + ",");
        msg += "0,";
        msg += sonarSendDatafrontDistance;
        msg += ",1,";
        msg += sonarSendDataRightDistance;
        msg += ",2,";
        msg += sonarSendDataLeftDistance;

        sendDataFromHC12(msg);

        timer.resetInterval();
    }
}

/**
 * @name sendGripperData
 * @author Sunny
 * @date 10-12-2025
 * @details Sends the gripper status via HC12 every 'interval' milliseconds.
 * @details Builds a message: "o,g,<robotCode>,<gripperStatus>"
 * @details gripperStatus is 1 if true (closed), 0 if false (open).
*/

void sendGripperData() {
    if (timer2.interval(interval)) {
        String robotCode = getCurrentRobotCode();
        String msg = "o,g,";
        msg += (robotCode + ",");
        msg += (gripperStatus ? "1" : "0");
        sendDataFromHC12(msg);
    }
}

/**
 * @name sendReflectiveSensorData
 * @author Sunny
 * @date 10-12-2025
 * @details Sends reflective sensor data once every 'interval' milliseconds using executeOnce().
 * @details Builds a message: "o,rs,<robotCode>,<sensor0>,...,<sensor7>,<status>"
 * @details Resets executeOnce timer after sending.
*/

void sendReflectiveSensorData()
{
    if (timer.executeOnce(interval)) {
        String msg = "o,rs,";
        msg += getCurrentRobotCode();

        for (int i = 0; i < 8; i++) {
            msg += ",";
            msg += *RS_SEND_DATA_RAW_ARRAY[i];
        }

        msg += ",";
        msg += RSSendDataStatus;
        sendDataFromHC12(msg);
        timer.resetExecuteOnce();
    }
}

/**
 * @name sendNeopixelData
 * @author Sunny
 * @date 10-12-2025
 * @details Sends Neopixel LED color data every 'interval' milliseconds via HC12.
 * @details Builds a message: "o,n,<robotCode>,<led0,r,g,b>,...,<led3,r,g,b>"
 * @details Resets the timeout timer after sending.
*/

void sendNeopixelData() {
    if (timer.timeout(interval)) {
        String robotCode = getCurrentRobotCode();
        String msg = "o,n,";
        msg += (robotCode + ",");

        for (int i = 0; i < 4; i++) {
            msg += i;
            msg += ",";

            for (int j = 0; j < 3; j++) {
                msg += colorArray[i][j];

                if (i != 3 || j != 2) {
                    msg += ",";
                }
            }
        }

        sendDataFromHC12(msg);
        timer.resetTimeout();
    }
}

/**
 * @name getCurrentRobotCode
 * @author Sunny
 * @date 10-12-2025
 * @details Returns the current robot code depending on preprocessor definitions:
 *  - BB046, BB011, or BB016
 * @return String with the robot code
*/

String getCurrentRobotCode() {
    String robotCode = "";
#ifdef BB046
    robotCode = BB046;
#endif
#ifdef BB011
    robotCode = BB011;
#endif
#ifdef BB016
    robotCode = BB016;
#endif
    return robotCode;
}
