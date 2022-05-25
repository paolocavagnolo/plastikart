#include <Servo.h> 

Servo myservo;  

void setup() {
  
  myservo.attach(9);   
  pinMode(5, INPUT);
  
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
