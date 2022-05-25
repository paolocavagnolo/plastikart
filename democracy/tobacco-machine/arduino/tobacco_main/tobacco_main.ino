#define DE 6
#define RE 7

#define LED 13

void setup() {
  // put your setup code here, to run once:
  pinMode(DE, OUTPUT);
  pinMode(RE, OUTPUT);
  pinMode(LED, OUTPUT);

  Serial2.begin(9600);
  Serial.begin(9600);


  Serial.println("start!");
  digitalWrite(LED, LOW);
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
}

long now = 0;
long n = 0;
bool bl = false;


void loop() {
  // put your main code here, to run repeatedly:

  if ((millis() - now) > 2000) {
    Serial2.println("m1:255;");
    now = millis();
    n = millis();
    bl = true;
  }

  if (bl) {
    digitalWrite(LED, HIGH);
    if ((millis() - n) > 500) {
      digitalWrite(LED, LOW);
      bl = false;
    }
  }

}


