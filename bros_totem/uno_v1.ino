#include <Conceptinetics.h>

#define DMX_SLAVE_CHANNELS   1

DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

void setup() {

  dmx_slave.enable ();
  dmx_slave.setStartAddress (2);

  pinMode(8,OUTPUT);
  digitalWrite(8, HIGH);

}

unsigned long dmxT = 0;
bool playOn = false;

void loop() {

  if (dmx_slave.getChannelValue(1) > 60 and !playOn) {
    playOn = true;
    digitalWrite(8,LOW);
    dmxT = millis();
  }

  if ((millis() - dmxT) > 100 and dmx_slave.getChannelValue(1) < 60) {
    playOn = false;
    digitalWrite(8, HIGH);
  }


}
