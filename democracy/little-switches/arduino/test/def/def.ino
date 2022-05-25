#define zampaAS 8
#define zampaAD 6
#define zampaPS 7
#define zampaPD 5

#define piede A0
#define tamburo 2

#define pot A3

int volo = 400; //tempo in ms delle gambe in aria
int attesaAppoggio = 60; //tempo in ms dell'appoggio tra le gambe vicine (as e ap per esempio)
int attesaAllungo = 120; //tempo in ms tra appoggio gambe davanti e gambe dietro

int z[4] = {zampaPS, zampaPD, zampaAS, zampaAD};

int tempo = 400;

void setup() {
  pinMode(zampaAS, OUTPUT);
  pinMode(zampaAD, OUTPUT);
  pinMode(zampaPS, OUTPUT);
  pinMode(zampaPD, OUTPUT);

  pinMode(piede, OUTPUT);
  pinMode(tamburo, OUTPUT);

  digitalWrite(zampaAS, LOW);
  digitalWrite(zampaAD, LOW);
  digitalWrite(zampaPS, LOW);
  digitalWrite(zampaPD, LOW);

  digitalWrite(piede, LOW);
  digitalWrite(tamburo, LOW);

}

void loop() {
  if (analogRead(pot) > 512) {
    veloce();
  }
  else {
    lenta();
  }
  
}

void lenta() {
  digitalWrite(zampaPS, HIGH);  //0 ms - apro 0
  delay(60);
  digitalWrite(zampaPD, HIGH);  //60 ms  - apro 1
  delay(160);
  digitalWrite(zampaAS, HIGH);  //220 ms - apro 2
  delay(60);
  digitalWrite(zampaAD, HIGH);  //280 ms - apro 3
  delay(200);
  digitalWrite(zampaPS, LOW);   //480 ms - chiudo 0: 740 ms di tempo aperto
  delay(60);
  digitalWrite(zampaPD, LOW);   //480 ms - chiudo 1: 740 ms di tempo aperto
  delay(160);
  digitalWrite(zampaAS, LOW);   //980 ms - chiudo 2: 740 ms di tempo aperto
  delay(60);
  digitalWrite(zampaAD, LOW);   //1060 ms - chiudo 3: 740 ms di tempo aperto
  delay(600);
}

void veloce() {
  digitalWrite(zampaPS, HIGH);  //0 ms - apro 0
  delay(40);
  digitalWrite(zampaPD, HIGH);  //80 ms  - apro 1
  delay(150);
  digitalWrite(zampaAS, HIGH);  //240 ms - apro 2
  delay(40);
  digitalWrite(zampaAD, HIGH);  //320 ms - apro 3
  delay(150);
  digitalWrite(zampaPS, LOW);   //740 ms - chiudo 0: 740 ms di tempo aperto
  delay(40);
  digitalWrite(zampaPD, LOW);   //820 ms - chiudo 1: 740 ms di tempo aperto
  delay(150);
  digitalWrite(zampaAS, LOW);   //980 ms - chiudo 2: 740 ms di tempo aperto
  delay(40);
  digitalWrite(zampaAD, LOW);   //1060 ms - chiudo 3: 740 ms di tempo aperto
  delay(400);
}
