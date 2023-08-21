#include <Controllino.h>
#include <AccelStepper.h>

#define stepPulse CONTROLLINO_D0
#define stepDir CONTROLLINO_D2
#define stepEnable CONTROLLINO_D1

#define esPin CONTROLLINO_A1
#define startPin CONTROLLINO_A0

AccelStepper stepper(AccelStepper::DRIVER, stepPulse, stepDir);
void setup() {

  pinMode(stepEnable, OUTPUT);
  digitalWrite(stepEnable, LOW);

  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(4000);


  while (digitalRead(esPin)) {

    stepper.moveTo(100000);
    stepper.run();

  }

  stepper.setCurrentPosition(0);
  digitalWrite(stepEnable, HIGH);

}

void loop() {

  if (digitalRead(startPin)) {
    digitalWrite(stepEnable, LOW);

    scatto(2000, -6000);
    delay(1000);

    giu(2000);
    delay(1000);

    scatto(3000, -6000);
    giu(2000);
    delay(1000);

    scatto(3000, -6000);
    giu(2000);
    delay(1000);

    scatto(3000, -6000);
    delay(2000);

    giu(1000);


  }
  else {
    digitalWrite(stepEnable, HIGH);
  }


}

void giu(int sp) {
//
//  stepper.setMaxSpeed(sp);
//  stepper.setAcceleration(sp);

  while (digitalRead(esPin)) {
    stepper.moveTo(10000);
    stepper.run();
  }

  stepper.setCurrentPosition(0);
}

void scatto(int sp, int pos) {
  //digitalWrite(dcPin, HIGH);
//  stepper.setMaxSpeed(sp);
//  stepper.setAcceleration(sp);
  stepper.moveTo(pos);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

}
