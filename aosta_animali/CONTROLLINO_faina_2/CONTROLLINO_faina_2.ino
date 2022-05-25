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

  stepper.setMaxSpeed(500);
  stepper.setAcceleration(500);

  stepper.moveTo(-500);
  while(stepper.distanceToGo() != 0) {       
    stepper.run(); 
  }

  while (digitalRead(esPin)) {
    
    stepper.moveTo(100000);
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

    scatto(2000,-500);
    delay(1000);
    
    coda(1);
    
    giu(2000);
    delay(1000);

    scatto(6000,-500);
    giu(6000);
    delay(1000);
    
    coda(2);

    scatto(6000,-500);
    giu(3000);
    delay(1000);

    scatto(6000,-500);
    delay(2000);

    coda(2);

    giu(1000);
    

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

void giu(int sp) {

  stepper.setMaxSpeed(sp);
  stepper.setAcceleration(sp);
  
  while (digitalRead(esPin)) {  
    stepper.moveTo(10000);
    stepper.run();
  }
  
  stepper.setCurrentPosition(0);
}

void scatto(int sp, int pos) {
  //digitalWrite(dcPin, HIGH);
  stepper.setMaxSpeed(sp);
  stepper.setAcceleration(sp);
  stepper.moveTo(pos);
  while(stepper.distanceToGo() != 0) {       
    stepper.run(); 
  } 
  //digitalWrite(dcPin, LOW);
}
