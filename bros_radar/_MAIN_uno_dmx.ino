#include <Conceptinetics.h>

#define DMX_SLAVE_CHANNELS   1

DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );


void setup() {

  dmx_slave.enable ();

  dmx_slave.setStartAddress (510);
  pinMode(8,OUTPUT);
  digitalWrite(8, HIGH);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);

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
