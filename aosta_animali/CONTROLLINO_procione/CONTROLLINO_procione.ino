#include <Controllino.h>
#include <AccelStepper.h>

#define stepPulse CONTROLLINO_D0
#define stepDir CONTROLLINO_D2
#define stepEnable CONTROLLINO_D1

#define dcPin CONTROLLINO_D5

#define esPin CONTROLLINO_A1
#define startPin CONTROLLINO_A0

AccelStepper stepper(AccelStepper::DRIVER, stepPulse, stepDir);
void setup() {

  pinMode(stepEnable,OUTPUT);
  digitalWrite(stepEnable,LOW);

  pinMode(dcPin, OUTPUT);
  digitalWrite(dcPin, LOW);

  
  pinMode(CONTROLLINO_D6,OUTPUT);
  digitalWrite(CONTROLLINO_D6,LOW);

  stepper.setMaxSpeed(200);
  stepper.setAcceleration(400);

  while (digitalRead(esPin)) {
    
    stepper.moveTo(-10000);
    stepper.run();
    
  }
  
  stepper.setCurrentPosition(0);

  digitalWrite(CONTROLLINO_D6,LOW);
  
}

unsigned long t = 0;
unsigned long dcT = 0;
unsigned long dcStep = 20;
uint8_t vel = 0;
bool dcDir = true;

bool start = false;

unsigned long codaT = 0;
bool codaS = false;

unsigned long testaT = 0;
uint8_t testaS = 0;

void loop() {

  if (digitalRead(startPin)) {

    if (stepper.currentPosition() != 0) {
      stepper.moveTo(0);
      while (digitalRead(esPin)) {
        stepper.moveTo(-10000);
        stepper.run();
      }
      stepper.setCurrentPosition(0);
    }
 
    stepper.setMaxSpeed(1600);
    stepper.setAcceleration(1000);
    stepper.moveTo(1500);
    while(stepper.distanceToGo() > 0) {       
      stepper.run();
    }

    delay(1000);

    digitalWrite(dcPin,HIGH);
    stepper.setMaxSpeed(400);
    stepper.setAcceleration(400);
    stepper.moveTo(2000);
    while(stepper.distanceToGo() > 0) {       
      stepper.run();
    }
    digitalWrite(dcPin,LOW);
    delay(1000);

    stepper.setMaxSpeed(3000);
    stepper.setAcceleration(1000);
    stepper.moveTo(0);
    while (digitalRead(esPin)) {
      stepper.moveTo(-10000);
      stepper.run();
    }
    stepper.setCurrentPosition(0);
    digitalWrite(dcPin,HIGH);
    delay(1000);
    digitalWrite(dcPin,LOW);

    //secondo

    stepper.setMaxSpeed(3200);
    stepper.setAcceleration(2000);
    stepper.moveTo(1000);
    while(stepper.distanceToGo() > 0) {       
      stepper.run();
    }

    
    delay(1000);
    digitalWrite(dcPin,HIGH);

    stepper.setMaxSpeed(3000);
    stepper.setAcceleration(2000);
    stepper.moveTo(1400);
    while(stepper.distanceToGo() > 0) {       
      stepper.run();
    }

    digitalWrite(dcPin,LOW);
    delay(2000);

    stepper.setMaxSpeed(800);
    stepper.setAcceleration(600);
    stepper.moveTo(0);
    while (digitalRead(esPin)) {
      stepper.moveTo(-10000);
      stepper.run();
    }
    stepper.setCurrentPosition(0);

    delay(1000);

    //terzo

    stepper.setMaxSpeed(3200);
    stepper.setAcceleration(2000);
    stepper.moveTo(1500);
    while(stepper.distanceToGo() > 0) {       
      stepper.run();
    }

    delay(1000);
    digitalWrite(dcPin,HIGH);
    stepper.setMaxSpeed(4000);
    stepper.setAcceleration(1000);
    stepper.moveTo(1800);
    while(stepper.distanceToGo() > 0) {       
      stepper.run();
    }
    digitalWrite(dcPin,LOW);

  }

  digitalWrite(dcPin,LOW);
  
 
}
