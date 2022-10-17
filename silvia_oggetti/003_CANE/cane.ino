#include <Servo.h>

Servo orecchie; // orecchie
Servo collo; // collo

int pos = 0;    // variable to store the servo position

void setup() {
  
  orecchie.attach(5);
  collo.attach(3);

  //ZERO CHECK
  orecchie.write(95);
  collo.write(95);
  
}

void muoviTesta(uint8_t da, uint8_t aa, uint8_t vel) {

  if (da <= aa) {
    for (pos = da; pos <= aa; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      collo.write(pos);
      delay(vel);                       // waits 15 ms for the servo to reach the position
    }
  }
  else {
    for (pos = da; pos >= aa; pos -= 1) { // goes from 180 degrees to 0 degrees
      collo.write(pos);
      delay(vel);                       // waits 15 ms for the servo to reach the position
    }
  }

  
}

void muoviOrecchie(uint8_t da, uint8_t aa, uint8_t vel) {

  if (da <= aa) {
    for (pos = da; pos <= aa; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      orecchie.write(pos);
      delay(vel);                       // waits 15 ms for the servo to reach the position
    }
  }
  else {
    for (pos = da; pos >= aa; pos -= 1) { // goes from 180 degrees to 0 degrees
      orecchie.write(pos);
      delay(vel);                       // waits 15 ms for the servo to reach the position
    }
  }

  
}

void loop() {

  muoviTesta(95,110, 50);
  delay(1000);
  muoviTesta(110,130, 50);
  delay(2000);
  muoviTesta(130,95, 5);
  delay(3000);
  muoviTesta(95,30, 5);
  delay(2000);

  muoviOrecchie(85,125, 5);
  delay(1000);
  muoviOrecchie(125,85, 5);
  delay(500);
  muoviOrecchie(85,125, 5);
  delay(100);
  muoviOrecchie(125,85, 5);

  muoviTesta(30,110,50);

  muoviOrecchie(85,125, 5);
  delay(100);
  muoviOrecchie(125,85, 5);
  muoviOrecchie(85,125, 5);
  delay(100);
  muoviOrecchie(125,85, 5);

  muoviTesta(110,30,5);
  delay(2000);
  muoviTesta(30,95,30);

  muoviOrecchie(85,125, 5);
  delay(100);

  muoviTesta(95,110, 5);
  delay(1000);
  muoviTesta(110,130, 50);
  delay(2000);
  muoviTesta(130,95, 5);
  delay(3000);

  muoviOrecchie(85,125, 5);
  delay(100);
  muoviOrecchie(125,85, 5);
  muoviOrecchie(85,125, 5);
  delay(100);
  muoviOrecchie(125,85, 5);
  muoviOrecchie(85,125, 5);
  delay(100);
  muoviOrecchie(125,85, 5);
  muoviOrecchie(85,125, 5);
  delay(100);
  muoviOrecchie(125,85, 5);
  muoviOrecchie(125,85, 50);
  delay(100);

 
}
