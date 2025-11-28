/**
 * @name functions of neopixels
 * @author Sunny
 * @date 24-11-2025
 */
#include "neopixel.h"

// define Neopixel class
Neopixel pixel(PIN_NI, NUMBER_OF_NEOPIXEL);

/**
 * @name initNeopixelPins
 * @author Sunny
 * @date 24-11-2025
 */
void initNeopixelPins()
{
  pixel.begin();
}
/**
 * @name initNeopixelPins
 * @author Sunny
 * @date 26-11-2025
 * @param R red color value (0-255)
 * @param G green color value (0-255)
 * @param B blue color value (0-255)
 */
void turnOnAllLeds(int R, int G, int B)
{
  pixel.fill(0, NUMBER_OF_NEOPIXEL - 1, R, G, B);
  pixel.show();
}

// asdfsad
/**
 * @name turnOffAllLeds
 * @author Sunny
 * @date 26-11-2025
 */
void turnOffAllLeds()
{
  pixel.clear();
}

/**
 * @name turnOnSomeLeds
 * @author Sunny
 * @date 26-11-2025
 * @param index array of led index
 * @param length length of led index array
 * @param R red color value (0-255)
 * @param G green color value (0-255)
 * @param B blue color value (0-255)
 */
void turnOnSomeLeds(int index[], int length, int R, int G, int B)
{
  for (int i = 0; i < length; i++)
  {
    pixel.setNeoPixelColor(index[i], R, G, B);
  }
  pixel.show();
}

/**
 * @name turnOffSomeLeds
 * @author Sunny
 * @date 26-11-2025
 * @param index array of led index
 * @param length length of led index array
 */
void turnOffSomeLeds(int index[], int length)
{
  for (int i = 0; i < length; i++)
  {
    pixel.setNeoPixelColor(index[i], 0, 0, 0);
  }
  pixel.show();
}