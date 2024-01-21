#include <AccelStepper.h>

#define UART2_TX_PIN (18u)  // Pin A4
#define UART2_RX_PIN (19u)  // Pin A5

// Instantiate the Serial2 class
UART _UART2_(UART2_TX_PIN, UART2_RX_PIN);  // Makes Serial2 available on pin A4 Tx, A5 Tx

#define T 500
#define maxLong 2147483646

uint8_t btnPin[] = { A0, A1, A2, A3 };

#define LMP 12
#define LMD 13
#define LME 11

#define RMP 8
#define RMD 7
#define RME 9

#define maxSpeed 8000
#define maxAcc 1000

AccelStepper LM(AccelStepper::DRIVER, LMP, LMD);
AccelStepper RM(AccelStepper::DRIVER, RMP, RMD);

char buf[7];

int readline(int readch, char *buffer, int len) {
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\r':  // Ignore CR
        break;
      case '\n':  // Return on new-line
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len - 1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  return 0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(LME, OUTPUT);
  pinMode(RME, OUTPUT);
  digitalWrite(LME, LOW);
  digitalWrite(RME, LOW);

  Serial.begin(9600);
  Serial2.begin(115200);

  LM.setMaxSpeed(8000);
  LM.setAcceleration(1000);
  LM.setCurrentPosition(0);

  RM.setMaxSpeed(8000);
  RM.setAcceleration(1000);
  RM.setCurrentPosition(0);
}

bool fB[] = { false, false, false, false };
bool P[] = { false, false, false, false };
bool R[] = { false, false, false, false };
unsigned long dbB[] = { 0, 0, 0, 0 };

uint8_t Lspeed = 0;
uint8_t Rspeed = 0;

bool remote = false;
bool change = false;
bool firstMan = true;

int LMspeed = 0;
int RMspeed = 0;

char msg[4];

void loop() {

  LM.run();
  RM.run();

  if (readline(Serial2.read(), buf, 7) > 0) {
    if (buf[0] != 'X') {
      remote = true;
      change = true;

      msg[0] = buf[0];
      msg[1] = buf[1];
      msg[2] = buf[2];
      msg[3] = buf[3];

      sscanf(msg, "%02X%02X", &Lspeed, &Rspeed);

      LMspeed = (Lspeed - 128) * maxSpeed / 128;
      RMspeed = (Rspeed - 128) * maxSpeed / 128;

    } else {

      remote = false;
      Lspeed = 0;
      Rspeed = 0;
    }
  }

  if (remote) {
    if (change) {
      change = false;

      if (abs(Lspeed - 128) > 1) {
        LM.setMaxSpeed(LMspeed);
        LM.move(((LMspeed > 0) - (LMspeed < 0)) * maxLong);
      } else {
        LM.stop();
        LM.setCurrentPosition(0);
      }

      if (abs(Rspeed - 128) > 1) {
        RM.setMaxSpeed(RMspeed);
        RM.move(((RMspeed > 0) - (RMspeed < 0)) * maxLong);
      } else {
        RM.stop();
        RM.setCurrentPosition(0);
      }
    }
  } else {
    // check buttons
    for (uint8_t i = 0; i < 4; i++) {
      if (!fB[i]) {
        if ((millis() - dbB[i]) > 200) {
          if (analogRead(btnPin[i]) < T) {
            fB[i] = true;
            P[i] = true;
            dbB[i] = millis();
          }
        }
      } else {
        if ((millis() - dbB[i]) > 200) {
          if (analogRead(btnPin[i]) > T) {
            R[i] = true;
            fB[i] = false;
            dbB[i] = millis();
          }
        }
      }
    }

    // action if pressed
    for (uint8_t i = 0; i < 4; i++) {
      if (P[i]) {
        Serial.print("pressed ");
        Serial.println(i);
      }
      if (P[3]) {
        RM.move(maxLong);
      }
      if (P[0]) {
        RM.move(-maxLong);
      }
      if (P[1]) {
        LM.move(maxLong);
      }
      if (P[2]) {
        LM.move(-maxLong);
      }
      P[i] = false;
    }

    // action if released
    for (uint8_t i = 0; i < 4; i++) {
      if (R[i]) {
        Serial.print("released ");
        Serial.println(i);
      }
      if (R[3]) {
        RM.stop();
      }
      if (R[0]) {
        RM.stop();
      }
      if (R[2]) {
        LM.stop();
      }
      if (R[1]) {
        LM.stop();
      }
      R[i] = false;
    }
  }
}
