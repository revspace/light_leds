#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUM_LEDS 4
#define BRIGHTNESS 255

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, 5, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, 6, NEO_GRBW + NEO_KHZ800);


void setup() {
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
  strip2.setBrightness(BRIGHTNESS);
  strip2.begin();
  strip2.show();
}
void loop() {
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;
  for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel
    for(int i=0; i< strip.numPixels(); i++) {
      wheelVal = Wheel(((i * 256 / strip.numPixels()) + j) & 255);
      strip.setPixelColor(i, strip.Color(red(wheelVal), green(wheelVal), blue(wheelVal)));
      strip2.setPixelColor(i, strip2.Color(red(wheelVal), green(wheelVal), blue(wheelVal)));
    }
    strip.show();
    strip2.show();
    delay(6);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}

