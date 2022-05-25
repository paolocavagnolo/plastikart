#include <FastLED.h>

#define DATA_PIN 9
#define NUM_LEDS    144
#define BRIGHTNESS  50
#define FRAMES_PER_SECOND 10

CRGB leds[NUM_LEDS];

uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE(heatmap_gp) {
    0,  255,  139,    0,  //orange
  100,  255,    0,    0,  //red
  255,    0,    0,    0,  //black
};

CRGBPalette16 myPal = heatmap_gp;

void setup() {
  digitalWrite(8,OUTPUT);
  delay(1000);
  LEDS.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  LEDS.setBrightness( 255 );
  LEDS.setTemperature(Candle);

  for (int i=0; i<NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }
  
}

bool state = true;

void loop() {

  for (uint8_t i=0; i<NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(myPal, colorIndex[i]);
  }

  EVERY_N_MILLISECONDS(5) {
    for (uint8_t i=0; i<NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }

  
  LEDS.show();
    

}
