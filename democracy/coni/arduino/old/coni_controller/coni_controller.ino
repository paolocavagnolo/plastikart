#define L1 12
#define L2 11
#define L3 10

#define L4 9
#define L5 8
#define L6 7

#define POT1 A0
#define POT2 A10
#define POT3 A8
#define POT4 A5
#define POT5 A2

#define DE 6
#define RE 7

#define MIN 480
#define MAX 530

int pos[5] = {0, 0, 0, 0, 0};

void setup() {
  //enable transmission on RS485 bus
  pinMode(DE, OUTPUT);
  pinMode(RE, OUTPUT);
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  Serial2.begin(9600);

  //led
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);

  pinMode(13, OUTPUT);

  while (!pot_position(&pos[0])) {
    digitalWrite(13, LOW);
  }

  digitalWrite(13, HIGH);

  Serial.begin(9600);

}

long t = 0;

void loop() {
  
  pot_position(&pos[0]);
  
  if ((millis() - t) > 1000) {
    pot_transmission(&pos[0]);
    t = millis();
  }
  
}

bool pot_position(int *ppos) {
  bool p[5] = {0, 0, 0, 0, 0};

  ppos[0] = analogRead(POT1);
  ppos[1] = analogRead(POT2);
  ppos[2] = analogRead(POT3);
  ppos[3] = analogRead(POT4);
  ppos[4] = analogRead(POT5);

  for (int i = 0; i < 5; i++) {
    if ((ppos[i] > MIN) && (ppos[i] < MAX)) {
      digitalWrite(12 - i, HIGH);
      p[i] = true;
    }
    else {
      digitalWrite(12 - i, LOW);
      p[i] = false;
    }
  }

  if (p[0] && p[1] && p[2] && p[3] && p[4]) {
    return true;
  }
  else {
    return false;
  }

}

void pot_transmission(int *pval) {
  for (int i=0; i<5; i++) {
    Serial2.println(pval[i]+1024*i);
  }

}




