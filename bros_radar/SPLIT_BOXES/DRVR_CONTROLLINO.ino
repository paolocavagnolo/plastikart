#include <SPI.h>
#include <Controllino.h> /* Usage of CONTROLLINO library allows you to use CONTROLLINO_xx aliases in your sketch. */

#define enaA CONTROLLINO_D0
#define velA CONTROLLINO_D10

#define enaB CONTROLLINO_D1
#define velB CONTROLLINO_D11

#define lux CONTROLLINO_R8

#define btnMan CONTROLLINO_A5
#define btnRem CONTROLLINO_A6
#define testMot1 CONTROLLINO_A7
#define testMot2 CONTROLLINO_A8
#define testLux CONTROLLINO_A9

void setup() {

 pinMode(enaA, OUTPUT);
 pinMode(velA, OUTPUT);
 pinMode(enaB, OUTPUT);
 pinMode(velB, OUTPUT);
 pinMode(lux, OUTPUT);

 pinMode(btnMan, INPUT);
 pinMode(btnRem, INPUT);
 pinMode(testMot1, INPUT);
 pinMode(testMot2, INPUT);
 pinMode(testLux, INPUT);

 Serial3.begin(115200);
 Controllino_RS485Init();

}

char in = "";
int vel = 0;

void loop() {

  // TEST BUTTONS
  if (digitalRead(btnMan)) {
    if (digitalRead(testMot1)) {
      digitalWrite(enaA,HIGH);
      analogWrite(velA,70);
    }
    else {
      digitalWrite(enaA,LOW);
      analogWrite(velA,0);
    }
  
    if (digitalRead(testMot2)) {
      digitalWrite(enaB,HIGH);
      analogWrite(velB,65);
    }
    else {
      digitalWrite(enaB,LOW);
      analogWrite(velB,0);
    }
  
    if (digitalRead(testLux)) {
      digitalWrite(lux,HIGH);
    }
    else {
      digitalWrite(lux,LOW);
    }
  }
  

  //RS485
  if (digitalRead(btnRem)) {
    if (Serial3.available() > 2) {
      in = Serial3.read();
      
      if (in == 'a') {
        
        in = Serial3.read();
        if (in == 'A') {
          
          in = Serial3.read();
          
          if (in == '0') {
            digitalWrite(enaA,LOW);
          }
          else if (in == '1') {
            digitalWrite(enaA,HIGH);            
          }
        }
        else if (in == 'V') {
          vel = (int)(Serial3.parseInt());
          analogWrite(velA,vel);
        }
        
      }
      else if (in == 'b') {
  
        in = Serial3.read();
        if (in == 'B') {
          in = Serial3.read();
          if (in == '0') {
            digitalWrite(enaB,LOW);
          }
          else if (in == '1') {
            digitalWrite(enaB,HIGH);
          }
        }
        else if (in == 'V') {
          vel = (int)(Serial3.parseInt());
          analogWrite(velB,vel);
        }
        
      }
      else if (in == 'l') {
        in = Serial3.read();
        if (in == 'L') {
          in = Serial3.read();
          if (in == '0') {
            digitalWrite(lux,LOW);
          }
          else if (in == '1') {
            digitalWrite(lux,HIGH);
          }
        }
      }
    }
  }

}
