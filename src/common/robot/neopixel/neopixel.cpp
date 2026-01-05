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
  for(int i = 0; i < 4; i++){
    colorArray[i][0] = R;
    colorArray[i][1] = G;
    colorArray[i][2] = B;
  }
  pixel.show();
}

/**
 * @name turnOffAllLeds
 * @author Sunny
 * @date 26-11-2025
 */
void turnOffAllLeds()
{
  pixel.clear();
  for(int i = 0; i < 4; i++){
    colorArray[i][0] = 0;
    colorArray[i][1] = 0;
    colorArray[i][2] = 0;
  }
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
    colorArray[index[i]][0] = R;
    colorArray[index[i]][1] = G;
    colorArray[index[i]][2] = B;
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
    colorArray[index[i]][0] = 0;
    colorArray[index[i]][1] = 0;
    colorArray[index[i]][2] = 0;
    pixel.setNeoPixelColor(index[i], 0, 0, 0);
  }
  pixel.show();
}