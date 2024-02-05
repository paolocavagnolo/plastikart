// 496 - Gatto / Pedale
// 493 - Asta 1
// 494 - Asta 2
// 495 - Asta 3
#define DMX_CHANNEL 496

// 1600 E' UN GIRO DI MOTORE
// 800 MEZZO GIRO.. ETC..
#define DISTANZA 400

// 100 E' UN VALORE DI ACCELERAZIONE BASSO
// 1000 MEDIO-BASSO
// 10000 VELOCE
// 100000 VELOCISSIMO
// 200000 ULTRA
#define FAST_ACC_FWD 20000
#define FAST_ACC_BWD 10000

#define SLOW_ACC_FWD 2000
#define SLOW_ACC_BWD 1000

// PAUSA TRA UN CICLO E L'ALTRO, in millisecondi. 500 sono mezzo secondo
#define PAUSA_LOOP 500

// PAUSA BATTENDO, quando l'asta e' contro il telo. quanto tempo sta contro il telo? in millisecondi
#define PAUSA_BATT 500

/////////////////////////////////

#include <EEPROM.h>

#define E_ADD 100

#include "FastAccelStepper.h"

#define dirPinStepper 9
#define enablePinStepper 10
#define stepPinStepper 8

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

#include <DMXSerial.h>

const int startChannel = DMX_CHANNEL;

long LIM_UPP = DISTANZA;
long LIM_LOW = 0;

#define BTN_A A1
#define BTN_B A4

long dmxVal = 0;

long pos = 0;
unsigned long tDMX = 0;
unsigned long tDebug = 0;

bool btnEn = false;

bool fB_A = false;
bool fB_B = false;
unsigned long dbB_A = 0;
unsigned long dbB_B = 0;

int loop_S = 0;
bool loop_P = true;
bool loop_E = false;

unsigned long loop_T = 0;

void setup() {

  Serial.begin(9600);
  delay(200);

  //long upp_buffer = 0;
  //EEPROM.get(E_ADD, upp_buffer);

  //if ((upp_buffer > 0) && (upp_buffer < 3200)) {
  //  LIM_UPP = upp_buffer;
  //} else {
  //  EEPROM.put(E_ADD, LIM_UPP);
  //}

  DMXSerial.init(DMXReceiver);
  delay(200);

  engine.init();
  stepper = engine.stepperConnectToPin(stepPinStepper);
  delay(100);

  if (stepper) {
    stepper->setDirectionPin(dirPinStepper, true, 100);
    stepper->setEnablePin(enablePinStepper);
    stepper->enableOutputs();

    stepper->setSpeedInUs(5000);
    stepper->setAcceleration(1000);
  }

  delay(1000);
  stepper->setCurrentPosition(LIM_LOW);

  dmxVal = DMXSerial.read(startChannel);

  while (dmxVal > 0) {
    dmxVal = DMXSerial.read(startChannel);
    delay(100);
  }
}


void loop() {

  // END STOPS
  pos = stepper->getCurrentPosition();

  if ((pos > (LIM_UPP)) || (pos < (LIM_LOW))) {
    stepper->forceStop();
  }

  // DMX
  if ((millis() - tDMX) > 15) {
    tDMX = millis();

    dmxVal = DMXSerial.read(startChannel);

    if (DMXSerial.noDataSince() > 2000) {
      btnEn = true;
    } else {
      btnEn = false;
    }

    if (!btnEn) {
      if (dmxVal == 255) {
        stepper->setAcceleration(FAST_ACC_FWD);
      } else if (dmxVal == 0) {
        stepper->setAcceleration(FAST_ACC_BWD);
      } else {
        stepper->setAcceleration(SLOW_ACC_FWD);
      }
      stepper->applySpeedAcceleration();
    }
  }

  if (btnEn) {

    // CHECK BUTTONS
    if (!fB_A) {
      if ((millis() - dbB_A) > 200) {
        if (analogRead(BTN_A) < 100) {
          fB_A = true;
          dbB_A = millis();
          stepper->runForward();
        }
      }
    } else {
      if ((millis() - dbB_A) > 200) {
        if (analogRead(BTN_A) > 1000) {
          fB_A = false;
          dbB_A = millis();
          stepper->stopMove();
        }
      }
    }

    if (!fB_B) {
      if ((millis() - dbB_B) > 200) {
        if (analogRead(BTN_B) < 100) {
          fB_B = true;
          dbB_B = millis();
          stepper->runBackward();
        }
      }
    } else {
      if ((millis() - dbB_B) > 200) {
        if (analogRead(BTN_B) > 1000) {
          fB_B = false;
          dbB_B = millis();
          stepper->stopMove();
        }
      }
    }

  } else {
    stepper->moveTo(map(dmxVal, 0, 255, LIM_LOW, LIM_UPP));
  }
}
