#include <SPI.h>
#include <SD.h>

#define rec_s 5
#define rec_led 10
#define ply_s 6
#define ply_led 11

#define mt1_s 7
#define mt2_s 8
#define lux_s 9

#define mt1_p A1
#define mt2_p A2
#define lux_p A3

#define mt1_pwm 20
#define mt2_pwm 21
#define lux_pwm 22

#define MAX_LEN 20000

float mt1[MAX_LEN];
float mt2[MAX_LEN];
float lux[MAX_LEN];

File myFile;

void setup() {

  pinMode(rec_s, INPUT_PULLUP);
  pinMode(ply_s, INPUT_PULLUP);
  pinMode(mt1_s, INPUT_PULLUP);
  pinMode(mt2_s, INPUT_PULLUP);
  pinMode(lux_s, INPUT_PULLUP);

  pinMode(rec_led, OUTPUT);
  pinMode(ply_led, OUTPUT);

  Serial.begin(9600);
  
  if (!SD.begin(4)) {
    Serial.println("SD failed!");
    while (1);
  }
  
  Serial.println("SD ok.");
  
}

bool rec_on = false;

void loop() {

  if (digitalRead(rec_s) && !digitalRead(ply_s)) {
    digitalWrite(rec_led, HIGH);
    digitalWrite(ply_led, LOW);
    rec_on = true;
  }

  else if (digitalRead(ply_s) && !digitalRead(rec_s)) {
    digitalWrite(ply_led, HIGH);
    digitalWrite(rec_led, LOW);
  }
  
  else if (!digitalRead(ply_s) && !digitalRead(rec_s)) {
    digitalWrite(rec_led, LOW);
    digitalWrite(ply_led, LOW);
  }

  if (digitalRead(mt1_s)) {
    analogWrite(mt1_pwm,map(analogRead(mt1_p),0,1023,0,254));
  }
  else {
    digitalWrite(mt1_pwm,LOW);
  }

  if (digitalRead(mt2_s)) {
    analogWrite(mt2_pwm,map(analogRead(mt2_p),0,1023,0,254));
  }
  else {
    digitalWrite(mt2_pwm,LOW);
  }

  if (digitalRead(lux_s)) {
    analogWrite(lux_pwm,map(analogRead(lux_p),0,1023,0,254));
  }
  else {
    digitalWrite(mt1_pwm,LOW);
  }


  if (rec_on) {
    if (!digitalRead(rec_s)) {
      rec_on = false;
      writeToSd(mt1, mt2, lux);
    }
  }
  
}


void writeToSd(float *mot1, float *mot2, float *lux) {

  myFile = SD.open("test.txt", FILE_WRITE);
  myFile.println(i);
  myFile.close();
  
}
