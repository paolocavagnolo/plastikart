// Gufo v2
// 22/07/2024

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
#define startPin CONTROLLINO_A0

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

  digitalWrite(stepEnable, HIGH);
  
}

bool ggo = false;
unsigned long tt = 0;

void loop() {

  if (!digitalRead(startPin)) {

    digitalWrite(stepEnable, HIGH);
    delay(100);

  } else {

    digitalWrite(stepEnable, LOW);

    stepper.setMaxSpeed(100);
    stepper.setAcceleration(100);
    stepper.moveTo(340);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(2000);

    stepper.setMaxSpeed(70);
    stepper.setAcceleration(70);
    stepper.moveTo(700);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(2000);

    stepper.setMaxSpeed(100);
    stepper.setAcceleration(100);
    stepper.moveTo(300);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(2000);


    stepper.setMaxSpeed(50);
    stepper.setAcceleration(50);
    while (!digitalRead(esPin)) {

      stepper.moveTo(-10000);
      stepper.run();

    }
    stepper.setCurrentPosition(0);

    delay(4000);

  }

}
