//CAR - VERSION 1.0

#include <Servo.h>

#define RR1 7 //LUCI
#define RR2 4 //RUOTE
#define RR3 3
#define RR4 2
#define RR5 9 //ok
#define RR6 8 //ok
#define RR7 11 //ok
#define RR8 10 //ok

Servo myservo1;
Servo myservo2;

int pos = 0;

void openBoth(uint8_t vel);
void closeBoth(uint8_t vel);
void openDX(uint8_t vel);
void closeDX(uint8_t vel);
void openSX(uint8_t vel);
void closeSX(uint8_t vel);

void setup() {

  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, HIGH);
  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, HIGH);
  digitalWrite(RR5, HIGH);
  digitalWrite(RR6, HIGH);
  digitalWrite(RR7, HIGH);
  digitalWrite(RR8, HIGH);

  pinMode(RR1, OUTPUT);
  pinMode(RR2, OUTPUT);
  pinMode(RR3, OUTPUT);
  pinMode(RR4, OUTPUT);
  pinMode(RR5, OUTPUT);
  pinMode(RR6, OUTPUT);
  pinMode(RR7, OUTPUT);
  pinMode(RR8, OUTPUT);

  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, HIGH);
  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, HIGH);
  digitalWrite(RR5, HIGH);
  digitalWrite(RR6, HIGH);
  digitalWrite(RR7, HIGH);
  digitalWrite(RR8, HIGH);

  myservo1.attach(5);
  myservo2.attach(6);

  delay(1000);

  myservo1.write(95);
  myservo2.write(95);



}

void loop() {

  // WHEEL START
  digitalWrite(RR2, LOW);
  digitalWrite(RR1, LOW);

  // DOORS OPEN
  openBoth(5);

  // LIGHTS BLINK
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(RR1, HIGH);
    delay(100);
    digitalWrite(RR1, LOW);
    delay(300);
  }

  // DOOR CLOSE
  closeBoth(5);

  // LIGHTS BLINK
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(RR1, HIGH);
    delay(100);
    digitalWrite(RR1, LOW);
    delay(300);
  }

  delay(1000);

  openBoth(5);
  delay(300);
  closeBoth(25);

  // LIGHTS BLINK
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(RR1, HIGH);
    delay(100);
    digitalWrite(RR1, LOW);
    delay(50);
  }

  for (uint8_t j = 0; j < 1; j++) {
    openSX(5);
    delay(150);
    openDX(30);
    closeSX(5);
    openSX(15);
    closeDX(5);
    delay(300);
    closeSX(5);
    openBoth(10);
    closeDX(5);
    closeSX(5);
  }

}

void openBoth(uint8_t vel) {
  // DOORS OPEN
  for (uint8_t x = 0; x < 50; x++) {
    myservo1.write(93 + x);
    myservo2.write(92 - x);
    delay(vel);
  }
}

void closeBoth(uint8_t vel) {
  for (uint8_t x = 50; x > 0; x--) {
    myservo1.write(93 + x);
    myservo2.write(92 - x);
    delay(vel);
  }
  myservo1.write(93);
  myservo2.write(92);
}

void openSX(uint8_t vel) {
  for (uint8_t x = 0; x < 50; x++) {
    myservo1.write(93 + x);
    delay(vel);
  }
}
void openDX(uint8_t vel) {
  for (uint8_t x = 0; x < 50; x++) {
    myservo2.write(92 - x);
    delay(vel);
  }
}
void closeSX(uint8_t vel) {
  for (uint8_t x = 50; x > 0; x--) {
    myservo1.write(93 + x);
    delay(vel);
  }
  myservo1.write(93);
}

void closeDX(uint8_t vel) {
  for (uint8_t x = 50; x > 0; x--) {
    myservo2.write(92 - x);
    delay(vel);
  }
  myservo2.write(92);
}

