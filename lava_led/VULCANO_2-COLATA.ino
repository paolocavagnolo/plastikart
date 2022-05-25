#include <FastLED.h>

#define DATA_PIN 9
#define NUM_LEDS    144*3

CRGB leds[NUM_LEDS];

uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE(heatmap_gp) {
    0,  255,  100,    0,  //orange
  100,    0,    0,    0,  //black
  255,  255,    0,    0,  //red
};

CRGBPalette16 myPal = heatmap_gp;

void setup() {
  pinMode(9,OUTPUT);   
  digitalWrite(9,LOW);

  delay(100);

  LEDS.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  LEDS.clear();
  LEDS.show();
  

  LEDS.setTemperature(Candle);

  for (int i=0; i<NUM_LEDS; i++) {
    colorIndex[i] = (int)random8()*0.4+(int)(i*3);
  }

  LEDS.clear();
  LEDS.show();
 
}


bool state = true;
unsigned long tt = 0;
unsigned long attesa = 0;
int an0 = 0;
uint8_t blev = 0;

unsigned long ttc = 0;

int colata = 0;

bool stuck = true;
int s_ind = 0;


void loop() {

    
    //POT 1
    an0 = analogRead(0);
    if (an0 > 1000) {
      blev = 0;
    }
    else if (an0 < 15) {
      blev = 255;
    }
    else if ((an0 > 10) && (an0 < 1010)) {
      blev = map(analogRead(0),1023,0,0,255);
    }
    
    LEDS.setBrightness( blev );
  
    //POT 2
    attesa = (unsigned long)map( analogRead(1),1024,0,0,25000 );
    
    for (uint16_t i=0; i<NUM_LEDS; i++) {
      leds[i] = ColorFromPalette(myPal, colorIndex[i]);
    }
  
    if ((micros() - tt) > attesa) {
      tt = micros();
      
      for (uint16_t i=0; i<NUM_LEDS; i++) {
        colorIndex[i]--;
      }
      
    }
  
    if ((colata < NUM_LEDS) ) {
  
      if (((millis() - ttc) > attesa/150)) {
        ttc = millis();
        colata++;
      }
      
      for (uint16_t i=colata; i<NUM_LEDS; i++) {
        leds[i].red = 0;
        leds[i].green = 0;
        leds[i].blue = 0;
      }
  
    }
  
  
    LEDS.show();

}
