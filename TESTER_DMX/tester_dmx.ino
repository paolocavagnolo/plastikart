
#include <DmxMaster.h>

void setup() {

  DmxMaster.usePin(3);

  DmxMaster.maxChannel(4);

}

int val;
int ch;

void loop() {

    //uno per volta lentamente
    for (ch = 1; ch <= 4; ch++) {
      for (val = 0; val <= 255; val++) {
        DmxMaster.write(ch, val);
        delay(15);
      }
      delay(1000);
      for (val = 255; val >= 0; val--) {
        DmxMaster.write(ch, val);
        delay(15);
      }
      delay(1000);
    }
  
    //uno per volta velocemente
    for (ch = 1; ch <= 4; ch++) {
      for (val = 0; val <= 255; val++) {
        DmxMaster.write(ch, val);
        delay(3);
      }
      delay(1000);
      for (val = 255; val >= 0; val--) {
        DmxMaster.write(ch, val);
        delay(3);
      }
      delay(1000);
    }
  
    //tutti insieme vel media per sempre
    while (true) {
   ; val++) {
        DmxMaster.write(1, val);
        DmxMaster.write(2, val);
        DmxMaster.write(3, val);
        DmxMaster.write(4, val);
        delay(5);
      }
      delay(1000);
      for (val = 255; val >= 0; val--) {
        DmxMaster.write(1, val);
        DmxMaster.write(2, val);
        DmxMaster.write(3, val);
        DmxMaster.write(4, val);
        delay(5);
      }
      delay(1000);
  
    }

}
