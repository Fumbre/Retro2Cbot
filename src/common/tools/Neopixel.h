/**
 * @name Neopixel
 * @author Sunny
 * @date 15-12-2025
 * @details Class to control WS2812/Neopixel RGB LEDs.
 * @details Manages LED colors using RGB structs 
 * and updates LEDs via direct port manipulation for speed.
 * @details Supports setting individual LEDs, filling ranges, clearing, and updating colors.
*/

#pragma once

#include <Arduino.h>

#define MAX_COLOUR_VALUE 255

struct RGB {
    uint8_t R;
    uint8_t G;
    uint8_t B;
};

class Neopixel {
private:
    int PIN_NI;                     // Data pin for LED strip
    int NUMBER_OF_LED;              // Total number of LEDs
    RGB *color;                     // Current RGB color array
    RGB *lastColor;                 // Previous RGB color array
    volatile uint8_t *port;         // PORT register pointer for fast pin writes
    uint8_t bitMask;                // Pin mask for PORT manipulation

    /**
     * @name initinfo
     * @author Sunny
     * @date 26-11-2025
     * @details Determines the correct PORT and bit mask for the data pin.
    */
  
    void initinfo() {
        uint8_t pin = PIN_NI;

        if (pin <= 7) {
            port = &PORTD;
            bitMask = 1 << pin;
        } else if (pin <= 13) {
            port = &PORTB;
            bitMask = 1 << (pin - 8);
        } else if (pin >= 14 && pin <= 19) {
            port = &PORTC;
            bitMask = 1 << (pin - 14);
        }
    }

    /**
     * @name checkRGBvalue
     * @author Sunny
     * @date 24-11-2025
     * @param R Red component
     * @param G Green component
     * @param B Blue component
     * @details Constrains RGB values to 0–255 and returns an RGB struct.
     * @return RGB Struct containing constrained values
    */

    RGB checkRGBvalue(int &R, int &G, int &B) {
        RGB rgb;
        R = constrain(R, 0, MAX_COLOUR_VALUE);
        G = constrain(G, 0, MAX_COLOUR_VALUE);
        B = constrain(B, 0, MAX_COLOUR_VALUE);
        rgb.R = R;
        rgb.G = G;
        rgb.B = B;
        return rgb;
    }

    /**
     * @name sendBytes
     * @author Sunny
     * @date 26-11-2025
     * @param ptr Pointer to array of bytes to send
     * @param count Number of bytes to send
     * @details Sends bytes to LEDs following the WS2812 protocol using precise timing and direct port writes.
    */

    void sendBytes(uint8_t *ptr, int count) {
        uint8_t b, bit, next, hi = bitMask, lo = 0;
        bit = 8;
        b = *ptr++;
        asm volatile(
            "head20%=:\n\t"
            "st %a[port], %[hi]\n\t"
            "sbrc %[byte], 7\n\t"
            "mov %[next], %[hi]\n\t"
            "dec %[bit]\n\t"
            "st %a[port], %[next]\n\t"
            "mov %[next], %[lo]\n\t"
            "breq nextbyte20%=\n\t"
            "rol %[byte]\n\t"
            "rjmp .+0\n\t"
            "nop\n\t"
            "st %a[port], %[lo]\n\t"
            "nop\n\t"
            "rjmp .+0\n\t"
            "rjmp head20%=\n\t"
            "nextbyte20%=:\n\t"
            "ldi %[bit], 8\n\t"
            "ld %[byte], %a[ptr]+\n\t"
            "st %a[port], %[lo]\n\t"
            "nop\n\t"
            "sbiw %[count], 1\n\t"
            "brne head20%=\n\t"
            : [port] "+e"(port), [byte] "+r"(b), [bit] "+r"(bit), [next] "+r"(next), [count] "+w"(count)
            : [ptr] "e"(ptr), [hi] "r"(hi), [lo] "r"(lo)
        );
    }

public:
    /**
     * @name Neopixel
     * @author Sunny
     * @date 26-11-2025
     * @param dataPin Arduino pin connected to the LED strip
     * @param numberOfLeds Total number of LEDs on the strip
     * @details Constructor initializes color arrays and sets all LEDs off
    */

    Neopixel(int dataPin, int numberOfLeds) {
        PIN_NI = dataPin;
        NUMBER_OF_LED = numberOfLeds;
        color = new RGB[NUMBER_OF_LED];
        lastColor = new RGB[NUMBER_OF_LED];

        for (int i = 0; i < NUMBER_OF_LED; i++) {
            color[i] = {0, 0, 0};
            lastColor[i] = {0, 0, 0};
        }
    }

    /**
     * @name ~Neopixel
     * @author Sunny
     * @date 26-11-2025
     * @details Destructor frees allocated color arrays to prevent memory leaks
    */

    ~Neopixel() {
        delete[] color;
        delete[] lastColor;
    }

    /**
     * @name begin
     * @author Sunny
     * @date 26-11-2025
     * @details Initializes the data pin and determines PORT register and bit mask
    */
  
    void begin() {
        pinMode(PIN_NI, OUTPUT);
        digitalWrite(PIN_NI, LOW);
        initinfo();
    }

    /**
     * @name fill
     * @author Sunny
     * @date 26-11-2025
     * @param start Start LED index
     * @param end End LED index (-1 = last LED)
     * @param R Red component
     * @param G Green component
     * @param B Blue component
     * @details Sets a range of LEDs to the specified color
    */

    void fill(int start = 0, int end = -1, int R = 0, int G = 0, int B = 0) {
        
      if (end == -1) {
        end = NUMBER_OF_LED - 1;
      }
        
      if (start < 0) {
        start = 0;
      }
        
      if (start > end) {
          
        start = end;
      }
        
        RGB rgb = checkRGBvalue(R, G, B);

      for (int i = start; i <= end; i++) {
          color[i] = rgb;
      }
    }

    /**
     * @name clear
     * @author Sunny
     * @date 26-11-2025
     * @details Turns off all LEDs and updates the strip
    */

    void clear() {

        for (int i = 0; i < NUMBER_OF_LED; i++) {
            color[i] = {0, 0, 0};
        }
        show();
    }

    /**
     * @name show
     * @author Sunny
     * @date 26-11-2025
     * @details Sends current color array to the LED strip using WS2812 protocol
    */

    void show() {
        if (!canShow()) {
          return;
        }
        
        memcpy(lastColor, color, NUMBER_OF_LED * sizeof(RGB));
        noInterrupts();
        sendBytes((uint8_t *)color, NUMBER_OF_LED * 3);
        delayMicroseconds(300);                                   // Reset signal
        interrupts();
    }

    /**
     * @name setNeoPixelColor
     * @author Sunny
     * @date 26-11-2025
     * @param index LED index
     * @param R Red component
     * @param G Green component
     * @param B Blue component
     * @details Sets a single LED to the specified RGB color
    */

    void setNeoPixelColor(int index, int R, int G, int B) {
        RGB rgb = checkRGBvalue(R, G, B);
        color[index] = rgb;
    }

    /**
     * @name canShow
     * @author Sunny
     * @date 27-11-2025
     * @details Checks if the current color array differs from the last shown array
     * @return bool True if colors have changed, otherwise false
    */

    bool canShow() {
        for (int i = 0; i < NUMBER_OF_LED; i++) {
            if (color[i].R != lastColor[i].R || color[i].G != lastColor[i].G || color[i].B != lastColor[i].B) {
                return true;
            }
        }
        return false;
    }
};
