/**
 * @name functions of neopixels
 * @author Sunny
 * @date 24-11-2025
 */
#include "neopixel.h"

Adafruit_NeoPixel pixels(NUMBER_OF_NEOPIXEL,PIN_NI,NEO_RGB + NEO_KHZ800);

/**
 * @name initNeopixel
 * @author Sunny
 * @date 24-11-2025
 */
void initNeopixel(){
    pixels.begin();
}

/**
 * @name checkRGBvalue
 * @author Sunny
 * @date 24-11-2025
 * @return RGB
 */
RGB checkRGBvalue(int &R, int &G, int &B){
    RGB rgb;
    R = constrain(R,0,MAX_COLOUR_VALUE);
    G = constrain(G,0,MAX_COLOUR_VALUE);
    B = constrain(B,0,MAX_COLOUR_VALUE);
    rgb.R = R;
    rgb.G = G;
    rgb.B = B;
    return rgb;
}

/**
 * @name turnONAllNeoPixels
 * @author Sunny
 * @date 24-11-2025
 * @param R red (0-255)
 * @param G green (0-255)
 * @param B blue (0-255)
 */
void turnONAllNeoPixels(int R, int G, int B){
    //clear all Neopixel leds
    pixels.clear();
    // limit color value
    RGB rgb =  checkRGBvalue(R,G,B);
    Serial.print("R: ");
    Serial.println(rgb.R);
    Serial.print("G: ");
    Serial.println(rgb.G);
    Serial.print("B: ");
    Serial.println(rgb.B);
    //open all leds
    pixels.fill(pixels.Color(rgb.R,rgb.G,rgb.B));
    pixels.show();
}

/**
 * @name turnOffAllNeopixel
 * @author Sunny
 * @date 24-11-2025
 */
void turnOffAllNeopixel(){
    pixels.clear();
}

/**
 * @name turnOnSomeNeopixels
 * @author Sunny
 * @date 24-11-2025
 * @param index led index array
 * @param length the length of index array
 * @param R red color value
 * @param G green color value
 * @param B blue color value
 */
void turnOnSomeNeopixels(int index[],int length, int R, int G, int B){
    //check color value
    RGB rgb = checkRGBvalue(R,G,B);
    Serial.println(length);
    if(length <= 0) return;
    //set color in leds
    for(int i = 0; i < length; i++){
        pixels.setPixelColor(index[i],pixels.Color(rgb.R,rgb.G,rgb.B));
    }
    //update led status
    pixels.show();
}

/**
 * @name turnOffSomeNeopixels
 * @author Sunny
 * @date 24-11-2025
 * @param index led index array
 * @param length the length of index array
 */
void turnOffSomeNeopixels(int index[], int length){
    //set led color to black
    for(int i = 0; i < length; i++){
        pixels.setPixelColor(index[i],pixels.Color(0,0,0));
    }
    //update led status
    pixels.show();
}
