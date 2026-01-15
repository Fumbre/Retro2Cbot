#include "datasend.h"

int interval = 2000;
String type = "o";

Timer timer;
Timer timer2;

void dataSend()
{
    sendGripperData();
    sendNeopixelData();
    sendReflectiveSensorData();
    sendSonarData();
}

void sendSonarData()
{
    if (timer.interval(interval))
    {
        String robotCode = getCurrentRobotCode();
        String msg = "o,so,";

        msg += (robotCode + ",");
        msg += "0,";
        msg += sonarSendDatafrontDistance;
        msg += ",1,";
        msg += sonarSendDataRightDistance;
        msg += ",2,";
        msg += sonarSendDataLeftDistance;

        // Serial.println(msg);
        sendDataFromHC12(msg);

        timer.resetInterval();
    }
}
void sendGripperData()
{
    if (timer2.interval(interval))
    {
        String robotCode = getCurrentRobotCode();
        String msg = "o,g,";
        msg += (robotCode + ",");
        msg += (gripperStatus ? "1" : "0");
        // Serial.println(msg);
        sendDataFromHC12(msg);
    }
}

void sendReflectiveSensorData()
{
    if (timer.executeOnce(interval))
    {
        String msg = "o,rs,";
        msg += getCurrentRobotCode();
        for (int i = 0; i < 8; i++)
        {
            msg += ",";
            msg += *RS_SEND_DATA_RAW_ARRAY[i];
        }
        msg += ",";
        msg += RSSendDataStatus;
        // Serial.println(msg);
        sendDataFromHC12(msg);
        timer.resetExecuteOnce();
    }
}

void sendNeopixelData()
{
    if (timer.timeout(interval))
    {
        String robotCode = getCurrentRobotCode();
        String msg = "o,n,";
        msg += (robotCode + ",");
        for (int i = 0; i < 4; i++)
        {
            msg += i;
            msg += ",";
            for (int j = 0; j < 3; j++)
            {
                msg += colorArray[i][j];
                if (i != 3 || j != 2)
                {
                    msg += ",";
                }
            }
        }
        // Serial.println(msg);

        sendDataFromHC12(msg);
        timer.resetTimeout();
    }
}

String getCurrentRobotCode()
{
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