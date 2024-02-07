// 496 - Gatto / Pedale
// 493 - Asta 1
// 494 - Asta 2
// 495 - Asta 3
#define DMX_CHANNEL 496

// 1600 E' UN GIRO DI MOTORE
// 800 MEZZO GIRO.. ETC..
#define DISTANZA 200

// 100 E' UN VALORE DI ACCELERAZIONE BASSO
// 1000 MEDIO-BASSO
// 10000 VELOCE
// 100000 VELOCISSIMO
// 200000 ULTRA
#define FAST_ACC_FWD 70000
#define FAST_ACC_BWD 35000

#define SLOW_ACC_FWD 1000
#define SLOW_ACC_BWD 500

#define DMX_ACC 30000

// PAUSA TRA UN CICLO E L'ALTRO, in millisecondi. 500 sono mezzo secondo
#define PAUSA_LOOP 2000

// PAUSA BATTENDO, quando l'asta e' contro il telo. quanto tempo sta contro il telo? in millisecondi
#define PAUSA_BATT 3

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
bool firstDMX = true;

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

    stepper->setSpeedInUs(50);
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

  // DMX
  if ((millis() - tDMX) > 15) {
    tDMX = millis();

    dmxVal = DMXSerial.read(startChannel);

    if (DMXSerial.noDataSince() > 2000) {
      btnEn = true;
      firstDMX = true;
    } else {
      btnEn = false;
    }

    if (firstDMX) {
      firstDMX = false;
      stepper->setAcceleration(DMX_ACC);
      stepper->applySpeedAcceleration();  
  }

  if (btnEn) {

    // CHECK BUTTONS
    if (!fB_A) {
      if ((millis() - dbB_A) > 200) {
        if (analogRead(BTN_A) < 100) {
          fB_A = true;
          loop_S = 0;
          loop_P = true;
          loop_E = false;
          dbB_A = millis();
        }
      }
    } else if (loop_S == 3) {
      if ((millis() - dbB_A) > 200) {
        if (analogRead(BTN_A) > 1000) {
          fB_A = false;
          dbB_A = millis();
        }
      }
    }

    if (!fB_B) {
      if ((millis() - dbB_B) > 200) {
        if (analogRead(BTN_B) < 100) {
          fB_B = true;
          loop_S = 0;
          loop_P = true;
          loop_E = false;
          dbB_B = millis();
        }
      }
    } else if (loop_S == 3) {
      if ((millis() - dbB_B) > 200) {
        if (analogRead(BTN_B) > 1000) {
          fB_B = false;
          dbB_B = millis();
        }
      }
    }

    // ACT SLOW
    if (fB_A) {

      if (loop_S == 0) {
        // ACCELERA FINO A DIST
        if (loop_P) {
          loop_P = false;
          loop_E = false;
          loop_T = millis();
          stepper->setAcceleration(SLOW_ACC_FWD);
          stepper->applySpeedAcceleration();
          stepper->moveTo(LIM_UPP);
        } else {
          if (stepper->isRunning() == false) {
            loop_E = true;
          }
        }

        if (loop_E) {
          loop_P = true;
          loop_S = 1;
        }

      } else if (loop_S == 1) {
        // PAUSA MINIMA
        if (loop_P) {
          loop_P = false;
          loop_E = false;
          loop_T = millis();
        } else {
          if ((millis() - loop_T) > PAUSA_BATT) {
            loop_E = true;
          }
        }

        if (loop_E) {
          loop_P = true;
          loop_S = 2;
        }

      } else if (loop_S == 2) {
        // ACCELERA FINO A 0
        if (loop_P) {
          loop_P = false;
          loop_E = false;
          loop_T = millis();
          stepper->setAcceleration(SLOW_ACC_BWD);
          stepper->applySpeedAcceleration();
          stepper->moveTo(0);
        } else {
          if (stepper->isRunning() == false) {
            loop_E = true;
          }
        }

        if (loop_E) {
          loop_P = true;
          loop_S = 3;
        }

      } else if (loop_S == 3) {
        // PAUSA LOOP
        if (loop_P) {
          loop_P = false;
          loop_E = false;
          loop_T = millis();
        } else {
          if ((millis() - loop_T) > PAUSA_LOOP) {
            loop_E = true;
          }
        }

        if (loop_E) {
          loop_P = true;
          loop_S = 0;
        }
      }
    }
    // ACT FAST
    else if (fB_B) {

      if (loop_S == 0) {
        // ACCELERA FINO A DIST
        if (loop_P) {
          loop_P = false;
          loop_E = false;
          loop_T = millis();
          stepper->setAcceleration(FAST_ACC_FWD);
          stepper->applySpeedAcceleration();
          stepper->moveTo(LIM_UPP);
        } else {
          if (stepper->isRunning() == false) {
            loop_E = true;
          }
        }

        if (loop_E) {
          loop_P = true;
          loop_S = 1;
        }

      } else if (loop_S == 1) {
        // PAUSA MINIMA
        if (loop_P) {
          loop_P = false;
          loop_E = false;
          loop_T = millis();
        } else {
          if ((millis() - loop_T) > PAUSA_BATT) {
            loop_E = true;
          }
        }

        if (loop_E) {
          loop_P = true;
          loop_S = 2;
        }

      } else if (loop_S == 2) {
        // ACCELERA FINO A 0
        if (loop_P) {
          loop_P = false;
          loop_E = false;
          loop_T = millis();
          stepper->setAcceleration(FAST_ACC_BWD);
          stepper->applySpeedAcceleration();
          stepper->moveTo(0);
        } else {
          if (stepper->isRunning() == false) {
            loop_E = true;
          }
        }

        if (loop_E) {
          loop_P = true;
          loop_S = 3;
        }

      } else if (loop_S == 3) {
        // PAUSA LOOP
        if (loop_P) {
          loop_P = false;
          loop_E = false;
          loop_T = millis();
        } else {
          if ((millis() - loop_T) > PAUSA_LOOP) {
            loop_E = true;
          }
        }

        if (loop_E) {
          loop_P = true;
          loop_S = 0;
        }
      }
    }

  } else {
    stepper->moveTo(map(dmxVal, 0, 255, LIM_LOW, LIM_UPP));
  }
}
