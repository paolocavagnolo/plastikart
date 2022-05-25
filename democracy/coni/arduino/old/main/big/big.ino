#include <SoftwareSerial.h>
#include <AccelStepper.h>

#define pinRX 11
#define pinTX 12

//MOTORE C 
#define pinStep_C 2        
#define pinDirection_C 3   
#define pinSens_C A0

//MOTORE D
#define pinStep_D 4         
#define pinDirection_D 5   
#define pinSens_D A2

//MOTORE E
#define pinStep_E 6         
#define pinDirection_E 7   
#define pinSens_E A5

#define RE 9
#define DE 10

#define MAXSPEED 6000
#define MAXACC 4000

SoftwareSerial mySerial(pinRX, pinTX);
AccelStepper stepper_C(1, pinStep_C, pinDirection_C);
AccelStepper stepper_D(1, pinStep_D, pinDirection_D);
AccelStepper stepper_E(1, pinStep_E, pinDirection_E);

void setup() {
  mySerial.begin(4800);

  //C
  stepper_C.setMaxSpeed(MAXSPEED);
  stepper_C.setAcceleration(MAXACC);
  //D
  stepper_D.setMaxSpeed(MAXSPEED);
  stepper_D.setAcceleration(MAXACC);
  //E
  stepper_E.setMaxSpeed(MAXSPEED);
  stepper_E.setAcceleration(MAXACC);


  //200 step per rev  (motor)
  //1600 pulse per rev (driver)
  pinMode(pinSens_C, INPUT_PULLUP);
  pinMode(pinSens_D, INPUT_PULLUP);
  pinMode(pinSens_E, INPUT_PULLUP);

  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);

  //Serial.begin(9600);

  //zerosC();
  //zerosD();
  //zerosE();
}

long posC = 0;
long posD = 0;
long posE = 0;

uint32_t velC = 1000;
uint32_t velD = 1000;
uint32_t velE = 1000;

uint32_t dataIn = 0;

void loop() {

  if (mySerial.available()) {
    dataIn = mySerial.parseInt();
    if ((dataIn >= 6000000) && (dataIn < 7000000)) {
      posC += dataIn - 6500000;
      //Serial.print("posC");
      //Serial.println(posC);
    }
    else if ((dataIn >= 7000000) && (dataIn < 8000000)) {
      velC = dataIn - 7500000;
      stepper_C.setMaxSpeed(velC);
      stepper_C.setAcceleration(velC - velC / 4);
      //Serial.print("velC");
      //Serial.println(velC);
    }
    else if ((dataIn >= 8000000) && (dataIn < 9000000)) {
      posD += dataIn - 8500000;
      //Serial.print("posD");
      //Serial.println(posD);
    }
    else if ((dataIn >= 9000000) && (dataIn < 10000000)) {
      velD = dataIn - 9500000;
      stepper_D.setMaxSpeed(velD);
      stepper_D.setAcceleration(velD - velD / 4);
      //Serial.print("velD");
      //Serial.println(velD);
    }
    else if ((dataIn >= 10000000) && (dataIn < 11000000)) {
      posE += dataIn - 10500000;
      //Serial.print("posE");
      //Serial.println(posE);
    }
    else if ((dataIn >= 11000000) && (dataIn < 12000000)) {
      velE = dataIn - 11500000;
      stepper_E.setMaxSpeed(velE);
      stepper_E.setAcceleration(velE - velE / 4);
      //Serial.print("velE");
      //Serial.println(velE);
    }
    else if ((dataIn >= 12000000) && (dataIn < 13000000)) {
      zeros_C();
    }
    else if ((dataIn >= 13000000) && (dataIn < 14000000)) {
      zeros_D();
    }
    else if ((dataIn >= 14000000) && (dataIn < 15000000)) {
      zeros_E();
    }
    else if ((dataIn >= 15000000) && (dataIn < 16000000)) {
      stepper_C.setCurrentPosition(posC);
      stepper_D.setCurrentPosition(posD);
      stepper_E.setCurrentPosition(posE);
    }
    else if ((dataIn >= 18000000) && (dataIn < 19000000)) {
      posC = dataIn - 18500000;
    }
    else if ((dataIn >= 19000000) && (dataIn < 20000000)) {
      posD = dataIn - 19500000;
    }
    else if ((dataIn >= 20000000) && (dataIn < 21000000)) {
      posD = dataIn - 20500000;
    }

    stepper_C.moveTo(posC);
    stepper_D.moveTo(posD);
    stepper_E.moveTo(posE);
  }
  stepper_C.run();
  stepper_D.run();
  stepper_E.run();
}

void zeros_C() {
  
  long valPos = 0;

  stepper_C.setMaxSpeed(6000);
  stepper_C.setAcceleration(2000);
  posC += 100800;
  stepper_C.moveTo(posC);
  while (stepper_C.distanceToGo() > 0) {
    if (!digitalRead(pinSens_C)) {
      stepper_C.setCurrentPosition(posC);
    }
    stepper_C.run();
  }
  stepper_C.setCurrentPosition(0);
  posC = 0;
  
  
}

void zeros_D() {

  long valPos = 0;

  stepper_D.setMaxSpeed(6000);
  stepper_D.setAcceleration(2000);
  posD += 100800;
  stepper_D.moveTo(posD);
  while (stepper_D.distanceToGo() > 0) {
    if (!digitalRead(pinSens_D)) {
      stepper_D.setCurrentPosition(posD);
    }
    stepper_D.run();
  }
  stepper_D.setCurrentPosition(0);
  posD = 0;

}

void zeros_E() {

  long valPos = 0;

  stepper_E.setMaxSpeed(6000);
  stepper_E.setAcceleration(2000);
  posE += 100800;
  stepper_E.moveTo(posE);
  while (stepper_E.distanceToGo() > 0) {
    if (!digitalRead(pinSens_E)) {
      stepper_E.setCurrentPosition(posE);
    }
    stepper_E.run();
  }
  stepper_E.setCurrentPosition(0);
  posE = 0;

}

