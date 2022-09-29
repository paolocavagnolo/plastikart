#define R1 2
#define R2 3
#define R3 4
#define R4 7
#define R5 8
#define R6 9
#define R7 10
#define R8 11

#define SERVO1 5
#define SERVO2 6


#include <Servo.h>

Servo myservo1;
Servo myservo2;

void setup() {
  // put your setup code here, to run once:
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(R3,OUTPUT);
  pinMode(R4,OUTPUT);
  pinMode(R5,OUTPUT);
  pinMode(R6,OUTPUT);
  pinMode(R7,OUTPUT);
  pinMode(R8,OUTPUT);

  myservo1.attach(6);
  myservo2.attach(5);

}

uint8_t pos1 = 93;
uint8_t pos2 = 92;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);

  delay(5000);

  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);

  delay(2000);


}
