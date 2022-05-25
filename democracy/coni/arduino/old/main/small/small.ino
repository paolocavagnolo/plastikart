#include <SoftwareSerial.h>
#include <AccelStepper.h>

#define pinRX 11
#define pinTX 12

//MOTORE STRETTO 
#define pinStep_A 4        //bianco
#define pinDirection_A 5   //giallo
#define pinSens_A A2

//MOTORE LARGO
#define pinStep_B 9         //bianco
#define pinDirection_B 10   //giallop
#define pinSens_B A0

#define RE 6
#define DE 7

#define MAXSPEED 6000
#define MAXACC 4000

SoftwareSerial mySerial(pinRX, pinTX);
AccelStepper stepper_A(1, pinStep_A, pinDirection_A);
AccelStepper stepper_B(1, pinStep_B, pinDirection_B);

void setup() {
  mySerial.begin(4800);

  stepper_A.setMaxSpeed(MAXSPEED);
  stepper_B.setMaxSpeed(MAXSPEED);
  stepper_A.setAcceleration(MAXACC);
  stepper_B.setAcceleration(MAXACC);

  //200 step per rev  (motor)
  //1600 pulse per rev (driver)
  pinMode(pinSens_A, INPUT_PULLUP);
  pinMode(pinSens_B, INPUT_PULLUP);

  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);

  //Serial.begin(9600);

  //zerosA();
  //zerosB();
  //zerosC();
}

long posA = 0;
long posB = 0;

uint32_t velA = 1000;
uint32_t velB = 1000;

uint32_t dataIn = 0;

void loop() {
  if (mySerial.available()) {
    dataIn = mySerial.parseInt();
    if (dataIn < 1000000) {
      posA += dataIn - 500000;
      //Serial.print("posA");
      //Serial.println(posA);
    }
    else if ((dataIn >= 1000000) && (dataIn < 2000000)) {
      velA = dataIn - 1500000;
      stepper_A.setMaxSpeed(velA);
      stepper_A.setAcceleration(velA - velA / 4);
      //Serial.print("velA");
      //Serial.println(velA);
    }
    else if ((dataIn >= 2000000) && (dataIn < 3000000)) {
      posB += dataIn - 2500000;
      //Serial.print("posB");
      //Serial.println(posB);
    }
    else if ((dataIn >= 3000000) && (dataIn < 4000000)) {
      velB = dataIn - 3500000;
      stepper_B.setMaxSpeed(velB);
      stepper_B.setAcceleration(velB - velB / 4);
      //Serial.print("velB");
      //Serial.println(velB);
    }
    else if ((dataIn >= 4000000) && (dataIn < 5000000)) {
      zeros_A();
    }
    else if ((dataIn >= 5000000) && (dataIn < 6000000)) {
      zeros_B();
    }
    else if ((dataIn >= 15000000) && (dataIn < 16000000)) {
      stepper_A.setCurrentPosition(posA);
      stepper_B.setCurrentPosition(posB);
    }
    else if ((dataIn >= 16000000) && (dataIn < 17000000)) {
      posA = dataIn - 16500000;
    }
    else if ((dataIn >= 17000000) && (dataIn < 18000000)) {
      posB = dataIn - 17500000;
    }

    stepper_A.moveTo(posA);
    stepper_B.moveTo(posB);
  }
  stepper_A.run();
  stepper_B.run();
}

void zeros_A() {
  
  long valPos = 0;

  stepper_A.setMaxSpeed(6000);
  stepper_A.setAcceleration(2000);
  posA += 100800;
  stepper_A.moveTo(posA);
  while (stepper_A.distanceToGo() > 0) {
    if (!digitalRead(pinSens_A)) {
      stepper_A.setCurrentPosition(posA);
    }
    stepper_A.run();
  }
  stepper_A.setCurrentPosition(0);
  posA = 0;
  
  
}

void zeros_B() {

  long valPos = 0;

  stepper_B.setMaxSpeed(6000);
  stepper_B.setAcceleration(2000);
  posB += 100800;
  stepper_B.moveTo(posB);
  while (stepper_B.distanceToGo() > 0) {
    if (!digitalRead(pinSens_B)) {
      stepper_B.setCurrentPosition(posB);
    }
    stepper_B.run();
  }
  stepper_B.setCurrentPosition(47600);
  posB = 47600;

}

