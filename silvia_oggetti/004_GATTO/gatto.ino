#include <Servo.h>

Servo zampa; // orecchie
Servo coda; // collo

int pos = 0;    // variable to store the servo position

void setup() {
  
  coda.attach(5);
  zampa.attach(3);

  //ZERO CHECK
  coda.write(95);
  zampa.write(95);
  
}

void loop() {
  for (pos = 95; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    coda.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 95; pos -= 1) { // goes from 180 degrees to 0 degrees
    coda.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 95; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    zampa.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 95; pos -= 1) { // goes from 180 degrees to 0 degrees
    zampa.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 95; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    coda.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 95; pos -= 1) { // goes from 180 degrees to 0 degrees
    coda.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  while(true);
}
