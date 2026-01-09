#include "datasend.h"

int interval = 2000;
String type = "o";

Timer timer;

void dataSend()
{
    // sendGripperData();
    // sendNeopixelData();
    // sendPulsesData();
    sendReflectiveSensorData();
    // sendSonarData();
}

// void sendSonarData()
// {
//     if (timer.interval(interval))
//     {
//         doc.clear();
//         String robotCode = getCurrentRobotCode();
//         setBasicInformation(doc);
//         doc["e"] = "so";
//         doc["rc"] = robotCode;
//         JsonArray data = doc.createNestedArray("d");
// #ifdef BB011
//         JsonObject leftSonar = data.createNestedObject();
//         leftSonar["sd"] = sonarSendDataLeftDistance;
//         leftSonar["d"] = "2";
//         JsonObject rightSonar = data.createNestedObject();
//         rightSonar["sd"] = sonarSendDataRightDistance;
//         rightSonar["d"] = "1";
// #endif
//         JsonObject frontSonar = data.createNestedObject();
//         frontSonar["sd"] = sonarSendDatafrontDistance;
//         frontSonar["d"] = "0";
//         serializeJson(doc, buffer);
//         Serial.println(buffer);
//         sendDataFromHC12(buffer);
//     }
// }
// void sendGripperData()
// {
//     if (timer.timeout(interval))
//     {
//         doc.clear();
//         doc["e"] = "g";
//         setBasicInformation(doc);
//         JsonObject gripper = doc.createNestedObject("d");
//         gripper["rc"] = getCurrentRobotCode();
//         gripper["g"] = gripperStatus;
//         serializeJson(doc, buffer);
//         sendDataFromHC12(buffer);
//         Serial.println(buffer);
//         timer.resetTimeout();
//     }
// }

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
        Serial.println(msg); 
        sendDataFromHC12(msg);
        timer.resetExecuteOnce();
    }
}

// void sendNeopixelData()
// {
//     if (timer.interval(interval))
//     {
//         String robotCode = getCurrentRobotCode();
//         for (int i = 0; i < 4; i++)
//         {
//             doc.clear();
//             doc["e"] = "n";
//             setBasicInformation(doc);
//             JsonArray data = doc.createNestedArray("d");
//             JsonObject neopxiel = data.createNestedObject();
//             neopxiel["rc"] = robotCode;
//             neopxiel["n"] = i;
//             neopxiel["r"] = colorArray[i][0];
//             neopxiel["g"] = colorArray[i][1];
//             neopxiel["b"] = colorArray[i][2];
//             serializeJson(doc, buffer, sizeof(buffer));
//             Serial.println(buffer);
//             sendDataFromHC12(buffer);
//         }
//         timer.resetInterval();
//     }
// }
// void sendPulsesData()
// {
//     if (timer.timeout(interval))
//     {
//         doc.clear();
//         doc["e"] = "pu";
//         setBasicInformation(doc);
//         JsonObject data = doc.createNestedObject("d");
//         doc["rc"] = getCurrentRobotCode();
//         data["l"] = motor_left_pulses_counter;
//         data["r"] = motor_right_pulses_counter;
//         serializeJson(doc, buffer);
//         Serial.println(buffer);
//         sendDataFromHC12(buffer);
//         timer.resetTimeout();
//     }
// }

// void setBasicInformation(JsonDocument &doc)
// {
//     doc["t"] = type;
// }

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