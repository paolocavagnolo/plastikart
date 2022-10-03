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

void setup() {

  digitalWrite(RR1,HIGH);
  digitalWrite(RR2,HIGH);
  digitalWrite(RR3,HIGH);
  digitalWrite(RR4,HIGH);
  digitalWrite(RR5,HIGH);
  digitalWrite(RR6,HIGH);
  digitalWrite(RR7,HIGH);
  digitalWrite(RR8,HIGH);

  pinMode(RR1,OUTPUT);
  pinMode(RR2,OUTPUT);
  pinMode(RR3,OUTPUT);
  pinMode(RR4,OUTPUT);
  pinMode(RR5,OUTPUT);
  pinMode(RR6,OUTPUT);
  pinMode(RR7,OUTPUT);
  pinMode(RR8,OUTPUT);

  digitalWrite(RR1,HIGH);
  digitalWrite(RR2,HIGH);
  digitalWrite(RR3,HIGH);
  digitalWrite(RR4,HIGH);
  digitalWrite(RR5,HIGH);
  digitalWrite(RR6,HIGH);
  digitalWrite(RR7,HIGH);
  digitalWrite(RR8,HIGH);
  
  myservo1.attach(5);
  myservo2.attach(6);

  delay(1000);

  myservo1.write(95);
  myservo2.write(95);

  
  
}

void loop() {

  // FARI LAMPEGGIANTI
//  for (uint8_t i=0; i<8; i++) {
//    digitalWrite(RR1, LOW);
//    delay(300);
//    digitalWrite(RR1, HIGH);
//    delay(150);
//  }
//
//  delay(1000);
//
//  for (uint8_t i=0; i<8; i++) {
//    digitalWrite(RR1, LOW);
//    delay(300);
//    digitalWrite(RR1, HIGH);
//    delay(150);
//  }

  // RUOTE
//  digitalWrite(RR2, LOW);
//
//  delay(2000);
//
//  for (uint8_t i=0; i<5; i++) {
//    digitalWrite(RR1, LOW);
//    delay(200);
//    digitalWrite(RR1, HIGH);
//    delay(500);
//  }
//
//  delay(2000);
//
//  digitalWrite(RR2, HIGH);
//
//  delay(1000);

  //FARI FISSI

 // digitalWrite(RR1, LOW);

  delay(2000);

  for (uint8_t x=0; x < 60; x++) {
    myservo1.write(93+x);
    myservo2.write(92-x);
    delay(5);
  }

  delay(2000);

  for (uint8_t x=60; x > 0; x--) {
    myservo1.write(93+x);
    myservo2.write(92-x);
    delay(25);
  }
  myservo1.write(93);
  myservo2.write(92);

  digitalWrite(RR1, HIGH);

//





}
