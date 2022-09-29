//DONNA

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        6 

#define NUMPIXELS 155 // Popular NeoPixel ring size
#define LEN 20

#define DTIME 90
#define LBEAM 3
#define DBEAM 1
#define NBEAM 180/(LBEAM+DBEAM+1)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int i;

void setup() {

  pinMode(3,OUTPUT);
  digitalWrite(3, LOW);

  pixels.begin();
  pixels.clear(); 
  pixels.show(); 

  delay(500);
  
  digitalWrite(3, HIGH);

  delay(500);

  for (i=0;i<NUMPIXELS;i++){
    for (uint8_t w = 0; w<NBEAM; w++) {
      beam0(i-(LBEAM+DBEAM+1)*w);
    }
    pixels.show();
  
    delay(DTIME);
  }
  
}

uint8_t intensity = 0;
uint8_t xx = 1;

void loop() {

  for (uint8_t w = 0; w<NBEAM; w++) {
    beam(i-(LBEAM+DBEAM+1)*w);
  }
  pixels.show();

  if (i>NUMPIXELS) {
    i = 0;
  }
  else {
    i++;
    delay(DTIME);
  }

  intensity = intensity + xx;
  
  if (intensity > 255) {
    xx = -1;
    intensity = 254;
  }
  else if (intensity < 1) {
    xx = 1;
    intensity = 0;
  }
  
  for (uint8_t k = 155; k < 180; k++) {
    pixels.setPixelColor(k, pixels.Color(intensity,0,0));
  }
  
  pixels.show();
  
}

void beam(int x) {

  uint8_t j;

  pixels.setPixelColor(x, pixels.Color(255,0,0));

  for (j=1; j<LBEAM; j++) {
    if ((x-j) < 0) {
      pixels.setPixelColor(NUMPIXELS+x-j, pixels.Color(255,0,0));
    }
    else {
      pixels.setPixelColor(x-j, pixels.Color(255,0,0));
    }
  }
  j++;
  if ((x-j) < 0) {
    pixels.setPixelColor(NUMPIXELS+x-j, pixels.Color(0,0,0));
  }
  else {
    pixels.setPixelColor(x-j, pixels.Color(0,0,0));
  }
  
}

void beam0(int x) {

  uint8_t j;

  pixels.setPixelColor(x, pixels.Color(255,0,0));

  for (j=1; j<LBEAM; j++) {
    if ((x-j) >= 0) {
      pixels.setPixelColor(x-j, pixels.Color(255,0,0));
    }
  }
  j++;
  if ((x-j) >= 0) {
    pixels.setPixelColor(x-j, pixels.Color(0,0,0));
  }
  
}
