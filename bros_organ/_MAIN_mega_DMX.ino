/////////
///////// ATTENTION!!!!
///////// Change the conceptinetic.h!!!!
///////// in order to use with the arduino mega:
/////////
///////// //#define USE_DMX_SERIAL_0
///////// //#define USE_DMX_SERIAL_1
///////// //#define USE_DMX_SERIAL_2
///////// #define USE_DMX_SERIAL_3
///////// 
///////// I'm using the Serial3. But with UNO use just Serial0


#include <Conceptinetics.h>

#define DMX_SLAVE_CHANNELS   1

DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );


void setup() {

  
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);

  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);


  dmx_slave.enable ();
  dmx_slave.setStartAddress (511);

}

int dmxMove;

void loop()
{

  if (dmx_slave.getChannelValue(1) > 60) {
    digitalWrite(8, LOW);
  }
  else {
    digitalWrite(8, HIGH);
  }

  
  
}
