#include <SoftwareSerial.h>
#include <AccelStepper.h>


const uint8_t stepPulse = 4; //11
const uint8_t stepDir = 5;   //12
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


  ss.begin(57600);
  Serial.begin(9600);

  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(2000);
  stepper.setCurrentPosition(215);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

}

long dt = 0;
bool dd = true;


char inByte;
int pos = 0;

bool go = false;
bool zero = false;
bool man = false;
bool eend = false;

bool first = false;

int mouth = 0;
int old_mouth = 0;

int pp=0;

void loop() {
  // put your main code here, to run repeatedly:
  if (ss.available()>1) {
    inByte = ss.read();

    if (inByte == 'k') {
      inByte = ss.read();
      if (inByte == 'K') {
        pos = ss.parseInt();
        
        if (!first) {
          go = true;
          first = true;
          stepper.setMaxSpeed(400);
          stepper.setAcceleration(1000);
      
          stepper.moveTo(0);

          stepper.setMaxSpeed(7000);
          stepper.setAcceleration(10000);
        }
      }   
    }
    else if (inByte == 'z') {
      inByte = ss.read();
      if (inByte == 'Z') {
        mouth = ss.parseInt();
        digitalWrite(13,mouth);
      }  
    }
    else if (inByte == 'e') {
      inByte = ss.read();
      if (inByte == 'E') {
        go = false;
        first = false;
        eend = true;
        Serial.println("FINE");
        
      } 
    }
    else if (inByte == 'f') {
      inByte = ss.read();
      if (inByte == 'F') {
        zero = true;
        Serial.println("ZERO");
      } 
    } 
    else if (inByte == 'm') {
      inByte = ss.read();
      if (inByte == 'M') {
        man = true;
        Serial.println("TEST");
      } 
    }
  }


  if (go) { 

    pp = (pos-head_min)/7.782;

    if (pp < 0) {
      pp = 0;
    }
    stepper.moveTo(pp);
    stepper.run();
    

  }
  else {
    if (zero) {
      stepper.setMaxSpeed(400);
      stepper.setAcceleration(1000);
    
      stepper.moveTo(0);

      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      stepper.setMaxSpeed(7000);
      stepper.setAcceleration(10000);
      //stepper.setCurrentPosition(215);
      zero = false;
    }
    else if (man) {
      stepper.setMaxSpeed(700);
      stepper.setAcceleration(1000);
      
      stepper.moveTo(200);

      digitalWrite(13,HIGH);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      stepper.moveTo(0);
      digitalWrite(13,LOW);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }

      stepper.setMaxSpeed(7000);
      stepper.setAcceleration(10000);
      man = false;
    }
    else if (eend) {
      stepper.moveTo(215);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      eend = false;
    }

  }
    
}
