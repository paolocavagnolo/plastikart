// ARDUINO UNO R3

#include "ppm.h"
#include "RunningAverage.h"

RunningAverage LM(40);
RunningAverage RM(40);

#define DT 920

// PPM channel layout (update for your situation)
#define THROTTLE 1
#define ROLL 2
#define PITCH 3
#define YAW 4
#define SWITCH3WAY_1 5
#define POT 6

// Loop interval time
long interval = 100;
unsigned long previousMillis = 0;

void setup() {
  // Start the serial port to display data
  Serial.begin(115200);

  // Start the PPM function on PIN 2
  ppm.begin(2, false);
}

short throttle;
short roll;
short pitch;
short yaw;
short switch3way_1;
short pot;

int S = 0;
// -1 - F/S
// 0 - manual
// 1 - fwd
// 2 - bwd

int Lspeed = 0;
int Rspeed = 0;
int Lstraight = 0;
int Rstraight = 0;
int Lturn = 0;
int Rturn = 0;

char old_S;
int ALspeed;
int ARspeed;
int old_Lspeed;
int old_Rspeed;

bool change = false;

void loop() {
  // Interval at which the PPM is updated

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Acquiring all the channels values
    throttle = ppm.read_channel(THROTTLE);
    roll = ppm.read_channel(ROLL);
    pitch = ppm.read_channel(PITCH);
    yaw = ppm.read_channel(YAW);
    switch3way_1 = ppm.read_channel(SWITCH3WAY_1);
    pot = ppm.read_channel(POT);

    if ((throttle < DT)) {
      S = -1;
    } else {
      if (switch3way_1 < 1200) {
        S = 1;
      } else if (switch3way_1 > 1800) {
        S = 2;
      } else {
        S = 0;
      }
    }

    if (S == -1) {
      Serial.println("X");
      interval = 1000;
    } else {
      interval = 40;
      if (S == 0) {

        if (pitch > 1600) {
          Lstraight = map(pitch, 1600, 2012, 129, 255);
          Rstraight = map(pitch, 1600, 2012, 129, 255);
        } else if (pitch < 1400) {
          Lstraight = map(pitch, 1400, 988, 128, 0);
          Rstraight = map(pitch, 1400, 988, 128, 0);
        } else {
          Lstraight = 128;
          Rstraight = 128;
        }

        if (roll > 1600) {
          Lturn = -map(roll, 1600, 2012, 0, 128);
          Rturn = map(roll, 1600, 2012, 0, 128);
        } else if (roll < 1400) {
          Lturn = map(roll, 1400, 988, 0, 128);
          Rturn = -map(roll, 1400, 988, 0, 128);
        } else {
          Lturn = 0;
          Rturn = 0;
        }
      }

      if (S == 1) {
        uint8_t v = map(pot, 988, 2012, 0, 127);
        Lstraight = 128 + v;
        Rstraight = 128 - v;

        if (roll > 1600) {
          Rturn = map(roll, 1600, 2012, 0, 48);
        } else if (roll < 1400) {
          Lturn = -map(roll, 1400, 988, 0, 48);
        } else {
          Lturn = 0;
          Rturn = 0;
        }
      }

      if (S == 2) {
        uint8_t v = map(pot, 988, 2012, 0, 127);
        Rstraight = 128 + v;
        Lstraight = 128 - v;

        if (roll > 1600) {
          Rturn = -map(roll, 1600, 2012, 0, 48);
        } else if (roll < 1400) {
          Lturn = map(roll, 1400, 988, 0, 48);
        } else {
          Lturn = 0;
          Rturn = 0;
        }
      }

      Lspeed = Lstraight + Lturn;
      Rspeed = Rstraight + Rturn;

      if (Lspeed > 255) {
        Lspeed = 255;
      } else if (Lspeed < 0) {
        Lspeed = 0;
      }

      if (Rspeed > 255) {
        Rspeed = 255;
      } else if (Rspeed < 0) {
        Rspeed = 0;
      }

      LM.addValue(Lspeed);
      RM.addValue(Rspeed);

      ALspeed = LM.getAverage();
      ARspeed = RM.getAverage();

      char buffer[5];
      sprintf(buffer, "%02X%02X", ALspeed, ARspeed);
      Serial.println(buffer);
    }
  }
}
