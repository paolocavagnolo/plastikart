// CIAO MICHELE, QUESTE LE 2 VARIABILI CHE PUOI CONTROLLARE:
#define TIME_ZERO 12  //secondi
long LIM_UPP = 200;   // 200 sono 45 gradi

// 496 - Gatto / Pedale
// 493 - Asta 1
// 494 - Asta 2
// 495 - Asta 3
const int startChannel = 496;

///////////////////////////////////////////////////////////////
// DA QUI IN POI PRIMA DI CAMBIARE CHIEDIMI
//////////////////////////////////////////////////////////////

#include <EEPROM.h>

#define E_ADD 100

#include "FastAccelStepper.h"

#define dirPinStepper 9
#define enablePinStepper 10
#define stepPinStepper 8

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

#include <DMXSerial.h>

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

void setup() {

  Serial.begin(9600);
  delay(200);

  long upp_buffer = 0;
  EEPROM.get(E_ADD, upp_buffer);

  if ((upp_buffer > 0) && (upp_buffer < 3200)) {
    LIM_UPP = upp_buffer;
  } else {
    EEPROM.put(E_ADD, LIM_UPP);
  }

  DMXSerial.init(DMXReceiver);
  delay(200);

  engine.init();
  stepper = engine.stepperConnectToPin(stepPinStepper);
  delay(100);

  // INITIAL ZERO

  // init motor
  stepper->setDirectionPin(dirPinStepper, true, 100);
  stepper->setEnablePin(enablePinStepper);
  stepper->enableOutputs();

  // set speed / acc
  stepper->setSpeedInUs(20000);
  stepper->setAcceleration(7000);
  stepper->setCurrentPosition(LIM_LOW);

  // enable motor
  stepper->enableOutputs();

  // start run backward
  stepper->runBackward();

  // wait for the signal
  unsigned long tZ = millis();
  while ((millis() - tZ) < TIME_ZERO * 1000) {};

  // stop
  stepper->stopMove();
  tZ = millis();
  while ((millis() - tZ) < 1000) {};

  // set position to 0
  stepper->setCurrentPosition(LIM_LOW);
  tZ = millis();
  while ((millis() - tZ) < 1000) {};

  // move forward
  stepper->runForward();
  tZ = millis();
  while ((millis() - tZ) < 200) {};
  stepper->stopMove();

  // set position to 0
  stepper->setCurrentPosition(LIM_LOW);

  if ((analogRead(BTN_A) < 100) && (analogRead(BTN_B) < 100)) {

    unsigned long tLoopBeat = 0;
    unsigned long tLoopBack = 0;

    bool beat = true;

    // INFINITE TEST LOOP

    stepper->setSpeedInUs(50);
    stepper->setAcceleration(7000);

    while (true) {

      if (beat) {
        if ((millis() - tLoopBack) > 2000) {
          tLoopBeat = millis();
          stepper->setAcceleration(150000);
          stepper->applySpeedAcceleration();
          delay(10);
          stepper->moveTo(LIM_UPP);
          beat = false;
        }
      } else {
        if ((millis() - tLoopBeat) > 1000) {
          tLoopBack = millis();
          stepper->setAcceleration(7000);
          stepper->applySpeedAcceleration();
          delay(10);
          stepper->moveTo(LIM_LOW);
          beat = true;
        }
      }
    }
  }

  stepper->setSpeedInUs(50);
  stepper->setAcceleration(7000);

  // PER ENTRARE NEL LOOP IL SEGNALE DMX DEVE ESSERE 0

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
        stepper->setAcceleration(150000);
      } else if (dmxVal == 0) {
        stepper->setAcceleration(50000);
      } else {
        stepper->setAcceleration(7000);
      }
      stepper->applySpeedAcceleration();
    }
  }

  if (btnEn) {

    if (!fB_A) {
      if ((millis() - dbB_A) > 200) {
        if (analogRead(BTN_A) < 100) {
          fB_A = true;
          dbB_A = millis();

          stepper->setAcceleration(1000);
          stepper->applySpeedAcceleration();
          delay(10);
          stepper->moveTo(LIM_UPP);
        }
      }
    } else {
      if ((millis() - dbB_A) > 200) {
        if (analogRead(BTN_A) > 1000) {
          fB_A = false;
          dbB_A = millis();

          stepper->setAcceleration(1000);
          stepper->applySpeedAcceleration();
          delay(10);
          stepper->moveTo(LIM_LOW);
        }
      }
    }

    if (!fB_B) {
      if ((millis() - dbB_B) > 200) {
        if (analogRead(BTN_B) < 100) {
          fB_B = true;
          dbB_B = millis();

          stepper->setAcceleration(150000);
          stepper->applySpeedAcceleration();
          delay(10);
          stepper->moveTo(LIM_UPP);
        }
      }
    } else {
      if ((millis() - dbB_B) > 200) {
        if (analogRead(BTN_B) > 1000) {
          fB_B = false;
          dbB_B = millis();

          stepper->setAcceleration(50000);
          stepper->applySpeedAcceleration();
          delay(10);
          stepper->moveTo(LIM_LOW);
        }
      }
    }

  } else {

    stepper->moveTo(map(dmxVal, 0, 255, LIM_LOW, LIM_UPP));
  }
}
