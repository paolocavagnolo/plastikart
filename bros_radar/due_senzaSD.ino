#include <SPI.h>
#include <SD.h>

#define rec_s 41
#define rec_led 30
#define play_s 43
#define play_led 31

#define mt1_s 45
#define mt2_s 49
#define lux_s 47

#define mt1_p A4
#define mt2_p A3
#define lux_p A5

#define mt1_pwm 12
#define mt2_pwm 11
#define lux_pwm 5
#define lux_relay 51

#define mt1_relay 52
#define mt2_relay 35

#define MAX_LEN 20000

uint8_t mt1[MAX_LEN];
uint8_t mt2[MAX_LEN];
uint8_t lux[MAX_LEN];

const uint16_t uspf = 33362;
//const uint16_t uspf = 100000;

File myFile;

void setup() {
  
  pinMode(rec_s, INPUT_PULLUP);
  pinMode(play_s, INPUT_PULLUP);
  pinMode(mt1_s, INPUT_PULLUP);
  pinMode(mt2_s, INPUT_PULLUP);
  pinMode(lux_s, INPUT_PULLUP);

  pinMode(rec_led, OUTPUT);
  pinMode(play_led, OUTPUT);

  pinMode(mt1_pwm, OUTPUT);
  pinMode(mt1_relay, OUTPUT);
  pinMode(mt2_pwm, OUTPUT);
  pinMode(mt2_relay, OUTPUT);
  pinMode(lux_pwm, OUTPUT);
  pinMode(lux_relay, OUTPUT);
  
  Serial.begin(9600);
  
  if (!SD.begin(4)) {
    Serial.println("SD failed!");
    while (1);
  }
  
  Serial.println("SD ok.");

  //DA FILE SU SD A VETTORI
  //populateVectors(mt1, mt2, lux);
}

bool rec = false;
bool play = false;

unsigned long triacTup = 0;
unsigned long triacTdown = 0;
bool tUp = true;
bool tDown = false;

uint8_t mt1_value;
uint8_t mt2_value;
uint8_t lux_value;

bool recStart = false;
bool playStart = false;
unsigned long frameT = 0;
int frame = 0;
int frameCOUNT = 0;

unsigned long deB = 0;

void loop() {
  
  modeState();
  
  if (!play) {
    controlState();
    if (rec) {
      if (!recStart) {
        Serial.println("START REC");
        recStart = true;
        frame = 0;
        frameT = micros();
      }
      record();
    }
    act();
  }
  
  else {
    if (!playStart) {
      Serial.println("START PLAY");
      playStart = true;
      frame = 0;
      frameT = micros();
    }
    goPlay();
    act();
  }
  
}

void goPlay() {

  if ((micros() - frameT) > uspf) {
    frameT = micros();
    
    frame = frame + 1;

    if (frame >= frameCOUNT) {
      while (!digitalRead(play_s)) {
        kill();
        digitalWrite(play_led,HIGH);
        delay(50);
        digitalWrite(play_led,LOW);
        delay(200);
      }
    }
    
    lux_value = lux[frame]; 
    mt1_value = mt1[frame];
    mt2_value = mt2[frame];

    if (!(mt1_value % 2)) {
      digitalWrite(mt1_relay,LOW);
    }
    else {
      digitalWrite(mt1_relay,HIGH);
    }

    if (!(mt2_value % 2)) {
      digitalWrite(mt2_relay,LOW);
    }
    else {
      digitalWrite(mt2_relay,HIGH);
    }

    if (!(lux_value % 2)) {
      digitalWrite(lux_relay,LOW);
    }
    else {
      digitalWrite(lux_relay,HIGH);
    }
    
  }
  
}

void record() {
  
  if ((micros() - frameT) > uspf) {
    
    frameT = micros();

    if (frame >= MAX_LEN - 1) {
      while(!digitalRead(rec_s)) {
      
        digitalWrite(rec_led,HIGH);
        delay(500);
        digitalWrite(rec_led,LOW);
        delay(750);
      }
      return;
    }
    
    frame = frame + 1;

    lux[frame] = lux_value;
    mt1[frame] = mt1_value;
    mt2[frame] = mt2_value;

  }
}

void act() {
  analogWrite(mt1_pwm,mt1_value);
  analogWrite(mt2_pwm,mt2_value);
  triac(lux_value*4);
}

void kill() {
  digitalWrite(mt1_relay, LOW);
  digitalWrite(mt1_pwm, LOW);
  digitalWrite(mt2_relay, LOW);
  digitalWrite(mt2_pwm, LOW);
  digitalWrite(lux_relay, LOW);
  digitalWrite(lux_pwm, LOW);
}

void modeState() {
  
  if (!digitalRead(rec_s) and !play) {
    rec = true;
    digitalWrite(rec_led, HIGH);
    deB = millis();
  }
  else {
    if ((millis() - deB) > 200 and recStart) {
      recStart = false;
      frameCOUNT = frame;
      Serial.println("REC STOP");
    }
    rec = false;
    digitalWrite(rec_led, LOW);
  }

  if (!digitalRead(play_s) and !rec) {
    play = true;
    digitalWrite(play_led, HIGH);
    deB = millis();
  }
  else {
    if ((millis() - deB) > 200 and playStart) {
      playStart = false;
      Serial.println("PLAY STOP");
      digitalWrite(lux_relay,LOW);
      digitalWrite(mt1_relay,LOW);
      digitalWrite(mt2_relay,LOW);
    }
    play = false;
    digitalWrite(play_led, LOW);
  }
  
}

void controlState() {

  mt1_value = analogRead(mt1_p)/4;
  
  if (!digitalRead(mt1_s)) {
    digitalWrite(mt1_relay, HIGH);
    if (!(mt1_value % 2)) {
      mt1_value = mt1_value + 1; //solo valori dispari con relè acceso.
    }
  }
  else {
    digitalWrite(mt1_relay, LOW);
    if ((mt1_value % 2)) {
      mt1_value = mt1_value + 1; //solo valori pari con relè spento.
    }
  }

  mt2_value = analogRead(mt2_p)/4;

  if (!digitalRead(mt2_s)) {
    digitalWrite(mt2_relay, HIGH);
    if (!(mt2_value % 2)) {
      mt2_value = mt2_value + 1; //solo valori dispari con relè acceso.
    }
  }
  else {
    digitalWrite(mt2_relay, LOW);
    if ((mt2_value % 2)) {
      mt2_value = mt2_value + 1; //solo valori pari con relè spento.
    }
  }

  lux_value = analogRead(lux_p)/4;

  if (!digitalRead(lux_s)) {
    digitalWrite(lux_relay, HIGH);
    if (!(lux_value % 2)) {
      lux_value = lux_value + 1; //solo valori dispari con relè acceso.
    }
  }
  else {
    digitalWrite(lux_relay, LOW);
    if ((lux_value % 2)) {
      lux_value = lux_value + 1; //solo valori pari con relè spento.
    }
  }
}

void triac(int value) {
  int x = map(value,0,1900,29,1);
  if ((micros() - triacTup) > x*1000 and tUp) {
    tUp = false;
    tDown = true;
    triacTdown = micros();
    digitalWrite(lux_pwm, HIGH);
  }
  if ((micros() - triacTdown) > (30-x)*1000 and tDown) {
    tDown = false;
    tUp = true;
    triacTup = micros();
    digitalWrite(lux_pwm, LOW);
  }
}


void writeToSd(float *mot1, float *mot2, float *lux) {

  myFile = SD.open("test.txt", FILE_WRITE);
  //myFile.println(i);
  myFile.close();
  
}
