#include "datasend.h"

int interval = 1000;
String type = "outside";
String method = "POST";

void dataSend()
{
    sendGripperData();
    sendNeopixelData();
    sendPulsesData();
    sendReflectiveSensorData();
    sendSonarData();
}

void sendSonarData()
{
    static Timer timer;
    static JsonDocument doc;
    if (timer.intervalStart(interval))
    {
        String robotCode = getCurrentRobotCode();
        setBasicInformation(doc);
        doc["event"] = "sonar";
        JsonArray data = doc.createNestedArray("data");
#ifdef BB011
        JsonObject leftSonar = data.createNestedObject();
        leftSonar["sonarDistance"] = sonarSendDataLeftDistance;
        leftSonar["direction"] = "2";
        leftSonar["robotCode"] = robotCode;
        JsonObject rightSonar = data.createNestedObject();
        rightSonar["sonarDistance"] = sonarSendDataRightDistance;
        rightSonar["direction"] = "1";
        rightSonar["robotCode"] = robotCode;
#endif
        JsonObject frontSonar = data.createNestedObject();
        frontSonar["sonarDistance"] = sonarSendDatafrontDistance;
        frontSonar["direction"] = "0";
        frontSonar["robotCode"] = robotCode;
        char buffer[256];
        serializeJson(doc, buffer);
        sendDataFromHC12(buffer);
    }
}
void sendGripperData()
{
    static Timer timer;
    static JsonDocument doc;
    if (timer.interval(interval))
    {
        doc["event"] = "gripper";
        setBasicInformation(doc);
        JsonArray data = doc.createNestedArray("data");
        JsonObject gripper = data.createNestedObject();
        gripper["robotCode"] = getCurrentRobotCode();
        gripper["gripperStatus"] = gripperStatus;
        char buffer[256];
        serializeJson(doc, buffer);
        sendDataFromHC12(buffer);
    }
}
void sendReflectiveSensorData()
{
    static Timer timer;
    static JsonDocument doc;
    if (timer.intervalStart(interval))
    {
        doc["event"] = "rs";
        setBasicInformation(doc);
        JsonArray data = doc.createNestedArray("data");
        JsonObject rs = data.createNestedObject();
        rs["robotCode"] = getCurrentRobotCode();
        rs["a0"] = a0;
        rs["a1"] = a1;
        rs["a2"] = a2;
        rs["a3"] = a3;
        rs["a4"] = a4;
        rs["a5"] = a5;
        rs["a6"] = a6;
        rs["a7"] = a7;
        rs["currentStatus"] = RSSendDataStatus;
        char buffer[256];
        serializeJson(doc, buffer);
        sendDataFromHC12(buffer);
    }
}
void sendNeopixelData()
{
    static Timer timer;
    static JsonDocument doc;
    if (timer.intervalStart(interval))
    {
        String robotCode = getCurrentRobotCode();
        doc["event"] = "neopixels";
        setBasicInformation(doc);
        JsonArray data = doc.createNestedArray("data");
        JsonObject neopxiels0 = data.createNestedObject();
        neopxiels0["robotCode"] = robotCode;
        neopxiels0["neopixelIndex"] = "0";
        neopxiels0["r"] = Red0;
        neopxiels0["g"] = Green0;
        neopxiels0["b"] = Blue0;
        JsonObject neopxiels1 = data.createNestedObject();
        neopxiels1["robotCode"] = robotCode;
        neopxiels1["neopixelIndex"] = "1";
        neopxiels1["r"] = Red1;
        neopxiels1["g"] = Green1;
        neopxiels1["b"] = Blue1;
        JsonObject neopxiels2 = data.createNestedObject();
        neopxiels2["robotCode"] = robotCode;
        neopxiels2["neopixelIndex"] = "2";
        neopxiels2["r"] = Red2;
        neopxiels2["g"] = Green2;
        neopxiels2["b"] = Blue2;
        JsonObject neopxiels3 = data.createNestedObject();
        neopxiels3["robotCode"] = robotCode;
        neopxiels3["neopixelIndex"] = "3";
        neopxiels3["r"] = Red3;
        neopxiels3["g"] = Green3;
        neopxiels3["b"] = Blue3;
        char buffer[256];
        serializeJson(doc, buffer);
        sendDataFromHC12(buffer);
    }
}
void sendPulsesData()
{
    static Timer timer;
    static JsonDocument doc;
    if (timer.intervalStart(interval))
    {
        doc["event"] = "pulses";
        setBasicInformation(doc);
        JsonArray data = doc.createNestedArray("data");
        JsonObject pulses = data.createNestedObject();
        pulses["robotCode"] = getCurrentRobotCode();
        pulses["leftWheelPulses"] = motor_left_pulses_counter;
        pulses["rightWheelPulses"] = motor_right_pulses_counter;
        char buffer[256];
        serializeJson(doc, buffer);
        sendDataFromHC12(buffer);
    }
}

void setBasicInformation(JsonDocument &doc)
{
    doc["type"] = type;
    doc["method"] = method;
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