#include "hc12.h"

SoftwareSerial hc12(RX, TX);

void buildHC12Connection()
{
    hc12.begin(9600);
}

void sendDataFromHC12(String data)
{
    if(data.length() == 0) return;
    hc12.println(data);
}