# The big tobacco machine

## scatola di controllo
 - **INPUT**:
 	- un pulsante lontano almeno 20 metri (dmx 3 poli + scatolina con switch)
 
 - **OUTPUT**:
 	- segnale RS485 per controllo di due arduino sullo stesso BUS
 	- audio bilanciato L + R

 - **PROCESS**:
 	- ARDUINO legge pulsante
 	- ARDUINO manda a RS485 comandi in seriale
 	- ARDUINO manda a WAVE TRIGGER segnale di sincro audio
 	- RS485 manda a bus comandi in seriale
 	- WAVE TRIGGER manda a DI STEREO audio

 - **COMPONENTI**:
 	- 1 x ARDUINO
 	- 1 x RS485
 	- 1 x WAVE TRIGGER
 	- 1 x DI STEREO
 	- 1 x ALIMENTATORE
 	- 1 x CONNETTORE DMX 3 POLI PER RS485
 	- 1 X CONNETTORE DMX 3 POLI PER PULSANTE CONTROLLO

## 2 x scatole per pwm controllo motori (10 motori l'una)
 - **INPUT**:
 	- segnale RS485 su bus seriale
 
 - **OUTPUT**:
 	- 10 x segnali PWM controllo motori

 - **PROCESS**:
 	- RS485 legge segnale e manda ad ARDUINO 
 	- ARDUINO legge segnale e manda a PWM segnale seriale
 	- PWM legge da arduino e manda a 10 DMX 5 poli

 -**COMPONENTI**:
 	- 1 x RS485 
 	- 1 X ARDUINO
 	- 1 x PWM
 	- 1 x ALIMENTATORE
 	- 10 x CONNETTORI DMX 5 POLI PER DRIVER MOTORI
 	- 1 x CONNETTORE DMX 3 POLI PER BUS RS485


