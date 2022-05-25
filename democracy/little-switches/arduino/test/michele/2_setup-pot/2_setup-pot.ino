void setup() {
  Serial.begin(9600);
}

void loop() {
  
  Serial.print("A3: ");
  Serial.println(analogRead(A3));
  delay(500);
}
