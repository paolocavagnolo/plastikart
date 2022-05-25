#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include "AsyncServoLib.h"

AsyncServo asyncServo;

const uint8_t stepPulse = 11;
const uint8_t stepDir = 12;
const uint8_t stepEnable = 7;

const int head_max = 3538;
const int head_mid = 2565;
const int head_min = 1826;

AccelStepper stepper(AccelStepper::DRIVER, stepPulse, stepDir);

SoftwareSerial ss(2,3); //RX, TX

void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);

  pinMode(A0, INPUT_PULLUP);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  stepper.setEnablePin(6);


  ss.begin(38400);
  
  stepper.setMaxSpeed(7000);
  stepper.setAcceleration(10000);
  stepper.setCurrentPosition(0);

  asyncServo.Attach(9);
  asyncServo.SetOutput(500, 1500, 2500);
}#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include "AsyncServoLib.h"

AsyncServo asyncServo;

const uint8_t stepPulse = 11;
const uint8_t stepDir = 12;
const uint8_t stepEnable = 7;

const int head_max = 3538;
const int head_mid = 2565;
const int head_min = 1826;

AccelStepper stepper(AccelStepper::DRIVER, stepPulse, stepDir);

SoftwareSerial ss(2,3); //RX, TX

void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);

  pinMode(A0, INPUT_PULLUP);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  stepper.setEnablePin(6);


  ss.begin(38400);
  
  stepper.setMaxSpeed(7000);
  stepper.setAcceleration(10000);
  stepper.setCurrentPosition(0);

  asyncServo.Attach(9);
  asyncServo.SetOutput(500, 1500, 2500);
}

long dt = 0;
bool dd = true;

char inByte;
int pos = 0;

bool go = false;
bool zero = false;
bool man = false;

int mouth = 0;
int old_mouth = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (ss.available()) {
    inByte = ss.read();
    if (inByte == 'k') {
      pos = ss.parseInt();
      go = true;
    }
    else if (inByte == 'z') {
      mouth = ss.parseInt();
    }
    else if (inByte == 'e') {
      go = false;;
    }
    else if (inByte == 'f') {
      zero = true;
    }
    else if (inByte == 'm') {
      man = true;
    }
  }


  if (go) { 
    stepper.moveTo((pos-head_min)/2);
    stepper.run();
    if (mouth != old_mouth) {
      if (mouth) {
        asyncServo.write(1000);
      }
      else {
        asyncServo.write(360);
      }
      old_mouth = mouth;
    }
  }
  else {
    if (zero) {
      while (digitalRead(A0)) {
        stepper.move(-1);
        stepper.run();
      }
      stepper.setCurrentPosition(0);
      zero = false;
    }
    else if (man) {
      stepper.moveTo(900);
      asyncServo.write(900);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      stepper.moveTo(0);
      asyncServo.write(0);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      man = false;
    }
  }
    
}


long dt = 0;
bool dd = true;

char inByte;
int pos = 0;

bool go = false;
bool zero = false;
bool man = false;

int mouth = 0;
int old_mouth = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (ss.available()) {
    inByte = ss.read();
    if (inByte == 'k') {
      pos = ss.parseInt();
      go = true;
    }
    else if (inByte == 'z') {
      mouth = ss.parseInt();
    }
    else if (inByte == 'e') {
      go = false;
      Serial.println("FINE");
    }
    else if (inByte == 'f') {
      zero = true;
      Serial.println("ZERO");
    }
    else if (inByte == 'm') {
      man = true;
      Serial.println("TEST");
    }
  }


  if (go) { 
    stepper.moveTo((pos-head_min)/2);
    stepper.run();
    if (mouth != old_mouth) {
      if (mouth) {
        asyncServo.write(1000);
      }
      else {
        asyncServo.write(360);
      }
      old_mouth = mouth;
    }
  }
  else {
    if (zero) {
      while (digitalRead(A0)) {
        stepper.move(-1);
        stepper.run();
      }
      stepper.setCurrentPosition(0);
      zero = false;
    }
    else if (man) {
      stepper.moveTo(900);
      asyncServo.write(900);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      stepper.moveTo(0);
      asyncServo.write(0);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      man = false;
    }
  }
    
}
