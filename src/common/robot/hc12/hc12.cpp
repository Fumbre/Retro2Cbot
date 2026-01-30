#include "hc12.h"

// Create a SoftwareSerial object to communicate with the HC-12 module
SoftwareSerial hc12(RX, TX);

/**
 * @name buildHC12Connection
 * @author Sunny
 * @date 15-12-2025
 * @details build connection between HC-12 and Arduino
*/

void buildHC12Connection() {
    hc12.begin(9600);
}

/**
 * @name sendDataFromHC12
 * @author Sunny
 * @date 15-12-2025
 * @details send data through HC-12
 * @param data the data that needs send
*/

void sendDataFromHC12(String data) {
    if (!data)
        return;
    hc12.println(data);
}

/**
 * @name receiveDataFromHC12
 * @author Sunny
 * @date 23-12-2025
 * @details Reads data from the HC-12 wireless module.
 * @details Checks if data is available, and if so, reads a complete line terminated by '\n'.
 * @details Returns an empty string if no data is available.
 * @return String containing the received data. If no data is received, returns an empty string.
*/

String receiveDataFromHC12() {
    if (hc12.available() > 0) {
        return hc12.readStringUntil('\n');
    }

    return "";
}

