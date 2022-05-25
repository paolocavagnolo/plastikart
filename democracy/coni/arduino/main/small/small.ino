#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <SerialCommand.h>

#define pinRX 11
#define pinTX 12

SoftwareSerial mySerial(pinRX, pinTX);
SerialCommand SCmd(mySerial);

//MOTORE STRETTO
#define pinStep_A 4        //bianco
#define pinDirection_A 5   //giallo

//MOTORE LARGO
#define pinStep_B 9         //bianco
#define pinDirection_B 10   //giallop

#define RE 6
#define DE 7

#define MAXSPEED 6000
#define MAXACC 4000

AccelStepper stepper_A(1, pinStep_A, pinDirection_A);
AccelStepper stepper_B(1, pinStep_B, pinDirection_B);

MultiStepper steppers;

long positions[2] = {0,0};

void setup() {

  SCmd.addCommand("p",process_command);
  SCmd.addCommand("P",Process_command);

  stepper_A.setMaxSpeed(MAXSPEED);
  stepper_B.setMaxSpeed(MAXSPEED);
  stepper_A.setAcceleration(MAXACC);
  stepper_B.setAcceleration(MAXACC);

  steppers.addStepper(stepper_A);
  steppers.addStepper(stepper_B);

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


}

void Process_command()
{
  int aNumber;
  char *arg;

  arg = SCmd.next();
  if (arg != NULL)
  {
    aNumber=atoi(arg);    // Converts a char string to an integer
    stepper_A.setMaxSpeed(aNumber);
    stepper_B.setMaxSpeed(aNumber);
  }

}
