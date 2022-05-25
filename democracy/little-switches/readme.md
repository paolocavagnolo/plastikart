# 6 pistoni
Il programma little-switches controlla 6 pistoni, su 3 installazioni differenti. Ogni pistone è collegato ad un elettrovalvola, collegata ad un relay comandato da arduino

## prima di cominciare
 - installare arduino IDE da qui: arduino.cc
 - collegare il cavo usb al pc
 - impostare come scheda ARDUINO/GENUINO UNO
 - scegliere la giusta porta USB tra quelle in elenco
 - dal menu "Sketch" andare su #include libreria e poi cliccare su "Gestione Librerie..."
 - verificare di avere installate o installare la seguente libreria:
 	- PS2Keyboard
 - scaricare i file descritti di seguito, caricarli e provarli uno ad uno

## lista dei test preliminare da effettuare
 1- **Setup Keyboard**: scaricalo o copialo da [qui](https://github.com/paolocavagnolo/plastik-art_democracy/blob/master/little-switches/arduino/1_setup-key/1_setup-key.ino). Dopo averlo caricato, aprire il monitor seriale e impostare la velocità (*baudrate* in basso a destra) su 9600. Verificare che la tastiera funzioni correttamente.


 2- **Setup Pot**: scaricalo o copialo da [qui](https://github.com/paolocavagnolo/plastik-art_democracy/blob/master/little-switches/arduino/2_setup-pot/2_setup-pot.ino). Leggere dal monitor seriale il numero della porta che cambia quando si muove il potenziometro

 3- **Setup Relay**: scaricalo o copialo da [qui](https://github.com/paolocavagnolo/plastik-art_democracy/blob/master/little-switches/arduino/3_setup-rel/3_setup-rel.ino). Inserisci nei #define all'inizio del codice il valore trovato precedentemente del potenziometro. Premi i tasti dall'1 allo 0, uno alla volta per capire cosa è collegato a cosa. Noi useremo solo i 4 delle zampe, gli altri li escluderemo dal codice.

 4- **Abbinamento Zampe a frecce**: scaricalo o copialo da [qui](https://github.com/paolocavagnolo/plastik-art_democracy/blob/master/little-switches/arduino/abbinamento/abbinamento.ino). INSERISCI ALL'INIZIO I PARAMETRI CORRETTI APPENA SCOPERTI DENTRO AI DEFINE.

 5- **Galoppo**: scaricalo o copialo da [qui](https://github.com/paolocavagnolo/plastik-art_democracy/blob/master/little-switches/arduino/galoppo/galoppo.ino). Testato





