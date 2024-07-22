// Camoscio V2
// 22/07/2024



#include <Controllino.h>
#include <AccelStepper.h>

#define stepPulse CONTROLLINO_D0
#define stepDir CONTROLLINO_D1
#define stepEnable CONTROLLINO_D2

#define esPin CONTROLLINO_A1
#define startPin CONTROLLINO_A0

AccelStepper stepper(AccelStepper::DRIVER, stepPulse, stepDir);

void setup() {

  pinMode(stepEnable, OUTPUT);

  stepper.setMaxSpeed(100);
  stepper.setAcceleration(100);

  digitalWrite(stepEnable, LOW);

  while (digitalRead(esPin)) {

    stepper.moveTo(10000);
    stepper.run();

  }

  stepper.setCurrentPosition(0);

  digitalWrite(stepEnable, HIGH);

}


void loop() {

  if (!digitalRead(startPin)) {

    digitalWrite(stepEnable, HIGH);
    delay(100);

  } else {

    digitalWrite(stepEnable, LOW);
    delay(800);

    //SU VELOCE
    stepper.setMaxSpeed(2000);
    stepper.setAcceleration(1000);
    stepper.moveTo(-180*1.9);
    while (stepper.distanceToGo() < 0) {
      stepper.run();
    }
    delay(1000);

    //GIU META
    stepper.setMaxSpeed(12000);
    stepper.setAcceleration(12000);
    stepper.moveTo(-150*1.9);
    while (stepper.distanceToGo() > 0) {
      stepper.run();
    };

    //SU VELOCE
    stepper.setMaxSpeed(12000);
    stepper.setAcceleration(12000);
    stepper.moveTo(-200*1.9);
    while (stepper.distanceToGo() < 0) {
      stepper.run();
    }

    delay(500);

    //GIU META
    stepper.setMaxSpeed(100);
    stepper.setAcceleration(100);
    stepper.moveTo(-100*1.9);
    while (stepper.distanceToGo() > 0) {
      stepper.run();
    }

    delay(3000);


    //SU VELOCE
    stepper.setMaxSpeed(12000);
    stepper.setAcceleration(12000);
    stepper.moveTo(-200*1.9);
    while (stepper.distanceToGo() < 0) {
      stepper.run();
    }


    delay(3000);

    //GIU LENTO
    stepper.setMaxSpeed(100);
    stepper.setAcceleration(40);
    while (digitalRead(esPin)) {
      stepper.moveTo(10000);
      stepper.run();
    }
    stepper.setCurrentPosition(0);

    delay(2000);

    //SU VELOCE
    stepper.setMaxSpeed(3000);
    stepper.setAcceleration(1000);
    stepper.moveTo(-180*1.9);
    while (stepper.distanceToGo() < 0) {
      stepper.run();
    }

    //GIU LENTO
    stepper.setMaxSpeed(100);
    stepper.setAcceleration(40);
    while (digitalRead(esPin)) {
      stepper.moveTo(10000);
      stepper.run();
    }
    stepper.setCurrentPosition(0);

    delay(2000);

  }
}
