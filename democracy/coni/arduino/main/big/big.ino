#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <SerialCommand.h>

#define pinRX 11
#define pinTX 12

SoftwareSerial mySerial(pinRX, pinTX);
SerialCommand SCmd(mySerial);

//MOTORE C
#define pinStep_C 2
#define pinDirection_C 3

//MOTORE D
#define pinStep_D 4
#define pinDirection_D 5

//MOTORE E
#define pinStep_E 6
#define pinDirection_E 7

#define RE 9
#define DE 10

#define MAXSPEED 6000
#define MAXACC 4000

AccelStepper stepper_C(1, pinStep_C, pinDirection_C);
AccelStepper stepper_D(1, pinStep_D, pinDirection_D);
AccelStepper stepper_E(1, pinStep_E, pinDirection_E);

MultiStepper steppers;

long positions[3] = {0,0,0};

void setup() {


  SCmd.addCommand("g",process_command);
  SCmd.addCommand("G",Process_command);

  //C
  stepper_C.setMaxSpeed(MAXSPEED);
  stepper_C.setAcceleration(MAXACC);
  //D
  stepper_D.setMaxSpeed(MAXSPEED);
  stepper_D.setAcceleration(MAXACC);
  //E
  stepper_E.setMaxSpeed(MAXSPEED);
  stepper_E.setAcceleration(MAXACC);

  steppers.addStepper(stepper_C);
  steppers.addStepper(stepper_D);
  steppers.addStepper(stepper_E);


  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);

  mySerial.begin(4800);

}


void loop() {

  SCmd.readSerial();
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();

}

void process_command()
{
  int aNumber;
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    aNumber=atoi(arg);    // Converts a char string to an integer
    positions[0] += (long)(aNumber * 100800 / 360);
  }

  arg = SCmd.next();
  if (arg != NULL)
  {
    aNumber=atoi(arg);
    positions[1] += (long)(aNumber * 100800 / 360);
  }

  arg = SCmd.next();
  if (arg != NULL)
  {
    aNumber=atoi(arg);
    positions[2] += (long)(aNumber * 100800 / 360);
  }


}

void Process_command()
{
  int aNumber;
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    aNumber=atoi(arg);    // Converts a char string to an integer
    stepper_C.setMaxSpeed(aNumber);
    stepper_D.setMaxSpeed(aNumber);
    stepper_E.setMaxSpeed(aNumber);
  }

}
