#include <PS2Keyboard.h>

const int DataPin = 9;
const int IRQpin =  3;

#define pot A3

PS2Keyboard keyboard;

long t1 = 0;
long t2 = 0;
long t3 = 0;
long t4 = 0;
long t5 = 0;
long t6 = 0;
long t7 = 0;
long t8 = 0;

int tempo = 0;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");

  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);

  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);

}

void loop() {
  tempo = map(analogRead(pot),0,1023,50,200);
  Serial.println(tempo);

  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == '1') {
      digitalWrite(2,HIGH);
      t1 = millis();
    } 
    else if (c == '3') {
      digitalWrite(5,HIGH);
      t3 = millis();
    }
    else if (c == '4') {
      digitalWrite(6,HIGH);
      t4 = millis();
    }
    else if (c == '5') {
      digitalWrite(7,HIGH);
      t5 = millis();
    }
    else if (c == '6') {
      digitalWrite(8,HIGH);
      t6 = millis();
    }
    else if (c == '7') {
      digitalWrite(A0,HIGH);
      t7 = millis();
    }
    else if (c == '8') {
      digitalWrite(A1,HIGH);
      t8 = millis();
    }
    else {
      Serial.print(c);
    }
  }

  else {
    if ((millis() - t1) > tempo) {
      digitalWrite(2,LOW);
    }
    if ((millis() - t3) > tempo) {
      digitalWrite(5,LOW);
    }
    if ((millis() - t4) > tempo) {
      digitalWrite(6,LOW);
    }
    if ((millis() - t5) > tempo) {
      digitalWrite(7,LOW);
    }
    if ((millis() - t6) > tempo) {
      digitalWrite(8,LOW);
    }
    if ((millis() - t7) > tempo) {
      digitalWrite(A0,LOW);
    }
    if ((millis() - t8) > tempo) {
      digitalWrite(A1,LOW);
    }

  }
}
