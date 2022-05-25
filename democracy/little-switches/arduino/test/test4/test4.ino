#include <PS2Keyboard.h>

const int DataPin = 9;
const int IRQpin =  3;

#define zampaAS 8
#define zampaAD 6
#define zampaPS 7
#define zampaPD 5

#define piede A0
#define tamburo 2

int volo = 500; //tempo in ms delle gambe in aria
int attesaAppoggio = 50; //tempo in ms dell'appoggio tra le gambe vicine (as e ap per esempio)
int attesaAllungo = 100; //tempo in ms tra appoggio gambe davanti e gambe dietro
int attesaTotale = volo + attesaAppoggio + attesaAllungo + attesaAppoggio;

int attesaTerra = 50; //tempo in ms in cui il piede rimane a terra



int z[4] = {zampaPS, zampaPD, zampaAS, zampaAD};

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

long t_start[4] = {0,0,0,0};
long t[4] = {0,attesaAppoggio,attesaAppoggio+attesaAllungo,attesaAppoggio+attesaAppoggio+attesaAllungo};

bool galoppo = false;

void loop() {

  if (keyboard.available()) {
    
    char c = keyboard.read();

    if (c == '1') {
      galoppo = true;
      t_start[0] = millis();
      t_start[1] = millis();
      t_start[2] = millis();
      t_start[3] = millis();
    } 
    else if (c == '2') {
      galoppo = false;
    } 
  }

  if (galoppo) {
    for (int = 0; i<4; i++) {
      if ((millis() - t_start[i]) > t[i]) {
        digitalWrite(z[i],HIGH);
      } 
      if ((millis() - (t_start[i]+t[i])) > attesaTotale) {
        digitalWrite(z[i],LOW);
        t_start[i] = millis()+attesaTerra;
      }
    }

  }

}

