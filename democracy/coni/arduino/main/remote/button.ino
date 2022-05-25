#define MAINSW 12 //1 su 0 e 0 su 1
#define SEL_A 28 //0 su 1
#define SEL_B 31 //0 su 2
#define BT_A A14 //0 premuto
#define BT_B A8 //1 premuto
#define SEL_Gp A5 //0 su G e 1 su p

#define passetto 10
#define vel_passetti 3000

#define NUM_CHANNELS 16

long muovi(char let, int vel, int posA, int posB, int posC = 0);
long t0 = 0;
long dd = 100;
long tdd = 0;

uint8_t channels[NUM_CHANNELS] = {53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38};

void setup() {
  pinMode(MAINSW, INPUT_PULLUP);
  pinMode(SEL_A, INPUT_PULLUP);
  pinMode(SEL_B, INPUT_PULLUP);
  pinMode(BT_A, INPUT_PULLUP);
  pinMode(BT_B, INPUT_PULLUP);
  pinMode(SEL_Gp, INPUT_PULLUP);

  for (int i=0; i<NUM_CHANNELS; i++) {
    pinMode(channels[i], OUTPUT);
  }

  Serial.begin(9600);

  Serial2.begin(4800);
}

int act = 0;
long att1 = 0;
long att2 = 0;
bool inviatoG = false;
bool inviatop = false;

void loop() {
  while (digitalRead(MAINSW)) //SHOW
  {
    digitalWrite(channels[15],LOW);
    if (act == 0) {
      t0 = millis();
      Serial.println("ACT 0");
      inviatop = false;
      inviatoG = false;
      act++;
      att1 = 0;
      att2 = 0;
      Serial.print(digitalRead(SEL_A));
      Serial.print(" ");
      Serial.print(digitalRead(SEL_B));
      Serial.println(" ");
    }
    if ((digitalRead(SEL_A) == 0) && (digitalRead(SEL_B) == 1)) //A
    {
      show_uno();
    }
    else if ((digitalRead(SEL_A) == 1) && (digitalRead(SEL_B) == 1)) //B
    {
      show_due();
    }
    else if ((digitalRead(SEL_A) == 1) && (digitalRead(SEL_B) == 0)) //C
    {
      show_tre();
    }


  }
  while (!digitalRead(MAINSW)) //TEST
  {
    

    // Reset the Act. for the Next Show.
    act = 0;

    // COMMAND FROM SERIAL AVAILABLE
    // p 20 -60     >> move little cone A: 20 degree clockwise - B: 60 degree counterclockwise
    // P 2000       >> set velocity of little cone to 2000
    // g 90 -90 90  >> move big cone
    // G 4000       >> set velocity of big cone
    if (Serial.available() > 0) {
      Serial2.write(Serial.read());
    }

    // Check button
    checkButton();

  }
}

void attore(int scena, char let_G, int vel_G, int posG_a, int posG_b, int posG_c, char let_p, int vel_p, int posp_a, int posp_b, int pausa) {

  if (act == scena) {
    if (inviatoG == false) {
      att1 = muovi(let_G, vel_G, posG_a, posG_b, posG_c);
      digitalWrite(channels[act-1], HIGH);
      Serial.println("mando scena G");
      Serial.println(act);
      inviatoG = true;
      tdd = millis();
    }
    if ((inviatop == false) && ((long)(millis() - tdd) > dd)) {
      att2 = muovi(let_p, vel_p, posp_a, posp_b);
      Serial.println("mando scena p");
      Serial.println(act);
      inviatop = true;
    }
    if ((long)(millis() - t0) > (long)(magg(att1, att2) + pausa)) {
      inviatop = false;
      inviatoG = false;
      digitalWrite(channels[act-1], LOW);
      t0 = millis();

      act++;
    }
  }
}

void show_uno() {

  //intro
  attore(1, 'g', 2000, -180,  -180,  160, 'p', 2000, -150, 180,  8000); //def
  attore(2, 'g', 2000, 0,  -180,  -160, 'p', 2500, 150, -180,  8000); //def
  attore(3, 'g', 2000, 0,  80,  110, 'p', 3400, -130, 180,  8000); //def
  attore(4, 'g', 3000, 180,  -250,  -110, 'p', 1800, 130, -180,  8000); //def

  //dance
  attore(5, 'g', 4000, -640,  300,  -720, 'p', 3000, 540, -540,  15000); //def
  attore(6, 'g', 4000, 110,  -310,  -190, 'p', 3000, -360, 360,  6000); //def

  //outro
  attore(7, 'g', 2000, 160,  170,  180, 'p', 1500, 175, -170,  6000); //def

}

void show_due() {

  //intro
  attore(1, 'g', 2000, -180,  -180,  180, 'p', 2000, -150, 180,  8000); //def
  attore(2, 'g', 2000, 0,  -180,  -180, 'p', 2500, 150, -180,  8000); //def
  attore(3, 'g', 2000, 0,  80,  110, 'p', 3400, -130, 180,  8000); //def
  attore(4, 'g', 3000, 180,  -250,  -110, 'p', 1800, 130, -180,  5000); //def

  //dance
  attore(5, 'g', 4000, -640,  300,  -720, 'p', 2800, 540, -540,  13000); //def
  attore(6, 'g', 4000, 110,  -310,  -190, 'p', 3000, -360, 360,  6000); //def

  //outro
  attore(7, 'g', 2000, 160,  170,  180, 'p', 1500, 175, -170,  6000); //def

}

void show_tre() {

  //intro
  attore(1, 'g', 2000, -180,  -180,  180, 'p', 2000, -150, 180,  8000); //def
  attore(2, 'g', 2000, 0,  -180,  -180, 'p', 2500, 150, -180,  8000); //def
  attore(3, 'g', 2000, 0,  80,  110, 'p', 3400, -130, 180,  8000); //def
  attore(4, 'g', 3000, 180,  -250,  -110, 'p', 1800, 130, -180,  8000); //def

  //dance
  attore(5, 'g', 4000, -640,  300,  -720, 'p', 3000, 540, -540,  15000); //def
  attore(6, 'g', 4000, 110,  -310,  -190, 'p', 3000, -360, 360,  6000); //def

  //outro
  attore(7, 'g', 2000, 160,  170,  180, 'p', 1500, 175, -170,  6000); //def

}


long magg(long a, long b) {
  if (a >= b) {
    return a;
  }
  else {
    return b;
  }
}

long muovi(char let, int vel, int posA, int posB, int posC = 0) {
  String payload = "";

  if (let == 'p') {
    char LET = 'P';
    payload = "";
    payload += LET;
    payload += " ";
    payload += String(vel);
    payload += '\r';
    Serial2.print(payload);
    payload = "";
    payload += let;
    payload += " ";
    payload += String(posA);
    payload += " ";
    payload += String(posB);
    payload += '\r';
    Serial2.print(payload);
  }
  else if (let == 'g') {
    char LET = 'G';
    payload = "";
    payload += LET;
    payload += " ";
    payload += String(vel);
    payload += '\r';
    Serial2.print(payload);
    payload = "";
    payload += let;
    payload += " ";
    payload += String(posA);
    payload += " ";
    payload += String(posB);
    payload += " ";
    payload += String(posC);
    payload += '\r';
    Serial2.print(payload);
  }

  int maxx = 0;
  if (abs(posA) >= abs(posB)) {
    if (abs(posA) >= abs(posC)) {
      maxx = abs(posA);
    }
    else {
      maxx = abs(posC);
    }
  }
  else {
    if (abs(posB) >= abs(posC)) {
      maxx = abs(posB);
    }
    else {
      maxx = abs(posC);
    }
  }

  return (long)(((maxx * 100800 / 360) / vel) * 1000);
}

void checkButton() {
  if ((digitalRead(SEL_A) == 0) && (digitalRead(SEL_B) == 1)) //A
  {
    if (digitalRead(BT_A) == 0)  //premuto
    {
      if (digitalRead(SEL_Gp)) //1 è piccolo
      {
        Serial.println("motore A orario");
        muovi('p', vel_passetti, passetto, 0);
      }
      else
      {
        Serial.println("motore C orario");
        muovi('g', vel_passetti, passetto,0);
      }
      delay(1000);
    }
    else if (digitalRead(BT_B) == 1)  //premuto
    {
      if (digitalRead(SEL_Gp)) //1 è piccolo
      {
        Serial.println("motore A antiorario");
        muovi('p', vel_passetti, -passetto, 0);
      }
      else
      {
        Serial.println("motore C antiorario");
        muovi('g',vel_passetti,-passetto, 0, 0);
      }
      delay(1000);
    }
  }
  else if ((digitalRead(SEL_A) == 1) && (digitalRead(SEL_B) == 1)) //B
  {
    if (digitalRead(BT_A) == 0)  //premuto
    {
      if (digitalRead(SEL_Gp)) //1 è piccolo
      {
        Serial.println("motore B orario");
        muovi('p',vel_passetti,0, passetto);
      }
      else
      {
        Serial.println("motore D orario");
        muovi('g',vel_passetti,0, passetto, 0);
      }
      delay(1000);
    }
    else if (digitalRead(BT_B) == 1)  //premuto
    {
      if (digitalRead(SEL_Gp)) //1 è piccolo
      {
        Serial.println("motore B antiorario");
        muovi('p',vel_passetti,0, -passetto);
      }
      else
      {
        Serial.println("motore D antiorario");
        muovi('g',vel_passetti,0, -passetto, 0);
      }

      delay(1000);
    }
  }
  else if ((digitalRead(SEL_A) == 1) && (digitalRead(SEL_B) == 0)) //C
  {
    if (digitalRead(BT_A) == 0)  //premuto
    {
      if (digitalRead(SEL_Gp)) //1 è piccolo
      {
        Serial.println("motore inesistente");
      }
      else
      {
        Serial.println("motore E orario");
        muovi('g',vel_passetti,0, 0, passetto);
      }
      delay(1000);
    }
    else if (digitalRead(BT_B) == 1)  //premuto
    {
      if (digitalRead(SEL_Gp)) //1 è piccolo
      {
        Serial.println("motore inesistente");
      }
      else
      {
        Serial.println("motore E antiorario");
        muovi('g',vel_passetti,0, 0, -passetto);
      }
      delay(1000);
    }
  }
}
