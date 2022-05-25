// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper(1, 7, 5); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

long PulseRev = 400;

void setup()
{
  //pinMode(3,OUTPUT);
  //digitalWrite(3,HIGH);
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(PulseRev / 2);
  stepper.setAcceleration(2 * PulseRev);
  stepper.moveTo(64 * PulseRev);

  //stepper.setCurrentPosition(0);

  Serial.begin(9600);
}

void loop()
{
  //Serial.println(stepper.currentPosition());
  // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());
  stepper.run();
}
