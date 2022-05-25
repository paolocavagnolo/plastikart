#define zampaAS 8
#define zampaAD 6
#define zampaPS 7
#define zampaPD 5

#define piede A0
#define tamburo 2

int z[4] = {zampaAS, zampaAD, zampaPS, zampaPD};

void setup() {
  Serial.begin(9600);

  pinMode(zampaAS,OUTPUT);
  pinMode(zampaAD,OUTPUT);
  pinMode(zampaPS,OUTPUT);
  pinMode(zampaPD,OUTPUT);

  pinMode(piede,OUTPUT);
  pinMode(tamburo,OUTPUT);

  digitalWrite(zampaAS,LOW);
  digitalWrite(zampaAD,LOW);
  digitalWrite(zampaPS,LOW);
  digitalWrite(zampaPD,LOW);

  digitalWrite(piede,LOW);
  digitalWrite(tamburo,LOW);

}

int a = 0;

void loop() {

  for (int i=0; i<4; i++) {
    Serial.print("Gamba numero: ");
    Serial.println(z[i]);

    for (int j=0; j<=20; j+=2) {
      a = j * 50;
      Serial.print(a);
      delay(2000);
      Serial.println(".");

      //testo
      digitalWrite(z[i],HIGH);
      delay(a);
      digitalWrite(z[i],LOW); 
    }
  }
  
}
