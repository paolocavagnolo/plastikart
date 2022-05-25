# Test del 19/02/2017

## Possibili problemi
 - compatibilità tra elettrovalvole e relay
 - interferenza su segnale da tastiera
 - codice che si rompe?! (delay..)
 - velocità dei relè
 - qualche loop di terra?
 - valori in float del potenziometro?

## Test da completare
 - Tempi di apertura delle gambe

## Implementazioni
 - Sostituire la tastiera con due pulsanti (pin liberi 9,10,11,12,13)

## Test da effettuare
 - **TEST1**: ciclo semplice - senza tastiera - con delay.
 	- testo i tempi necessari per l'apertura completa delle gambe
 	- testo i relè

 - **TEST2**: ciclo con millis - con tastiera - stampa in seriale il tempo di apertura delle gambe, nel frattempo scrivo in seriale con la tastiera.
 	- testo problematiche con i millis
 	- testo interferenze della tastiera
 
 - **TEST3**: ritesto galappo con i tempi giusti di apertura gambe
 	- testo il codice di prima, ripulito dal float e dal pot.
 	- testo i nuovi tempi di apertura delle gambe
 	- testo la galoppata

 - **TEST4**: testo la galoppata con millis - meglio?
  	- ho aggiunto il tempo di attesa delle gambe a terra

 - **TEST5**: ultimo codice ma con i pulsanti anzichè la tastiera
 	- che sia questo il problema?
