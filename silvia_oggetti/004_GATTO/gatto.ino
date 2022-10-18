//CAT - VERSION 1.0

/*  Code written by Paolo Cavagnolo for FREITAG - 17/10/2022
 *  
 *  
 *  !!! IMPORTANT MOTORS LIMIT !!!
 *  tail: min 50 - max 95
 *  foot: min 95 - max 151
 */

#include "AsyncServoLib.h"

AsyncServo foot;
AsyncServo tail;

void tailLEFT();
void tailRIGHT();
void footUP();
void footDOWN();
void footSTILL();

void setup()
{

  tail.Attach(9);
  foot.Attach(10);

  tail.SetOutput(500, 1500, 2500);
  foot.SetOutput(500, 1500, 2500);
 
  delay(100);
  tail.WriteDegree(95);
  foot.WriteDegree(95);

  tailLEFT();
  footUP();
  
}

void tailLEFT() {
  tail.MoveDegrees(50,random(500,3000),tailRIGHT);
}

void tailRIGHT() {
  tail.MoveDegrees(95,random(500,3000),tailLEFT);
}

void footUP() {
  foot.MoveDegrees(150,random(500,3000),footSTILL);
}

void footSTILL() {
  foot.MoveDegrees(151,random(500,3000),footDOWN);
}

void footDOWN() {
  foot.MoveDegrees(95,random(500,3000));
}

unsigned long dt=0;
unsigned long dur = 8000;

void loop()
{
  delay(10);
  tail.Update();
  foot.Update();

  if ((millis() - dt) > dur) {
    dt = millis();
    dur = random(4000,8000);
    footUP();
  }
  

}
