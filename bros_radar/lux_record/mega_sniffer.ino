const uint16_t uspf = 33362;
unsigned long frameT = 0;
int frame = 0;
int maxFrame = 17216;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  if ((micros() - frameT) > uspf) {
    
    frameT = micros();
    
    frame = frame + 1;
    
    if (analogRead(A0) > 500) {
      Serial.println("1");
    }
    else {
      Serial.println("0");
    }

  }
    
  

}
