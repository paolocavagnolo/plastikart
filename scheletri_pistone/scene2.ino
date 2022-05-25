#include <Controllino.h>

//INPUT
const byte csScn1 = CONTROLLINO_A0;
const byte csScn2 = CONTROLLINO_A1;

const byte swAuto = CONTROLLINO_A2;

const byte swScn1 = CONTROLLINO_A3;
const byte swScn2 = CONTROLLINO_A4;


//OUTPUT
const byte evVel = CONTROLLINO_D6;
const byte evPos = CONTROLLINO_D7;


void setup() {

  pinMode(evPos, OUTPUT);
  pinMode(evVel, OUTPUT);

  pinMode(csScn1, INPUT);
  pinMode(csScn2, INPUT);
  pinMode(swScn1, INPUT);
  pinMode(swScn2, INPUT);
  pinMode(swAuto, INPUT);

  digitalWrite(evPos, LOW);
  digitalWrite(evVel, LOW);


}

uint8_t oneshot1 = 0;
uint8_t oneshot2 = 0;

void loop() {

  //AUTO
  if ((digitalRead(csScn1) && digitalRead(swAuto)) || (digitalRead(swScn1) && !digitalRead(swAuto))) {

  delay(50);

    if (!oneshot1) {

      //SCENE FAST // OLD // STRONG
      digitalWrite(evVel, LOW);
      digitalWrite(evPos, HIGH);

      delay(1500);

      digitalWrite(evVel, HIGH);
      digitalWrite(evPos, LOW);

      delay(500);
      oneshot1 = 1;
    }

  }
  else {
    oneshot1 = 0;
  }



  if ((digitalRead(csScn2) && digitalRead(swAuto)) || ((analogRead(swScn2) > 512) && !digitalRead(swAuto))) {

  delay(50);

    if (!oneshot2) {

      //SCENE SLOW // NEW // WEAK
      digitalWrite(evVel, LOW);
      digitalWrite(evPos, HIGH);

      delay(1500);

      digitalWrite(evVel, LOW);
      digitalWrite(evPos, LOW);

      delay(500);
      oneshot2 = 1;
    }
  }
  else {
    oneshot2 = 0;
  }

  digitalWrite(evVel, LOW);
  digitalWrite(evPos, LOW);
}
