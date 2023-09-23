// ESP32 DEV KIT

#include <EEPROM.h>
#define EEPROM_SIZE 2000
#define E_ADD_1 100
#define E_ADD_2 300
#define E_ADD_3 600
#define E_ADD_4 900

int adds[] = { E_ADD_1, E_ADD_2, E_ADD_3, E_ADD_4 };

#include <ESP32Encoder.h>

#define NUM_ENC 1
#define btnPin 19
#define ENC1_CLK 23
#define ENC1_DT 22

#define ENC_TYPE 2  // 1: HalfQuad  2: SingleEdge  3: FullQuad

ESP32Encoder enc[NUM_ENC];
int encVal[NUM_ENC];
int encStep = 1;
int oldEnc[NUM_ENC];
int clk[] = { ENC1_CLK };
int dt[] = { ENC1_DT };
int encMax[] = { 255 };
int encMin[] = { 0 };

void init_enc(int num) {
  if (ENC_TYPE == 1) {
    enc[num].attachHalfQuad(clk[num], dt[num]);
  } else if (ENC_TYPE == 2) {
    enc[num].attachSingleEdge(clk[num], dt[num]);
  } else if (ENC_TYPE == 3) {
    enc[num].attachFullQuad(clk[num], dt[num]);
  }
}


// GAMMA 2.8
const uint8_t gamma8[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
  2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
  5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};


#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define DATA_PIN 13
#define NUM_LEDS 33
#define MAX_POWER_MILLIAMPS 3000
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

unsigned long tPulse = 0;
unsigned long tCaso = 0;
unsigned long dT = 0;
float brightVal = 0;
bool direction = true;
float steps = 2;

int state = 0;
bool btnEn = false;
unsigned long tPress = 0;
bool btnGo = false;
bool firstState = true;
uint8_t hue = 0;
int maxB = 255;
float cp10s = 0;
int caso = 0;

unsigned long tChange = 0;
bool change = false;

void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(1000);

  pinMode(btnPin, INPUT);
  EEPROM.begin(EEPROM_SIZE);

  // INIT ENCODER
  ESP32Encoder::useInternalWeakPullResistors = UP;

  for (int i = 0; i < NUM_ENC; i++) {
    init_enc(i);
  }
  encVal[0] = EEPROM.read(adds[0]);
  enc[0].setCount(encVal[0]);
  oldEnc[0] = encVal[0];

  hue = encVal[0]/4-32;
  maxB = EEPROM.read(adds[1]);
  cp10s = EEPROM.read(adds[2]);
  caso = EEPROM.read(adds[3]);
  Serial.print(hue);
  Serial.print(",");
  Serial.print(maxB);
  Serial.print(",");
  Serial.print(cp10s);
  Serial.print(",");
  Serial.print(caso);
  Serial.println();


  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_POWER_MILLIAMPS);

  FastLED.clear();
  FastLED.show();
}

void loop() {

  readEnc();

  if (btnEn) {
    if ((millis() - tPress) > 200) {
      if (digitalRead(btnPin)) {
        btnGo = true;
        btnEn = false;
        tPress = millis();
      }
    }
  } else {
    if ((millis() - tPress) > 200) {
      if (!digitalRead(btnPin)) {
        btnEn = true;
        tPress = millis();
      }
    }
  }

  if (btnGo) {
    btnGo = false;

    EEPROM.write(adds[state], encVal[0]);
    EEPROM.commit();

    state++;
    if (state > 3) {
      state = 0;
    }
    Serial.println(state);

    encVal[0] = EEPROM.read(adds[state]);

    oldEnc[0] = encVal[0];
    enc[0].setCount(encVal[0]);
  }

  if (encVal[0] != oldEnc[0]) {

    tChange = millis();
    change = true;

    if (state == 0) {
      encStep = 4;
      
      hue = encVal[0]/4-32;
      
      Serial.print(encVal[0]);
      Serial.print("-");
      Serial.println(hue);
    }
    if (state == 1) {
      encStep = 3;
      maxB = encVal[0];
    }
    if (state == 2) {
      encStep = 3;
      cp10s = encVal[0];
    }
    if (state == 3) {
      encStep = 10;
      caso = encVal[0];
    }
    oldEnc[0] = encVal[0];
  }

  pulse();

  if (change) {
    if ((millis() - tChange) > 5000) {
      change = false;
      EEPROM.write(adds[state], encVal[0]);
      EEPROM.commit();
    }
  }
}

void readEnc() {
  for (uint8_t i = 0; i < NUM_ENC; i++) {
    int e = enc[i].getCount() * encStep;
    if (e > encMax[i]) {
      encVal[i] = encMax[i];
      enc[i].setCount(encMax[i] / encStep);
    } else if (e < encMin[i]) {
      encVal[i] = encMin[i];
      enc[i].setCount(encMin[i] / encStep);
    } else {
      encVal[i] = e;
    }
  }
}


void pulse() {

  if (((millis() - tPulse) > 10) && (millis() - dT) > 50) {
    tPulse = millis();
    FastLED.clear();
    fill_solid(leds, NUM_LEDS, CHSV(hue, 255, maxB));

    if (cp10s > 0) {
      steps = cp10s * (255 * 2) / 8000;

      if ((brightVal >= 255) || (brightVal <= 0)) {
        direction = !direction;
      }

      if (direction) {
        brightVal = brightVal + steps;
      } else {
        brightVal = brightVal - steps;
      }

      if (brightVal > 255) {
        brightVal = 255;
      }
      if (brightVal < 0) {
        brightVal = 0;
      }

      FastLED.setBrightness(dim8_raw(int(brightVal)));
    } else {
      FastLED.setBrightness(dim8_raw(int(255)));
    }

    if (caso > 0) {
      long endT = map(caso, 0, 255, 3000, 150);
      long startT = map(caso, 0, 255, 1000, 50);
      long tt = random(startT, endT);
      if ((millis() - tCaso) > tt) {
        tCaso = millis();
        if (tt % 2 == 0) {
          int mH = map(caso, 0, 255, 0, -10);
          int MH = map(caso, 0, 255, 0, 10);
          fill_solid(leds, NUM_LEDS, CHSV(hue + random(mH, MH), 255, 255));
          dT = millis();
        } else {
          FastLED.clear();
          dT = millis();
        }
      }
    }

    FastLED.show();
  }
}
