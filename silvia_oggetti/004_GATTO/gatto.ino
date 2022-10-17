#include "AsyncServoLib.h"

AsyncServo zampa;
AsyncServo coda;

void step1();
void step2();
void zampaSU();
void zampaGIU();
void staiSU();

void setup()
{

	coda.Attach(9);
	zampa.Attach(10);

	coda.SetOutput(500, 1500, 2500);
	zampa.SetOutput(500, 1500, 2500);
 
	delay(1000);
	coda.WriteDegree(95);
  zampa.WriteDegree(95);

  step1();
  
}

void step1() {
  coda.MoveDegrees(50,random(500,3000),step2);
}

void step2() {
  coda.MoveDegrees(95,random(500,3000),step1);
}

void zampaSU() {
  zampa.MoveDegrees(150,random(500,3000),staiSU);
}

void staiSU() {
  zampa.MoveDegrees(151,random(500,3000),zampaGIU);
}

void zampaGIU() {
  zampa.MoveDegrees(95,random(500,3000));
}

unsigned long dt=0;
unsigned long dur = 8000;

void loop()
{
	delay(10);
	coda.Update();
  zampa.Update();

  if ((millis() - dt) > dur) {
    dt = millis();
    dur = random(4000,8000);
    zampaSU();
  }
  

}
