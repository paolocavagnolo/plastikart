

long mot1[2][45] = {{0,1817,11317,11770,12494,13265,14489,15265,16520,18255,32000,33817,43984,45796,84505,85276,86473,87234,88531,90229,170968,171739,172947,173713,174979,176697,510760,511536,512739,513520,514796,516531,535229,535984,537213,537984,539223,540937}, { 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64, 127, 64}};
long zero = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  zero = millis();
}

int clk = 0;

void loop() {
  // put your main code here, to run repeatedly:

  if ((millis() - zero) > mot1[0][clk]) {
    if (clk < 45) {
      muovi(mot1[1][clk]);
      clk++;
    }
    else {
      ferma();
    }
  }

}

void muovi(long vel) {
  if (vel == 64) {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  else if (vel > 64) {
    digitalWrite(5, LOW);
    analogWrite(6, map(vel, 64, 127, 0, 255));
  }
  else if (vel < 64) {
    digitalWrite(6, LOW);
    analogWrite(5, map(vel, 64, 0, 0, 255));
  }
}

void ferma() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

