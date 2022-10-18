//FLIPPER - VERSION 1.0

#define NR 32

uint8_t relay[NR] = {14, 9, 15, 8, 16, 7, 17, 6, 18, 5, 19, 4, 20, 3, 21, 2, 23, 36, 25, 34, 27, 32, 29, 30, 31, 28, 33, 26, 35, 24, 37, 22};

void setup() {
  // put your setup code here, to run once:
  for (uint8_t i = 0; i < NR; i++) {
    pinMode(relay[i], OUTPUT);
  }

  for (uint8_t i = 0; i < NR; i++) {
    digitalWrite(relay[i], HIGH);
  }

}

void fontana(uint8_t tt) {
  int cc = 0;
  int ac = 0;
  int j = 0;
  for (uint8_t x = 0; x <= 16 + 6; x++) {
    cc = 11 + x; //da 11 a 26
    ac = 11 - x; //da 11 a 0, poi 31-30-29-28-27
    if (ac < 0) {
      ac = 32 + ac;
    }
    if (x <= 16) {
      digitalWrite(relay[cc], LOW);
      digitalWrite(relay[ac], LOW);
    }

    if (x >= 6) {
      j = x - 6;
      cc = 11 + j; //da 11 a 26
      ac = 11 - j; //da 11 a 0, poi 31-30-29-28-27
      if (ac < 0) {
        ac = 32 + ac;
      }
      digitalWrite(relay[cc], HIGH);
      digitalWrite(relay[ac], HIGH);

    }

    delay(50+20*tt);

  }
}


void spegni() {
  for (uint8_t i = 0; i < NR; i++) {
    digitalWrite(relay[i], HIGH);
  }
}

void accendi() {
  for (uint8_t i = 0; i < NR; i++) {
    digitalWrite(relay[i], LOW);
  }
}

void caso() {
  uint8_t x;
  x = random(0, 32);
  digitalWrite(relay[x], LOW);
  x = random(0, 32);
  digitalWrite(relay[x], HIGH);

}

void giro() {
  for (uint8_t i = 0; i < NR; i++) {
    digitalWrite(relay[i], LOW);
    delay(100);
    digitalWrite(relay[i], HIGH);
    delay(100);
  }
}

void scalasync() {
  for (uint8_t i = 0; i < NR - 3; i++) {
    digitalWrite(relay[i + 3], LOW);
    delay(30);
    digitalWrite(relay[i + 2], LOW);
    delay(30);
    digitalWrite(relay[i + 1], LOW);
    delay(30);
    digitalWrite(relay[i], HIGH);
    delay(30);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  spegni();

  for (uint8_t j = 0; j < 4; j++) {
    fontana(j);
  }


  delay(1000);
  for (uint8_t j = 0; j < 24; j++) {
    caso();
    delay(150);
  }
  spegni();
  delay(3000);
  
  accendi();
  delay(1000);
  spegni();
  
  scalasync();
  spegni();
  scalasync();

  accendi();
  for (uint8_t j = 0; j < 200; j++) {
    caso();
    delay(75);
  }
  giro();

  spegni();
  delay(1000);

}
