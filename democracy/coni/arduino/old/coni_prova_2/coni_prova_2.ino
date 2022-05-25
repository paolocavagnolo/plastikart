// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

AccelStepper stepper(1, 2, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{
  stepper.setMaxSpeed(1000);
  Serial.begin(9600);
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(100.0);
  stepper.stop();
}

char inc;

int vel = 0;

void loop()
{
  if (Serial.available() > 0) {
    // read the incoming byte:
    inc = Serial.read();

    switch (inc) {
      case 'a':
        vel = abs(vel);
        Serial.print("antiorario: ");
        Serial.println(vel);
        break;
      case 'o':
        vel = -1 * abs(vel);
        Serial.print("orario: ");
        Serial.println(vel);
        break;
      default:
        vel = ((int)inc-47)*100;
        Serial.println(vel);
        break;
    }
  }
  stepper.setSpeed(vel);
  stepper.runSpeed();
  
}

