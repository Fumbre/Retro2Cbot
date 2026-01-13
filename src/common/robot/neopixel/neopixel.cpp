/**
 * @name functions of neopixels
 * @author Sunny
 * @date 24-11-2025
 */

#include "neopixel.h"

// define Neopixel class
// Neopixel pixel(PIN_NI, NUMBER_OF_NEOPIXEL);
Adafruit_NeoPixel strip(NUMBER_OF_NEOPIXEL, PIN_NI, NEO_RGB + NEO_KHZ800);

/**
 * @name initNeopixelPins
 * @author Sunny
 * @date 24-11-2025
 */

void initNeopixelPins()
{
  strip.begin();
  strip.clear();
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

  for (int i = 0; i < 4; i++)
  {
    strip.setPixelColor(i, strip.Color(R, G, B));
    colorArray[i][0] = R;
    colorArray[i][1] = G;
    colorArray[i][2] = B;
  }
  strip.show();
}

/**
 * @name turnOffAllLeds
 * @author Sunny
 * @date 26-11-2025
 */

void turnOffAllLeds()
{
  for (int i = 0; i < 4; i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    colorArray[i][0] = 0;
    colorArray[i][1] = 0;
    colorArray[i][2] = 0;
  }
  strip.show();
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
    strip.setPixelColor(index[i], strip.Color(R, G, B));
    colorArray[index[i]][0] = R;
    colorArray[index[i]][1] = G;
    colorArray[index[i]][2] = B;
  }

  strip.show();
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
    strip.setPixelColor(index[i], strip.Color(0, 0, 0));
  }

  strip.show();
}

void turnOnOneLed(int index, int R, int G, int B)
{
  strip.setPixelColor(index, strip.Color(R, G, B));
  strip.show();
}