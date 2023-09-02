#include <Controllino.h>
#include <AccelStepper.h>

// PIN ON THE DRIVER
// 1  2  3  4
// ON ON ON OFF (very small current)
// 5  6   7  8
// ON OFF ON ON (800 step per rev)

#define stepPulse CONTROLLINO_D0
#define stepDir CONTROLLINO_D1
#define stepEnable CONTROLLINO_D2

#define esPin CONTROLLINO_A1

AccelStepper stepper(AccelStepper::DRIVER, stepPulse, stepDir);
void setup() {

  pinMode(stepEnable, OUTPUT);
  digitalWrite(stepEnable, LOW);

  stepper.setMaxSpeed(100);
  stepper.setAcceleration(100);

  while (!digitalRead(esPin)) {

    stepper.moveTo(-10000);
    stepper.run();

  }

  delay(1000);

  stepper.setCurrentPosition(0);

  stepper.setMaxSpeed(700);
  stepper.setAcceleration(700);

  stepper.moveTo(370);

  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  digitalWrite(stepEnable, HIGH);
  

}

bool ggo = false;
unsigned long tt = 0;

void loop() {

  if ((millis() - tt) > (60000)) {
    tt = millis();
    ggo = true;
  }

  if (ggo) {
    digitalWrite(stepEnable, LOW);

    stepper.setMaxSpeed(200);
    stepper.setAcceleration(200);
    stepper.moveTo(10);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(2000);

    stepper.setMaxSpeed(500);
    stepper.setAcceleration(500);
    stepper.moveTo(500);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(500);


    stepper.setMaxSpeed(300);
    stepper.setAcceleration(300);
    stepper.moveTo(700);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(2000);

    stepper.setMaxSpeed(600);
    stepper.setAcceleration(600);
    stepper.moveTo(300);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(2000);


    stepper.setMaxSpeed(200);
    stepper.setAcceleration(200);
    while (!digitalRead(esPin)) {

      stepper.moveTo(-10000);
      stepper.run();

    }
    stepper.setCurrentPosition(0);

    delay(4000);

    stepper.setMaxSpeed(200);
    stepper.setAcceleration(200);
    stepper.moveTo(370);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(2000);
    ggo = false;

  }
  else {
    digitalWrite(stepEnable, HIGH);
    delay(100);
  }

}
