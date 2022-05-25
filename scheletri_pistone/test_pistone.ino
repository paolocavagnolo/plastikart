#define PROPVALVE 9
#define PISTVALVE 7

#define REMOTEBTN 12
#define PISTBTN 11
#define SPEEDPOT A5


void setup() {
// put your setup code here, to run once:

pinMode(PROPVALVE, OUTPUT);
pinMode(PISTVALVE, OUTPUT);
pinMode(REMOTEBTN, INPUT_PULLUP);
pinMode(PISTBTN, INPUT_PULLUP);

}

void loop() {

  if (digitalRead(REMOTEBTN)) {
    //MANUAL
    
    analogWrite(PROPVALVE, map(analogRead(A5), 1023, 0, 0, 255));
    
    if (digitalRead(PISTBTN)) {
      digitalWrite(PISTVALVE, HIGH);
    }
    else {
      digitalWrite(PISTVALVE, LOW);
    }
    
  }
  else {
    //AUTO

    //vai su lento
    analogWrite(PROPVALVE, 100);
    digitalWrite(PISTVALVE, LOW);
    delay(1500);

    //torna giu veloce
    analogWrite(PROPVALVE, 255);
    digitalWrite(PISTVALVE, HIGH);

    //aspetta 3 sec
    delay(3000);
    
  }

}
