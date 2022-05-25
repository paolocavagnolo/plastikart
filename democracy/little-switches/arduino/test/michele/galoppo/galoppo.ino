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

int volo = 400; //tempo in ms delle gambe in aria
int attesaAppoggio = 75; //tempo in ms dell'appoggio tra le gambe vicine (as e ap per esempio)
int attesaAllungo = 150; //tempo in ms tra appoggio gambe davanti e gambe dietro


PS2Keyboard keyboard;

long t1 = 0;
long t2 = 0;
long t3 = 0;
long t4 = 0;
long t5 = 0;
long t6 = 0;

int tempo = 78;
float w = 0;



float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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
  w = mapfloat(analogRead(pot)/1.0,0,1023,0.25,3);

  Serial.print("weight: ");
  Serial.println(w);

  if (keyboard.available()) {
    
    char c = keyboard.read();

    if (c == '1') {
      galoppo(w);
    } 
    else if (c == 'p') {
      digitalWrite(piede,HIGH);
      t5 = millis();
    } 
    else if (c == 't') {
      digitalWrite(tamburo,HIGH);
      t6 = millis();
    }
       
  }

  else {
    if ((millis() - t5) > tempo) {
      digitalWrite(piede,LOW);
    }
    if ((millis() - t5) > tempo) {
      digitalWrite(piede,LOW);
    }
    if ((millis() - t6) > tempo) {
      digitalWrite(tamburo,LOW);
    }
  }
}

void galoppo(float w) {
  for (int i=0; i<10; i++) {
  digitalWrite(zampaPS,HIGH);
  delay(attesaAppoggio*w);
  digitalWrite(zampaPD,HIGH);
  delay(attesaAllungo*w);
  digitalWrite(zampaAS,HIGH);
  delay(attesaAppoggio*w);
  digitalWrite(zampaAD,HIGH);
  delay(volo*w);
  digitalWrite(zampaPS,LOW);
  delay(attesaAppoggio*w);
  digitalWrite(zampaPD,LOW);
  delay(attesaAllungo*w);
  digitalWrite(zampaAS,LOW);
  delay(attesaAppoggio*w);
  digitalWrite(zampaAD,LOW);
  }
}
