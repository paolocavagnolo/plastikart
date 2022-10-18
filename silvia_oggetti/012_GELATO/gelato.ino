//ICECREAM - VERSION 1.0

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

  //activate the Orange
  
  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, HIGH);
  delay(500);
  digitalWrite(RR1, LOW);
  digitalWrite(RR2, HIGH);

  delay(20000); //wait 20 seconds

  //activate the Violet

  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, HIGH);
  delay(500);
  digitalWrite(RR3, LOW);
  digitalWrite(RR4, HIGH);

  //ASPETTA 
  delay(60000*20); //wait 20 minute

  //send closing signal
  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, HIGH);

  delay(500);

  digitalWrite(RR1, HIGH);
  digitalWrite(RR2, LOW);

delay(500);
  
  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, HIGH);

  delay(500);

  digitalWrite(RR3, HIGH);
  digitalWrite(RR4, LOW);

  
  while(true);
}
