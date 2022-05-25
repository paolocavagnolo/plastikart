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
    
    stepper.moveTo(10000);
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

    scatto_s();
    delay(2000);
    coda(1);
    scatto_s();
    scatto_m();
    scatto_s();
    scatto_m();
    scatto_s();
    scatto_g();
    delay(2000);
    scatto_g();
    delay(3000);
    scatto_g();
    scatto_g();
    delay(300);
    scatto_g();
    digitalWrite(dcPin,HIGH);
    delay(500);
    digitalWrite(dcPin,LOW);
    scatto_s();
    scatto_g();
    scatto_s();
    scatto_g();
    delay(2000);
    scatto_g();
    delay(2000);
    

  }

  digitalWrite(dcPin,LOW);
  
 
}

void coda(int i) {
  for (int j=0; j<i; j++) {
  digitalWrite(dcPin,HIGH);
    delay(500);
    digitalWrite(dcPin,LOW);
  }
}

void scatto_g() {
  
  while (digitalRead(esPin)) {  
    stepper.moveTo(10000);
    stepper.run();
  }
  
  stepper.setCurrentPosition(0);
  //digitalWrite(dcPin, HIGH);
  stepper.setMaxSpeed(14000);
  stepper.setAcceleration(10000);
  stepper.moveTo(-100);
  while(stepper.distanceToGo() < 0) {       
    stepper.run(); 
  } 
  //digitalWrite(dcPin, LOW);

  while (digitalRead(esPin)) {  
    stepper.moveTo(10000);
    stepper.run();
  }
  
  stepper.setCurrentPosition(0);
}

void scatto_s() {
  //digitalWrite(dcPin, HIGH);
  stepper.setMaxSpeed(14000);
  stepper.setAcceleration(10000);
  stepper.moveTo(-300);
  while(stepper.distanceToGo() < 0) {       
    stepper.run(); 
  } 
  //digitalWrite(dcPin, LOW);

}

void scatto_m() {
  //digitalWrite(dcPin, HIGH);
  stepper.setMaxSpeed(14000);
  stepper.setAcceleration(10000);
  stepper.moveTo(-200);
  while(stepper.distanceToGo() != 0) {       
    stepper.run(); 
  } 
  //digitalWrite(dcPin, LOW);

}
