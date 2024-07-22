#define RR1 12
#define RR2 11
#define RR3 10
#define RR4 9

#define BTN 7

void setup() {
  // put your setup code here, to run once:
  pinMode(RR1, OUTPUT);
  pinMode(RR2, OUTPUT);
  pinMode(RR3, OUTPUT);
  pinMode(RR4, OUTPUT);

  digitalWrite(RR1, LOW);
  digitalWrite(RR2, LOW);
  digitalWrite(RR3, LOW);
  digitalWrite(RR4, LOW);

  Serial.begin(9600);
}


unsigned long dt = 0;
unsigned long counter = 0;
bool gioco = false;
bool seq = true;
bool pos = false;

void loop() {
  // put your main code here, to run repeatedly:


  if (gioco) {
    if ((millis() - dt) > 291000) {
      gioco = false;
      digitalWrite(RR4, LOW);
      digitalWrite(RR3, LOW);
    }
    else {
      //disattiva led pulsante - collegato su NC
      digitalWrite(RR4, HIGH);

      //manda sequenza
      if (seq) {
        digitalWrite(RR3, HIGH);
        delay(500);
        digitalWrite(RR3, LOW);
        delay(500);
        
        seq = false;
      }
      else {
        digitalWrite(RR3, LOW);
      }


    }

  }
  else {
    //accendi led pulsante - collegato su NC
    digitalWrite(RR4, LOW);

    //assicurazione sul non mandare segnale
    digitalWrite(RR3, LOW);
   
    //controlla pulsante ingresso
    seq = true;
    if (digitalRead(BTN)) {
      counter++;
    }
    else {
      counter = 0;
    }

    if (counter > 10000) {
      pos = true;
    }

    if ((pos) && !digitalRead(BTN)) {
      gioco = true;
      dt = millis();
      pos = false;
    }
  }

}
