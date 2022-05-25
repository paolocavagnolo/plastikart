#include <FastLED.h>

#define DATA_PIN 9
#define NUM_LEDS    144
#define BRIGHTNESS  50
#define FRAMES_PER_SECOND 10

CRGB leds[NUM_LEDS];


void setup() {
  delay(1000);
  LEDS.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  LEDS.setBrightness( 255 );
  LEDS.setTemperature(Candle);
  
}

void loop() {

  EVERY_N_MILLISECONDS(40) {
    leds[0] = CHSV(random8(-5,35), 255, random8()*random8(0,2)*random8(0,2));
  
    for (uint8_t i=NUM_LEDS-1; i>0; i--) {
      leds[i] = leds[i-1];
    }
  }
  
  LEDS.show();
  
  

}
