#include <FastLED.h>

#define DATA_PIN 9
#define NUM_LEDS    144

CRGB leds[NUM_LEDS];

uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE(heatmap_gp) {
    0,  255,  90,    0,  //orange
  100,    0,    0,    0,  //black
  255,  255,    0,    0,  //red
};

CRGBPalette16 myPal = heatmap_gp;

void setup() {
  
  digitalWrite(9,OUTPUT);
  digitalWrite(9,LOW);
  
  delay(100);
  
  LEDS.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  LEDS.clear();
  LEDS.show();
  
  LEDS.setTemperature(Candle);

  for (int i=0; i<NUM_LEDS; i++) {
    //colorIndex[i] = random8();
    colorIndex[i] = (int)random8()+(int)(i);
  }

  LEDS.clear();
  LEDS.show();

  delay(10000);
   
}

uint8_t i = 0;
unsigned long attesa = 0;
unsigned long tt = 0;

void loop() {

  for (uint16_t i=0; i<NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(myPal, colorIndex[i]);
  }

  if (millis() < 25500) {
    
    LEDS.setBrightness(i);
    LEDS.show();
    i++;
  
    delay(60);

    if (i>255) {
      i = 255;
    }
  }

  else {
    
    //POT 2
    attesa = 5000;
  
    if ((micros() - tt) > attesa) {
      tt = micros();
      
      for (uint16_t i=0; i<NUM_LEDS; i++) {
        colorIndex[i]++;
      }
      
    }

    LEDS.show();
  }
    
}
