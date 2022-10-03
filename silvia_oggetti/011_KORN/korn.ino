#include <AccelStepper.h>

const uint8_t stepPulse = 10;
const uint8_t stepDir = 8;
const uint8_t stepEnable = 7;

AccelStepper stepper(1, stepPulse, stepDir);

long MAXSPEED = 3000;
long MAXACC = 1250;

const int ledPin = 13;

void setup() {
  delay(1000);

  pinMode(34, OUTPUT);
  pinMode(27, INPUT_PULLUP);


  // Set led pin as output pin
  pinMode ( ledPin, OUTPUT );
  //Serial.begin(500000);

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);

  if (!digitalRead(27)) {
    MAXSPEED = MAXSPEED * 4;
    MAXACC = MAXACC * 4;
  }

  stepper.setMaxSpeed(MAXSPEED);
  stepper.setAcceleration(MAXACC);
  stepper.setCurrentPosition(0);

  digitalWrite(stepEnable, LOW);

  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(1000);

}

uint8_t j = 0;
unsigned long dt = 0;
uint16_t x[] = {100,250,400,600,800};

void viaggiaLento(uint16_t durata) {

  stepper.setMaxSpeed(250);
  stepper.setAcceleration(25);

  unsigned long dvl = millis();

  while ((millis() - dvl) < durata) {
  
    stepper.move(200);
    stepper.run();
  }
  
  
}



void sprint(uint16_t durata) {

  stepper.setCurrentPosition(0);

  stepper.setMaxSpeed(3200);
  stepper.setAcceleration(100);

  unsigned long dvl = millis();
  int x=100;

  while ((millis() - dvl) < durata) {
  
    stepper.moveTo(x);

    if (stepper.distanceToGo() == 0) {
      x = random(0,800);  
      delay(1000);
    }
    
    stepper.run();
  
  }
  
  
}

void sprintVeloci(uint16_t durata) {

  stepper.setCurrentPosition(0);

  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(5000);

  unsigned long dvl = millis();
  int x=100;

  while ((millis() - dvl) < durata) {
  
    stepper.moveTo(x);

    if (stepper.distanceToGo() == 0) {
      x = random(500,1600);  
      delay(250);
    }
    
    stepper.run();
  
  }
  
  
}


void bounce(uint16_t durata) {

  stepper.setMaxSpeed(7000);
  stepper.setAcceleration(3000);

  unsigned long dvl = millis();
  
  while ((millis() - dvl) < durata) {
  
    stepper.move(1000);
    
    stepper.run();
  
  }
  
  
}


void loop()
{

  
  viaggiaLento(9000);
  sprint(7000);
  bounce(7000);
  sprintVeloci(10000);

  digitalWrite(stepEnable, HIGH);
  delay(2000);
  digitalWrite(stepEnable, LOW);

}
