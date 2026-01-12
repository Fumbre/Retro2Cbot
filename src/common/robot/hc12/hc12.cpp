/**
 * @name HC-12
 * @author Sunny
 * @date 15-12-2025
 */

#include "hc12.h"

// Create a SoftwareSerial object to communicate with the HC-12 module
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
    if (!data)
        return;
    hc12.println(data);
}

/**
 * @name receiveDataFromHC12
 * @author Sunny
 * @date 23-12-2025
 * @details receive data from HC-12
 * @return Json string
 */

String receiveDataFromHC12()
{
    String data = ""; // create an empty string to store incoming data

    if (hc12.available())
    {
        // check if there is data available to read from the HC-12 module
        data = hc12.readStringUntil('\n');
    }

    return data; // return the received data
}
