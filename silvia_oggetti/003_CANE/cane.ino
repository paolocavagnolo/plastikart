//DOG - VERSION 1.0

/*  Code written by Paolo Cavagnolo for FREITAG - 17/10/2022
 *  
 *  
 *  !!! IMPORTANT MOTORS LIMIT !!!
 *  Head: min 30 - max 130
 *  Ears: min 85 - max 125
 */

#include <Servo.h>

#define minEar 85
#define maxEar 125

Servo Ears; // Ears
Servo Head; // Head

int pos = 0;    // variable to store the servo position

void setup() {
  
  Ears.attach(5);
  Head.attach(3);

  //ZERO CHECK
  Ears.write(95);
  Head.write(95);
  
}

void moveHead(uint8_t da, uint8_t aa, uint8_t vel) {

  if (da <= aa) {
    for (pos = da; pos <= aa; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      Head.write(pos);
      delay(vel);                       // waits 15 ms for the servo to reach the position
    }
  }
  else {
    for (pos = da; pos >= aa; pos -= 1) { // goes from 180 degrees to 0 degrees
      Head.write(pos);
      delay(vel);                       // waits 15 ms for the servo to reach the position
    }
  }

  
}

void moveEars(uint8_t da, uint8_t aa, uint8_t vel) {

  if (da <= aa) {
    for (pos = da; pos <= aa; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      Ears.write(pos);
      delay(vel);                       // waits 15 ms for the servo to reach the position
    }
  }
  else {
    for (pos = da; pos >= aa; pos -= 1) { // goes from 180 degrees to 0 degrees
      Ears.write(pos);
      delay(vel);                       // waits 15 ms for the servo to reach the position
    }
  }

  
}

void loop() {

  //INITIAL 
  moveEars(minEar,maxEar, 5);
  moveHead(95,60, 5);
  delay(500);
  moveEars(maxEar,minEar, 5);
  moveHead(60,95, 30);
  delay(300);
  moveHead(95,130, 30);

  delay(2000);
  moveHead(130,95, 5);
  delay(3000);
  moveHead(95,30, 5);
  delay(2000);

  moveEars(minEar,maxEar, 5);
  delay(1000);
  moveEars(maxEar,minEar, 5);
  delay(500);
  moveEars(minEar,maxEar, 5);
  delay(100);
  moveEars(maxEar,minEar, 5);

  moveHead(30,110,50);

  moveEars(minEar,maxEar, 5);
  delay(100);
  moveEars(maxEar,minEar, 5);
  moveEars(minEar,maxEar, 5);
  delay(100);
  moveEars(maxEar,minEar, 5);

  moveHead(110,30,5);
  delay(2000);
  moveHead(30,95,30);

  moveEars(minEar,maxEar, 5);
  delay(100);
  
  moveHead(95,110, 5);
  delay(1000);
  moveHead(110,130, 50);
  delay(2000);
  moveHead(130,95, 5);
  delay(3000);

  // LAST EAR FAST BLINKS
  moveEars(minEar,maxEar, 5);
  delay(100);
  moveEars(maxEar,minEar, 5);
  moveEars(minEar,maxEar, 5);
  delay(100);
  moveEars(maxEar,minEar, 5);
  moveEars(minEar,maxEar, 5);
  delay(100);
  moveEars(maxEar,minEar, 5);
  moveEars(minEar,maxEar, 5);
  delay(100);
  moveEars(maxEar,minEar, 5);
  moveEars(maxEar,minEar, 50);  //SLOW EAR MOVEMENT
  delay(100);

 
}
