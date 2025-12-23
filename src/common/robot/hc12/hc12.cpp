/**
 * @name HC-12
 * @author Sunny
 * @date 15-12-2025
 */
#include "hc12.h"

SoftwareSerial hc12(RX, TX);

/**
 * @name buildHC12Connection
 * @author Sunny
 * @date 15-12-2025
 * @details build connection between HC-12 and Arduino
 */
void buildHC12Connection()
{
    hc12.begin(9600);
}

/**
 * @name sendDataFromHC12
 * @author Sunny
 * @date 15-12-2025
 * @details send data through HC-12
 * @param data the data that needs send
 */
void sendDataFromHC12(String data)
{
    if(data.length() == 0) return;
    hc12.println(data);
}