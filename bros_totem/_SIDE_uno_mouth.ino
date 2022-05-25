#include <Servo.h> 

Servo myservo;  

void setup() {

  delay(100);
  
  myservo.attach(9);  

  delay(100);
  
  pinMode(5, INPUT);
  
  myservo.write(0);
  
}

bool state = true;

void loop() {

  if (digitalRead(5)) {
    if (state) {
      myservo.write(90);
      state = false;
      delay(600);
    }
  }
  else {
    if (!state) {
      myservo.write(0);
      state = true;
      delay(600);
    }
  }
  
}
