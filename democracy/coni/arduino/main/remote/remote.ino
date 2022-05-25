void setup() {

  Serial.begin(9600);
  Serial2.begin(4800);

  pinMode(12, INPUT_PULLUP);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

}

bool oki = false;
uint32_t dataOut = 0;
long dataIn = 0;
char tag;
bool inv = false;

String inString = "";

void loop() {
  /*// put your main code here, to run repeatedly:
    if (digitalRead(12)) {
    digitalWrite(52,HIGH);
    if (oki) {
      Serial2.println("ciao");
      oki = false;
    }
    }
    else {
    digitalWrite(52,LOW);
    oki = true;
    }*/
  if (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    else {
      if ((inChar != '\n') && (inChar != '-')) {
        tag = ((char)inChar);
      }
      else if (inChar == '-') {
        inv = true;
      }
    }

    if (inChar == '\n') {

      dataIn = inString.toInt();
      if (inv) {
        dataIn *= -1;
        inv = false;
      }

      switch (tag) {
        case 'a':   //pos A
          dataOut = dataIn * (100800 / 360) + 500000;
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'A':
          if (dataIn > 360) { //vel A
            dataOut = dataIn + 1500000;
          }
          else { //abs A
            dataOut = dataIn * (100800 / 360) + 16500000;
          }
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'b':   //pos B
          dataOut = dataIn * (100800 / 360) + 2500000;
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'B':   //vel B
          if (dataIn > 360) { //vel B
            dataOut = dataIn + 3500000;
          }
          else { //abs B
            dataOut = dataIn * (100800 / 360) + 17500000;
          }
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'c':   //pos C
          dataOut = dataIn * (100800 / 360) + 6500000;
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'C':
          if (dataIn > 360) { //vel C
            dataOut = dataIn + 7500000;
          }
          else { //abs C
            dataOut = dataIn * (100800 / 360) + 18500000;
          }
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'd':   //pos D
          dataOut = dataIn * (100800 / 360) + 8500000;
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'D':
          if (dataIn > 360) { //vel D
            dataOut = dataIn + 9500000;
          }
          else { //abs D
            dataOut = dataIn * (100800 / 360) + 19500000;
          }
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'e':   //pos E
          dataOut = dataIn * (100800 / 360) + 10500000;
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'E':
          if (dataIn > 360) { //vel E
            dataOut = dataIn + 11500000;
          }
          else { //abs E
            dataOut = dataIn * (100800 / 360) + 20500000;
          }
          Serial.print(tag);
          Serial.print(dataIn);
          Serial.print(" // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 's':
          dataOut = 15500000;
          Serial.print("Stop // ");
          Serial.println(dataOut);
          Serial2.print(dataOut);
          break;
        case 'z':
          Serial.println("z");
          Serial.println(dataOut);
          switch (dataIn) {
            case 1:
              Serial.print("zerosA // ");
              Serial.println(4500000);
              Serial2.print(4500000);
              break;
            case 2:
              Serial.print("zerosB // ");
              Serial.println(5500000);
              Serial2.print(5500000);
              break;
            case 3:
              Serial.print("zerosC // ");
              Serial.println(12500000);
              Serial2.print(12500000);
              break;
            case 4:
              Serial.print("zerosD // ");
              Serial.println(13500000);
              Serial2.print(13500000);
              break;
            case 5:
              Serial.print("zerosE // ");
              Serial.println(14500000);
              Serial2.print(14500000);
              break;
            default:
              Serial.println("motore non esistente");
              break;
          }
          break;
        default:
          Serial.println("comando inesistente");
          break;
      }

      inString = "";

    }
  }
}
