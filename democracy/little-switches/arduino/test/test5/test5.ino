#define zampaAS 8
#define zampaAD 6
#define zampaPS 7
#define zampaPD 5

#define piedePin A0
#define tamburoPin 2

#define buttonZampe 10
#define buttonPiede 11
#define buttonTamburo 12
#define buttonStop 13

int volo = 500; //tempo in ms delle gambe in aria
int attesaAppoggio = 50; //tempo in ms dell'appoggio tra le gambe vicine (as e ap per esempio)
int attesaAllungo = 100; //tempo in ms tra appoggio gambe davanti e gambe dietro
int attesaTotale = volo + attesaAppoggio + attesaAllungo + attesaAppoggio;

int attesaTerra = 50; //tempo in ms in cui il piede rimane a terra

int z[4] = {zampaPS, zampaPD, zampaAS, zampaAD};

void setup() {
  pinMode(zampaAS,OUTPUT);
  pinMode(zampaAD,OUTPUT);
  pinMode(zampaPS,OUTPUT);
  pinMode(zampaPD,OUTPUT);

  pinMode(buttonZampe, INPUT_PULLUP);
  pinMode(buttonPiede, INPUT_PULLUP);
  pinMode(buttonTamburo, INPUT_PULLUP);
  pinMode(buttonTamburo, INPUT_PULLUP);

  pinMode(piedePin,OUTPUT);
  pinMode(tamburoPin,OUTPUT);

  digitalWrite(zampaAS,LOW);
  digitalWrite(zampaAD,LOW);
  digitalWrite(zampaPS,LOW);
  digitalWrite(zampaPD,LOW);

  digitalWrite(piedePin,LOW);
  digitalWrite(tamburoPin,LOW);

}

long z_start[4] = {0,0,0,0};
long t[4] = {0,attesaAppoggio,attesaAppoggio+attesaAllungo,attesaAppoggio+attesaAppoggio+attesaAllungo};

long p_start = 0;
long t_start = 0;

bool galoppo = false;
bool piede = false;
bool tamburo = false;

int tempoTamburo = 500;
int tempoPiede = 1000;

void loop() {

  if (digitalRead(buttonZampe) == LOW) {
    galoppo = true;
    z_start[0] = millis();
    z_start[1] = millis();
    z_start[2] = millis();
    z_start[3] = millis();
  }
  if (digitalRead(buttonTamburo) == LOW) {
    tamburo = true;
    t_start = millis();
  }
  if (digitalRead(buttonPiede) == LOW) {
    piede = true;
    p_start = millis();
  }
  if (digitalRead(buttonStop) == LOW) {
    galoppo = false;
    piede = false;
    tamburo = false;
  }


  if (galoppo) {
    for (int = 0; i<4; i++) {
      if ((millis() - z_start[i]) > t[i]) {
        digitalWrite(z[i],HIGH);
      } 
      if ((millis() - (z_start[i]+t[i])) > attesaTotale) {
        digitalWrite(z[i],LOW);
        z_start[i] = millis()+attesaTerra;
      }
    }

  }

  if (tamburo) {
    digitalWrite(tamburoPin, HIGH);
    if ((millis() - t_start) > tempoTamburo) {
      digitalWrite(tamburoPin, LOW);
      t_start = millis();
    }
  }

  if (piede) {
    digitalWrite(piedePin, HIGH);
    if ((millis() - p_start) > tempoPiede) {
      digitalWrite(piedePin, LOW);
      p_start = millis();
    }
  }

}

