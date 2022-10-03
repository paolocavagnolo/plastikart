#define RR1 8
#define RR2 9
#define RR3 10
#define RR4 11


void setup() {
  // put your setup code here, to run once:
  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, LOW);
  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, LOW);
  
  pinMode(RR1, OUTPUT);
  pinMode(RR2, OUTPUT);
  pinMode(RR3, OUTPUT);
  pinMode(RR4, OUTPUT);

  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, LOW);
  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, LOW);


}

void loop() {
  // put your main code here, to run repeatedly:

  //ATTIVA IL PRIMO
  
  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, HIGH);
  delay(500);
  digitalWrite(RR1, LOW);
  digitalWrite(RR2, HIGH);

  delay(20000);

  //ATTIVA IL SECONDO

  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, HIGH);
  delay(500);
  digitalWrite(RR3, LOW);
  digitalWrite(RR4, HIGH);

  //ASPETTA 10 SECONDI
  delay(20000);

  //MANDA SEGNALE CHIUSURA A TUTTI E DUE
  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, HIGH);

  delay(500);

  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, LOW);

  delay(20000);
  
  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, HIGH);

  delay(500);

  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, LOW);

  
  while(true);
}
