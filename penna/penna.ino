
#include <AccelStepper.h>

const uint8_t pinStep = 10;
const uint8_t pinDirection = 8;
const uint8_t pinEnable = 5;

const uint8_t ledPin = 13;

const uint16_t velMin = 20;
const uint16_t velMax = 400;
const uint16_t pulseRev = 800;


AccelStepper stepper(1, pinStep, pinDirection);

void setup()
{

  digitalWrite(ledPin, HIGH);

  stepper.setMaxSpeed(200);
  stepper.setAcceleration(150);
  stepper.setEnablePin(pinEnable);

  stepper.disableOutputs();
  digitalWrite(ledPin, LOW);

  delay(2000);

  stepper.enableOutputs();
  digitalWrite(ledPin, HIGH);

  setCurrentPosition(0);

}

void loop()
{

  bounce(1,4,35);
  delay(100);
  bounce(3,2,10);
  delay(100);
  bounce(3,2,10);
  delay(100);
  bounce(2,1,15);
  down(4,5);
  delay(100);
  down(4,5);
  delay(100);
  down(4,5);
  delay(100);
  down(4,5);
  delay(100);
  up(2,10);
  delay(100);
  up(2,10);

}

void down(uint8_t velDown, uint16_t gradi) {

  velDown = map(velDown, 1, 5, velMin, velMax);
  gradi = gradi/360*pulseRev;

  stepper.setMaxSpeed(velDown);
  stepper.setAcceleration(velDown*0.8);

  stepper.runToNewPosition(gradi);

}

void up(uint8_t velUp, uint16_t gradi) {

  velUp = map(velUp, 1, 5, velMin, velMax);
  gradi = gradi/360*pulseRev;

  stepper.setMaxSpeed(velUp);
  stepper.setAcceleration(velUp*0.8);

  stepper.runToNewPosition(-gradi);

}

void bounce(uint8_t velDown, uint8_t velUp, uint16_t gradi) {

  velDown = map(velDown, 1, 5, velMin, velMax);
  velUp = map(velUp, 1, 5, velMin, velMax);
  gradi = gradi/360*pulseRev;

  stepper.setMaxSpeed(velDown);
  stepper.setAcceleration(velDown*0.8);

  stepper.runToNewPosition(gradi);

  stepper.setMaxSpeed(velUp);
  stepper.setAcceleration(velUp*0.8);

  stepper.runToNewPosition(-gradi);

}
