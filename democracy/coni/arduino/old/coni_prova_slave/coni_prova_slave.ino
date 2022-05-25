#include <AccelStepper.h>

AccelStepper stepper(1, 2, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup() {
  stepper.setMaxSpeed(1000);
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(100.0);
  stepper.stop();
  Serial2.begin(9600);
  Serial.begin(9600);
  Serial.println("si parte");
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
}

char inc;
int vel = 0;

void loop() { // run over and over
  if (Serial2.available() > 0) {
    // read the incoming byte:
    inc = Serial2.read();
    Serial.println(inc);
    if (inc == 'a') {
      vel = abs(vel);
    }
    else if (inc == 'o') {
       vel = -1 * abs(vel);
    }
    else if ((inc == '1') || (inc == '2') || (inc == '3') || (inc == '4') || (inc == '5') || (inc == '6') || (inc == '7') || (inc == '8') || (inc == '9')) {
      vel = ((int)inc - 48) * 100;
    }
    else {
      vel = 0;
    }
    
  
  }


  stepper.setSpeed(vel);
  stepper.runSpeed();
}

