#include <Controllino.h>
#include <AccelStepper.h>

#define stepPulse CONTROLLINO_D0
#define stepDir CONTROLLINO_D1
#define stepEnable CONTROLLINO_D2

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

  stepper.setMaxSpeed(800);
  stepper.setAcceleration(300);

  while (digitalRead(esPin)) {
    
    stepper.moveTo(-10000);
    stepper.run();
    
  }

  stepper.setCurrentPosition(0);

  stepper.setMaxSpeed(400);
  stepper.setAcceleration(1000);
  stepper.moveTo(-3000);
  while(stepper.distanceToGo() != 0) {       
    stepper.run(); 
  } 
  
  

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

    stepper.setMaxSpeed(400);
    stepper.setAcceleration(4000);
    stepper.moveTo(0);
    while(stepper.distanceToGo() != 0) {       
      stepper.run(); 
    } 

    delay(2000);

    stepper.setMaxSpeed(1200);
    stepper.setAcceleration(4000);
    stepper.moveTo(1500);
    while(stepper.distanceToGo() != 0) {       
      stepper.run(); 
    } 

    delay(500);


    stepper.setMaxSpeed(200);
    stepper.setAcceleration(4000);
    stepper.moveTo(2500);
    while(stepper.distanceToGo() != 0) {       
      stepper.run(); 
    } 

    delay(2000);

    stepper.setMaxSpeed(300);
    stepper.setAcceleration(4000);
    stepper.moveTo(3500);
    while(stepper.distanceToGo() != 0) {       
      stepper.run(); 
    } 

    delay(2000);

    stepper.setMaxSpeed(3000);
    stepper.setAcceleration(2000);
    stepper.moveTo(600);
    while(stepper.distanceToGo() != 0) {       
      stepper.run(); 
    } 

    delay(4000);

    stepper.setMaxSpeed(1200);
    stepper.setAcceleration(4000);
    while (digitalRead(esPin)) {
    
      stepper.moveTo(-10000);
      stepper.run();
      
    }

    delay(4000);

    stepper.setMaxSpeed(300);
    stepper.setAcceleration(4000);
    stepper.moveTo(-3000);
    while(stepper.distanceToGo() != 0) {       
      stepper.run(); 
    } 

    delay(2000);

  }

  
 
}
