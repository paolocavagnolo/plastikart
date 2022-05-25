#include <PS2Keyboard.h>

const int DataPin = 9;
const int IRQpin =  3;

#define pot A3

#define zampaAS 8
#define zampaAD 6
#define zampaPS 7
#define zampaPD 5

#define piede A0
#define tamburo 2

PS2Keyboard keyboard;

long t1 = 0;
long t2 = 0;
long t3 = 0;
long t4 = 0;
long t5 = 0;
long t6 = 0;

int tempo = 0;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");

  pinMode(zampaAS,OUTPUT);
  pinMode(zampaAD,OUTPUT);
  pinMode(zampaPS,OUTPUT);
  pinMode(zampaPD,OUTPUT);

  pinMode(piede,OUTPUT);
  pinMode(tamburo,OUTPUT);

  digitalWrite(zampaAS,LOW);
  digitalWrite(zampaAD,LOW);
  digitalWrite(zampaPS,LOW);
  digitalWrite(zampaPD,LOW);

  digitalWrite(piede,LOW);
  digitalWrite(tamburo,LOW);

}

void loop() {
  tempo = map(analogRead(pot),0,1023,50,200);
  Serial.print("tempo: ");
  Serial.print(tempo);
  Serial.println(" ms");

  if (keyboard.available()) {
    
    char c = keyboard.read();

    if (c == PS2_LEFTARROW) {
      digitalWrite(zampaAS,HIGH);
      t1 = millis();
    } else if (c == PS2_UPARROW) {
      digitalWrite(zampaAD,HIGH);
      t2 = millis();
    } else if (c == PS2_RIGHTARROW) {
      digitalWrite(zampaPS,HIGH);
      t3 = millis();
    } else if (c == PS2_DOWNARROW) {
      digitalWrite(zampaPD,HIGH);
      t4 = millis();
    } else if (c == 'p') {
      digitalWrite(piede,HIGH);
      t5 = millis();
    } else if (c == 't') {
      digitalWrite(tamburo,HIGH);
      t6 = millis();
    }
    
    
  }

  else {
    if ((millis() - t1) > tempo) {
      digitalWrite(zampaAS,LOW);
    }
    if ((millis() - t2) > tempo) {
      digitalWrite(zampaAD,LOW);
    }
    if ((millis() - t3) > tempo) {
      digitalWrite(zampaPS,LOW);
    }
    if ((millis() - t4) > tempo) {
      digitalWrite(zampaPD,LOW);
    }
    if ((millis() - t5) > tempo) {
      digitalWrite(piede,LOW);
    }
    if ((millis() - t6) > tempo) {
      digitalWrite(tamburo,LOW);
    }
  }
}
