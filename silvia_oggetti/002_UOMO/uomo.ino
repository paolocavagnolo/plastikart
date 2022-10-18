//HOMME - VERSION 1.0

/*  Code written by Paolo Cavagnolo for FREITAG - 17/10/2022
  

    3 MOMENTS:
    0 - FLASH!
    1 - Starts a beam of light - BEAM
    2 - Light segments - CIRC
    3 - Pulsing of the leds - FADE
*/

#define BEAM_SPEED 85   //50 FAST - 100 SLOW
#define CIRC_SPEED 120  //80 FAST - 160 SLOW
#define FADE_SPEED 2    //1 FAST  - 3 SLOW

#define BRIGHT 150      //255 MAX BRIGHTNESS (ONLY DURING FADE PART)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        6

#define NUMPIXELS 180 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int i, j, w, zz,hh;

void setup() {

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  Serial.begin(9600);

  pixels.begin();
  pixels.clear();
  pixels.show();

  delay(100);

  digitalWrite(3, HIGH);

  delay(200);

  //FLASH

//  for (zz = 0; zz < 1; zz++) {
//    for (hh = 0; hh < NUMPIXELS; hh++) {
//      pixels.setPixelColor(hh, pixels.Color(0, 0, 255));
//    }
//    pixels.show();
//    delay(500);
//    pixels.clear();
//    pixels.show();
//  }



}



unsigned long dt_beam = 0;
unsigned long dt_fade = 0;
unsigned long dt_circ = 0;

uint8_t lval = 255;
int vval = BRIGHT;
int x = 1;

void loop() {


  if (millis() > 14000) {

    fade();

  }
  else if (millis() > 10000) {

    circ();

  }
  else {

    beam();

  }

}


void beam() {
  if ((millis() - dt_beam) > BEAM_SPEED) {
    dt_beam = millis();

    pixels.setPixelColor(i, pixels.Color(0, 0, lval));

    i++;

    if (i > NUMPIXELS) {
      lval = 0;
      i = 0;
    }

    pixels.show();

  }
}

void circ() {
  if ((millis() - dt_circ) > CIRC_SPEED) {
    dt_circ = millis();

    for (w = 0; w < NUMPIXELS; w++) {
      if (((w - i) % 5 == 0)) {
        pixels.setPixelColor(w, pixels.Color(0, 0, 0));
      }
      else {
        pixels.setPixelColor(w, pixels.Color(0, 0, lval));
      }

    }
    pixels.show();

    i++;

    if (i >= 5) {
      i = 0;
    }

  }
}

void fade() {

  if ((micros() - dt_fade) > 7700) {

    dt_fade = micros();

    if (vval >= BRIGHT) {
      x = -1;
    }
    if (vval <= 0) {
      x = 1;
    }

    vval = vval + x;

    for (j = 0; j < NUMPIXELS; j++) {
      if (j % 5 == 0) {
        pixels.setPixelColor(j, pixels.Color(0, 0, 0));
      }
      else {
        pixels.setPixelColor(j, pixels.Color(0, 0, vval));
      }
    }

    pixels.show();
  }
}
