
#include <DmxMaster.h>

void setup() {

  DmxMaster.usePin(3);
  DmxMaster.maxChannel(4);
  
  // Serial.begin(9600);
  // Serial.flush();
  // while (!Serial);
  // Serial.println("zampe,occhi,collo,becco");
}

int ch;

int v[] = { 0, 0, 0, 0 };
int s[] = { 13, 4, 15, 4 };
unsigned long t[] = { 0, 0, 0, 0 };

int i = 0;
int ss = 0;

bool fU[] = { 0, 0, 0, 0 };
bool fD[] = { 1, 1, 1, 1 };

int d[] = { 0, 0, 0, 0 };

int oState = 0;
int bState = 0;

unsigned long dt = 0;

void loop() {

  zampe();

  occhi();

  collo();

  becco();

  // stampa();
}

void zampe() {
  if ((millis() - t[0]) > s[0]) {
    t[0] = millis();

    if (fD[0]) {
      s[0] = 13;
      if (v[0] > 255) {
        v[0] = 255;
        fU[0] = 1;
        fD[0] = 0;
        s[0] = 2000;
      } else {
        v[0] = v[0] + 4;
      }
    } else {
      s[0] = 13;
      if (v[0] < 0) {
        v[0] = 0;
        fD[0] = 1;
        fU[0] = 0;
        s[0] = 2000;
      } else {
        v[0] = v[0] - 4;
      }
    }

    DmxMaster.write(1, v[0]);
  }
}

void occhi() {
  if ((millis() - t[1]) > s[1]) {
    t[1] = millis();
    if (oState == 0) {
      oState = 255;
      s[1] = random(300, 2000);  //tempo aperti
    } else {
      oState = 0;
      s[1] = random(400, 600);  //tempo chiuso
    }
    DmxMaster.write(2, oState);
  }
}

void collo() {
  if ((millis() - t[2]) > s[2]) {
    t[2] = millis();

    if (fD[2]) {
      s[2] = 15;
      if (v[2] > 255) {
        v[2] = 255;
        fU[2] = 1;
        fD[2] = 0;
        s[2] = 1000;
      } else {
        v[2] = v[2] + 2;
      }
    } else {
      s[2] = 15;
      if (v[2] < 0) {
        v[2] = 0;
        fD[2] = 1;
        fU[2] = 0;
        s[2] = 1000;
      } else {
        v[2] = v[2] - 2;
      }
    }

    DmxMaster.write(3, v[2]);
  }
}

void becco() {
  if ((millis() - t[3]) > s[3]) {
    t[3] = millis();
    if (bState == 0) {
      bState = 255;
      s[3] = random(600, 800);  //tempo aperto
    } else {
      bState = 0;
      s[3] = random(300, 2000);  //tempo chiuso
    }
    DmxMaster.write(4, bState);
  }
}

void valori(int ccc, int vvv) {
  d[ccc-1] = vvv;
}

void stampa() {
  if ((millis() - dt) > 50) {
    dt = millis();
    Serial.print(d[0]);
    Serial.print(",");
    Serial.print(d[1]);
    Serial.print(",");
    Serial.print(d[2]);
    Serial.print(",");
    Serial.print(d[3]);
    Serial.println();
  }
}
