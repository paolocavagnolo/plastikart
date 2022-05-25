#include <AccelStepper.h>

#define STEP 12
#define DIR 11

AccelStepper stepper1(1, STEP, DIR);
AccelStepper stepper2(1, 4, 5);

int vel;

int i = 0;

void setup() {
  //read from RS485 bus
  Serial2.begin(9600);

  //debug
  Serial.begin(9600);

  //motor
  stepper1.setMaxSpeed(1000);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.stop();
}

void loop() {
  if (Serial2.available() > 0) {
    vel = Serial2.parseInt();
    if (vel < 1024) {
      stepper1.setSpeed(vel);
      stepper1.runSpeed();
    }
    
  }
}


