#include <PS2Keyboard.h>

const int DataPin = 9;
const int IRQpin =  3;

#define zampaAS 8
#define zampaAD 6
#define zampaPS 7
#define zampaPD 5

#define piede A0
#define tamburo 2

int volo = 420; //tempo in ms delle gambe in aria
int attesaAppoggio = 80; //tempo in ms dell'appoggio tra le gambe vicine (as e ap per esempio)
int attesaAllungo = 160; //tempo in ms tra appoggio gambe davanti e gambe dietro

PS2Keyboard keyboard;

void setup() {
  keyboard.begin(DataPin, IRQpin);
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

  if (keyboard.available()) {
    
    char c = keyboard.read();

    if (c == '1') {
      galoppo();
    } 
       
  }

}

//80 - 160 - 420

void galoppo() {
  for (int i=0; i<10; i++) {
    digitalWrite(zampaPS,HIGH);   //0 ms - apro 0
    delay(attesaAppoggio);        
    digitalWrite(zampaPD,HIGH);   //80 ms  - apro 1
    delay(attesaAllungo);
    digitalWrite(zampaAS,HIGH);   //240 ms - apro 2
    delay(attesaAppoggio);
    digitalWrite(zampaAD,HIGH);   //320 ms - apro 3
    delay(volo);
    digitalWrite(zampaPS,LOW);    //740 ms - chiudo 0: 740 ms di tempo aperto
    delay(attesaAppoggio);
    digitalWrite(zampaPD,LOW);    //820 ms - chiudo 1: 740 ms di tempo aperto
    delay(attesaAllungo);
    digitalWrite(zampaAS,LOW);    //980 ms - chiudo 2: 740 ms di tempo aperto
    delay(attesaAppoggio);
    digitalWrite(zampaAD,LOW);    //1060 ms - chiudo 3: 740 ms di tempo aperto
  }
}
