#define RR1 7
#define RR2 10
#define RR3 3
#define RR4 4
#define RR5 9
#define RR6 10
#define RR7 11
#define RR8 2

#define SERVO1 5
#define SERVO2 6


#include <Servo.h>

Servo myservo1;
Servo myservo2;

void setup() {
  // put your setup code here, to run once:
  pinMode(RR1,OUTPUT);
  pinMode(RR2,OUTPUT);
  pinMode(RR3,OUTPUT);
  pinMode(RR4,OUTPUT);
  pinMode(RR5,OUTPUT);
  pinMode(RR6,OUTPUT);
  pinMode(RR7,OUTPUT);
  pinMode(RR8,OUTPUT);

  myservo1.attach(6);
  myservo2.attach(5);

  digitalWrite(RR1,HIGH);
  digitalWrite(RR2,HIGH);
  digitalWrite(RR3,HIGH);
  digitalWrite(RR4,HIGH);
  digitalWrite(RR5,HIGH);
  digitalWrite(RR6,HIGH);
  digitalWrite(RR7,HIGH);
  digitalWrite(RR8,HIGH);

}

uint8_t pos1 = 93;
uint8_t pos2 = 92;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RR1,LOW);
  digitalWrite(RR2,LOW);

  delay(5000);

  digitalWrite(RR1,HIGH);
  digitalWrite(RR2,HIGH);

  delay(2000);
 
  

}
