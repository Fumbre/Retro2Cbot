/**
 * @name class of Neopixels
 */

#pragma once
#include <Arduino.h>
#define MAX_COLOUR_VALUE 255

struct RGB
{
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

class Neopixel
{
private:
  int PIN_NI;             // data pin
  int NUMBER_OF_LED;      // number of led
  RGB *color;             // RGB color pointer
  volatile uint8_t *port; // Arduino pin pointers (PORTD = D0~D7, PORTB = D8~D13, PORTC = A0~A7 )
  uint8_t bitMask;        // the position binary code of Arduino pins

  /**
   * @name initinfo
   * @author Sunny
   * @date 26-11-2025
   * @details According number of pins, it can find that which register does this pin belong to. And get related binary code
   */
  void initinfo()
  {
    uint8_t pin = PIN_NI; // 5
    if (pin <= 7)
    { // D0 ~ D7 -> PORTD
      port = &PORTD;
      bitMask = 1 << pin;
    }
    else if (pin <= 13)
    { // D8 ~ D13 -> PORTB
      port = &PORTB;
      bitMask = 1 << (pin - 8);
    }
    else if (pin >= 14 && pin <= 19)
    { // A0~A7 PORTC
      port = &PORTC;
      bitMask = 1 << (pin - 14);
    }
  }

  /**
   * @name checkRGBvalue
   * @author Sunny
   * @date 24-11-2025
   * @return RGB
   */
  RGB checkRGBvalue(int &R, int &G, int &B)
  {
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
   * @param colorValue color binary code (0-255)
   * @details There is a small shift register in RGB led. According to WS2812 protocol, it should obey agreement of MSB(from left to right)
   */
  void sendBytes(uint8_t *ptr, int count)
  {
    uint8_t b;
    uint8_t bit;
    uint8_t next = 0; 
    uint8_t hi = bitMask;
    uint8_t lo = 0;

    bit = 8;
    b = *ptr++;
    asm volatile("head20%=:\n\t"            // loop 1 byte => while(bit>0) {
                 "st %a[port], %[hi]\n\t"   // digitalWrite(pin, HIGH)
                 "sbrc %[byte], 7\n\t"      // check the first left digit. if this digit is 0, skip next command. if it is 1, execute next command
                 "mov %[next], %[hi]\n\t"   // next = hi
                 "dec %[bit]\n\t"           // bit--
                 "st %a[port], %[next]\n\t" // digitalWrite(pin, HIGH)
                 "mov %[next], %[lo]\n\t"   // next = lo
                 "breq nextbyte20%=\n\t"    // if bit equals 0, jump to the nextbyte20 loop. loop next byte
                 "rol %[byte]\n\t"          // left recycle b0 -> b1, b2 -> b3, .... b6 -> b7, b7 put into the Carry register
                 "rjmp .+0\n\t"             // execute next command, which occupies 2 cycle. cycle depends on the CPU frequency
                 "nop\n\t"                  // no operation, which occupies 1 cycle
                 "st %a[port], %[lo]\n\t"   // digitalWrite(pin, LOW)
                 "nop\n\t"
                 "rjmp .+0\n\t"
                 "rjmp head20%=\n\t"        // }
                 "nextbyte20%=:\n\t"        // loop next byte
                 "ldi %[bit], 8\n\t"        // reset bit => bit = 8
                 "ld %[byte], %a[ptr]+\n\t" // put ptr value to the byte virable and point next value in ptr pointer
                 "st %a[port], %[lo]\n\t"   // digitalWrite(pin, LOW)
                 "nop\n\t"
                 "sbiw %[count], 1\n\t" // count--
                 "brne head20%=\n\t" : [port] "+e"(port), [byte] "+r"(b), [bit] "+r"(bit), [next] "=r"(next), [count] "+w"(count) : [ptr] "e"(ptr), [hi] "r"(hi), [lo] "r"(lo));
    // brne head20% go back to loop beginning
  }

public:
  /**
   * @name constructure function of Neopixels
   * @author Sunny
   * @date 26-11-2025
   * @param dataPin  PIN_NI
   * @param numberOfLeds number of leds
   */
  Neopixel(int dataPin, int numberOfLeds)
  {
    // set value to private properties
    PIN_NI = dataPin;
    NUMBER_OF_LED = numberOfLeds;
    color = new RGB[NUMBER_OF_LED];
    // turn off leds
    for (int i = 0; i < NUMBER_OF_LED; i++)
    {
      color[i] = {0, 0, 0};
    }
  }

  /**
   * @name ~Neopixel
   * @author Sunny
   * @date 26-11-2025
   * @details In Arduino, when Arduino closing or reseting, color pointer should be released
   */
  ~Neopixel()
  {
    delete[] color;
  }

  /**
   * @name begin
   * @author Sunny
   * @date 26-11-2025
   */
  void begin()
  {
    pinMode(PIN_NI, OUTPUT);
    digitalWrite(PIN_NI, LOW);
    initinfo();
  }

  /**
   * @name fill
   * @author Sunny
   * @date 26-11-2025
   * @details turn on some RGB LEDs in certain color
   * @param start the index of first led
   * @param end the index of last led
   * @param R red color value
   * @param G green color value
   * @param B blue color value
   */
  void fill(int start = 0, int end = -1, int R = 0, int G = 0, int B = 0)
  {
    // check index edge
    if (end == -1)
    {
      end = NUMBER_OF_LED - 1;
    }
    if (start < 0)
      start = 0;
    if (start > end)
      start = end;
    // check color value
    RGB rgb = checkRGBvalue(R, G, B);
    // put color value into the RGB pointer
    for (int i = start; i <= end; i++)
    {
      color[i] = rgb;
    }
  }

  /**
   * @name clear
   * @author Sunny
   * @date 26-11-2025
   * @details turn off all leds
   */
  void clear()
  {
    for (int i = 0; i < NUMBER_OF_LED; i++)
    {
      color[i] = {0, 0, 0};
    }
    show();
  }

  /**
   * @name show
   * @author Sunny
   * @date 26-11-2025
   * @details update led color status from RGB pointer
   */
  void show()
  {
    noInterrupts();
    sendBytes((uint8_t *)color, NUMBER_OF_LED * 3);
    interrupts();
    // resetting signal, In WS2812B, if low voltage last 50µs at least, WS2812B should get last LED color status
    delayMicroseconds(300);
  }

  /**
   * @name setNeoPixelColor
   * @author Sunny
   * @date 26-11-2025
   * @details change one led color status and put it into RGB pointer
   * @param index led index
   * @param R red color
   * @param G green color
   * @param B blue color
   */
  void setNeoPixelColor(int index, int R, int G, int B)
  {
    RGB rgb = checkRGBvalue(R, G, B);
    color[index] = rgb;
  }
};