//DONNA

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        6

#define NUMPIXELS 150 // Popular NeoPixel ring size
#define LEN 20

#define DTIME 90
#define LBEAM 3
#define DBEAM 1
#define NBEAM 180/(LBEAM+DBEAM+1)

Adafruit_NeoPixel pixels(180, PIN, NEO_GRB + NEO_KHZ800);

int i;

void setup() {

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  Serial.begin(9600);

  pixels.begin();
  pixels.clear();
  pixels.show();

  delay(500);

  digitalWrite(3, HIGH);

  delay(500);

  for (i = 0; i < NUMPIXELS; i++) {
    for (uint8_t w = 0; w < NBEAM; w++) {
      beam0(i - (LBEAM + DBEAM + 1)*w);
    }
    pixels.show();

    delay(DTIME);
  }

}

int intensity = 0;
int xx = 1;
int s = 0;
unsigned long dt = 0;

void loop() {

  //SPENGO PANCIA
  if (s == 0) {
    for (i = 150; i < 180; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    s = 1;
  }


  //BEAM
  if (s == 1) {

    for (uint8_t w = 0; w < NBEAM; w++) {
      beam(i - (LBEAM + DBEAM + 1)*w);
    }

    if (i > NUMPIXELS) {
      i = 0;
    }
    else {
      i++;
      delay(DTIME);
    }

    if ((millis() - dt) > 15000) {
      dt = millis();
      s = 2;
    }

  }

  // SPENGO BEAM
  if (s == 2) {
    for (i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    s = 3;
  }

  // PANCIA
  if (s == 3) {

    intensity = intensity + xx;

    if (intensity > 255) {
      xx = -4;
      intensity = 254;
    }
    else if (intensity < 1) {
      xx = 4;
      intensity = 0;
    }

    for (uint8_t k = 150; k < 180; k++) {
      pixels.setPixelColor(k, pixels.Color(intensity, 0, 0));
    }

    Serial.println((millis() - dt));
    if ((millis() - dt) > 10000) {
      dt = millis();
      s = 0;
    }
  }


  pixels.show();
  Serial.println(s);

}

void beam(int x) {

  uint8_t j;

  pixels.setPixelColor(x, pixels.Color(255, 0, 0));

  for (j = 1; j < LBEAM; j++) {
    if ((x - j) < 0) {
      pixels.setPixelColor(NUMPIXELS + x - j, pixels.Color(255, 0, 0));
    }
    else {
      pixels.setPixelColor(x - j, pixels.Color(255, 0, 0));
    }
  }
  j++;
  if ((x - j) < 0) {
    pixels.setPixelColor(NUMPIXELS + x - j, pixels.Color(0, 0, 0));
  }
  else {
    pixels.setPixelColor(x - j, pixels.Color(0, 0, 0));
  }

}

void beam0(int x) {

  uint8_t j;

  pixels.setPixelColor(x, pixels.Color(255, 0, 0));

  for (j = 1; j < LBEAM; j++) {
    if ((x - j) >= 0) {
      pixels.setPixelColor(x - j, pixels.Color(255, 0, 0));
    }
  }
  j++;
  if ((x - j) >= 0) {
    pixels.setPixelColor(x - j, pixels.Color(0, 0, 0));
  }

}a
