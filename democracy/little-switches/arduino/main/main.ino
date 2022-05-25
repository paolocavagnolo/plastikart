/* scritto da Paolo Cavagnolo 03-03-17 */
/* codice definitivo ancora da tespare */


#define zampaAS 8
#define zampaAD 6
#define zampaPS 7
#define zampaPD 5

#define piede A0
#define tamburo 2

#define pot A3

unsigned long tOn[6] = {0, 0, 0, 0, 0, 0};
unsigned long tOff[6] = {0, 0, 0, 0, 0, 0};
unsigned long currentMillis = 0;

unsigned long volo = 0;
unsigned long appoggio = 0;
unsigned long attesaCorta = 0;
unsigned long attesaLunga = 0;
unsigned long aspetta = 0;

unsigned long ritmo = 200;
unsigned long gioco = 600;

bool zampeEnable = false;
bool tamburoEnable = false;
bool piedeEnable = false;

void setup() {
  Serial.begin(9600);

  pinMode(zampaAS, OUTPUT);
  pinMode(zampaAD, OUTPUT);
  pinMode(zampaPS, OUTPUT);
  pinMode(zampaPD, OUTPUT);

  pinMode(tamburo, OUTPUT);
  pinMode(piede, OUTPUT);

  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  if (analogRead(pot) > 512) {
    //veloce
    attesaCorta = 50;
    attesaLunga = 150;
    appoggio = 500;
    aspetta = 600;
  }
  else {
    //lenta
    attesaCorta = 100;
    attesaLunga = 120;
    appoggio = 200;
    aspetta = 780;
  }

  volo = (unsigned long)(attesaCorta + attesaLunga + attesaCorta);
  tOn[1] = attesaCorta;
  tOn[2] = (unsigned long)(attesaCorta + attesaLunga);
  tOn[3] = volo;

  if (true) {
    zampeEnable = true;
  }
}


void loop() {

  currentMillis = millis();
  
  if (!digitalRead(11)) {
    galoppo((unsigned long)(volo + appoggio), aspetta);
  }
  else {
    init_galoppo();
  }
  if (!digitalRead(12)) {
    calcio(gioco);
  }
  else {
    init_calcio();
  }



}

void rullo(unsigned long tempoOff) {
  blinka(tamburo, 480UL, tempoOff, 4);
}

void calcio(unsigned long tempoOff) {
  blinka(piede, 480UL, tempoOff, 5);
}

void galoppo(unsigned long tempoOn, unsigned long tempoOff) {
  blinka(zampaPS, tempoOn, tempoOff, 0);
  blinka(zampaPD, tempoOn, tempoOff, 1);
  blinka(zampaAS, tempoOn, tempoOff, 2);
  blinka(zampaAD, tempoOn, tempoOff, 3);
}

void blinka(uint8_t pin, unsigned long timeOn, unsigned long timeOff, uint8_t index) {

  if (!digitalRead(pin)) {
    if (currentMillis > tOn[index]) {
      tOff[index] = (unsigned long)(currentMillis + timeOn);
      digitalWrite(pin, HIGH);
    }
  }

  if (digitalRead(pin)) {
    if (currentMillis > tOff[index]) {
      tOn[index] = (unsigned long)(currentMillis + timeOff);
      digitalWrite(pin, LOW);
    }
  }
}

void init_galoppo() {
  digitalWrite(zampaPS,LOW);
  digitalWrite(zampaPD,LOW);
  digitalWrite(zampaAS,LOW);
  digitalWrite(zampaAD,LOW);

  tOn[0] = currentMillis;
  tOn[1] = (unsigned long)(currentMillis + attesaCorta);
  tOn[2] = (unsigned long)(currentMillis + attesaCorta + attesaLunga);
  tOn[3] = (unsigned long)(currentMillis + volo);

  tOff[0] = 0;
  tOff[1] = 0;
  tOff[2] = 0;
  tOff[3] = 0;
  

}

void init_calcio() {
  digitalWrite(piede,LOW);

  tOn[5] = currentMillis;
  tOff[5] = 0;
}

