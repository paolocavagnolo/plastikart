#define SWITCH 12

#define RE 6
#define DE 7

uint8_t tracks[16] = {53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38};

void setup() {

  Serial.begin(9600);
  Serial2.begin(4800);

  pinMode(SWITCH, INPUT_PULLUP);
 
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(RE, HIGH);
  digitalWrite(DE, HIGH);

}

uint32_t dataOut = 0;
long dataIn = 0;

char tag;
bool inv = false;

String inString = "";

void loop() {

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
          break;
        case 'A':
          if (dataIn > 360) { //vel A
            dataOut = dataIn + 1500000;
          }
          else { //abs A
            dataOut = dataIn * (100800 / 360) + 16500000;
          }
          Serial.print(tag);
          Serial2.print(dataOut);
          break;
        case 'b':   //pos B
          dataOut = dataIn * (100800 / 360) + 2500000;
          Serial.print(tag);
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
          Serial2.print(dataOut);
          break;
        case 'c':   //pos C
          dataOut = dataIn * (100800 / 360) + 6500000;
          Serial.print(tag);
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
          Serial2.print(dataOut);
          break;
        case 'd':   //pos D
          dataOut = dataIn * (100800 / 360) + 8500000;
          Serial.print(tag);
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
          Serial2.print(dataOut);
          break;
        case 'e':   //pos E
          dataOut = dataIn * (100800 / 360) + 10500000;
          Serial.print(tag);
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
          Serial2.print(dataOut);
          break;
        case 's':
          dataOut = 15500000;
          Serial.println("stop");
          Serial2.print(dataOut);
          break;
        case 'z':
          switch (dataIn) {
            case 1:
              dataOut = 4500000;
              Serial2.print(dataOut);
              break;
            case 2:
              dataOut = 5500000;
              Serial2.print(dataOut);
              break;
            case 3:
              dataOut = 12500000;
              Serial2.print(dataOut);
              break;
            case 4:
              dataOut = 13500000;
              Serial2.print(dataOut);
              break;
            case 5:
              dataOut = 14500000;
              Serial2.print(dataOut);
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

      Serial.print(dataIn);
      Serial.print(" // ");
      Serial.println(dataOut);

      inString = "";

    }
  }
}
