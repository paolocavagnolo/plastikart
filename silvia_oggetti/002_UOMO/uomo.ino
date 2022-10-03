//UOMO

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN  6 

#define NUMPIXELS 130 // Popular NeoPixel ring size
#define LEN 20

uint8_t valD[] = {90,45,130,30,100};
uint8_t DTIME = 90;

#define LBEAM 3
#define DBEAM 3 //1
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

unsigned long dtt = 0;
uint8_t kk = 0;


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

  if ((millis() - dtt) > 7000) {
    dtt = millis();
    DTIME = valD[kk];
    if (kk == 4) {
      kk = 0;
    }
    else {
      kk++;
    }
  }

  
  
}

void beam(int x) {

  uint8_t j;

  pixels.setPixelColor(x, pixels.Color(0,0,255));

  for (j=1; j<LBEAM; j++) {
    if ((x-j) < 0) {
      pixels.setPixelColor(NUMPIXELS+x-j, pixels.Color(0,0,255));
    }
    else {
      pixels.setPixelColor(x-j, pixels.Color(0,0,255));
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

  pixels.setPixelColor(x, pixels.Color(0,0,255));

  for (j=1; j<LBEAM; j++) {
    if ((x-j) >= 0) {
      pixels.setPixelColor(x-j, pixels.Color(0,0,255));
    }
  }
  j++;
  if ((x-j) >= 0) {
    pixels.setPixelColor(x-j, pixels.Color(0,0,0));
  }
  
}
