#include <Conceptinetics.h>

#define DMX_SLAVE_CHANNELS   4

DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );


void setup() {

  dmx_slave.enable ();

  dmx_slave.setStartAddress (1);
  pinMode(8,OUTPUT);

}

int dmxMove;

void loop()
{

  if (dmx_slave.getChannelValue(1) > 60) {
    digitalWrite(8, HIGH);
  }
  else {
    digitalWrite(8, LOW);
  }

  
}
