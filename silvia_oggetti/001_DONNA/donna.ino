//FEMME

#define BEAM_SPEED 70
#define CIRC_SPEED 110
#define VENTRE_SPEED 3

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        6

#define NUMPIXELS 180 // Popular NeoPixel ring size
#define FLOWPIXELS 150

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int i, j, w;

void setup() {

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  Serial.begin(9600);

  pixels.begin();
  pixels.clear();
  pixels.show();

  delay(100);

  digitalWrite(3, HIGH);

  delay(100);

}

unsigned long dt_beam = 0;
unsigned long dt_circ = 0;
unsigned long dt_fade = 0;

uint8_t lval = 255;
int vval = 0;
int x = 1;

bool firstB = true;
bool firstA = true;

void loop() {


  if (millis() > 14000) {
    if (firstB) {
      pixels.clear();
      pixels.show();
      firstB = false;
    }

    fade();

  }
  else if (millis() > 10000) {
    if (firstA) {
      for (i = 0; i < FLOWPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
      pixels.show();
      firstA = false;
    }

    circ();

  }
  else {

    beam();

  }

}


void beam() {
  if ((millis() - dt_beam) > BEAM_SPEED) {
    dt_beam = millis();

    pixels.setPixelColor(i, pixels.Color(lval, 0, 0));
    pixels.show();

    i++;

    if (i > FLOWPIXELS) {
      lval = 0;
      i = 0;
    }

  }
}

void circ() {
  if ((millis() - dt_circ) > CIRC_SPEED) {
    dt_circ = millis();

    for (w = 0; w < FLOWPIXELS; w++) {
      if ((w+i)%5 == 0) {
        pixels.setPixelColor(w, pixels.Color(0, 0, 0));
      }
      else {
        pixels.setPixelColor(w, pixels.Color(lval, 0, 0));
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

  if ((millis() - dt_fade) > VENTRE_SPEED) {

    dt_fade = millis();

    if (vval >= 255) {
      x = -1;
    }
    if (vval <= 0) {
      x = 1;
    }

    vval = vval + x;

    for (j = FLOWPIXELS; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, pixels.Color(vval, 0, 0));
    }

    pixels.show();
  }
}
