#include <PS2Keyboard.h>

const int DataPin = 9;
const int IRQpin =  3;

#define zampaAS 8
#define zampaAD 6
#define zampaPS 7
#define zampaPD 5

#define piede A0
#define tamburo 2

int z[4] = {zampaAS, zampaAD, zampaPS, zampaPD};

void setup() {
  Serial.begin(9600);

  keyboard.begin(DataPin, IRQpin);

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

  Serial.println("Zampa numero: 0");
}

int a = 0;
int aa = 0;

long t_a = 0;
long t_aa = 0;

int i = 0;

void loop() {
  if (keyboard.available()) {

    char c = keyboard.read();
    Serial.println(c);

  }

  

  if ((millis() - t_aa) > 2000) {
    
    Serial.println(a);
    digitalWrite(z[i],HIGH);
    
    if ((millis() - t_a) > a) {

      t_a = millis();
      digitalWrite(z[i],LOW);
      t_aa = millis();
      
      if (a <= 1000) {
        a += 100;
      }
      else {
        a = 0;
        i++;
        Serial.println("Zampa numero: ");
        Serial.println(z[i]);
      }

    }
  }
  
  


  
}
