#define LED 13

void setup() {
  pinMode(LED, OUTPUT);

  Serial2.begin(9600);
  Serial.begin(9600);

  Serial.println("start!");
  digitalWrite(LED, LOW);
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


