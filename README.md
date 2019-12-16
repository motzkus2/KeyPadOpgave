# Keypad Opgave

I denne opgave har jeg kodet en 4x4 keypad til at kunne registrere når man trykker på en knap og udfører en handling ud fra hvilken knap man har trykket på


## Fysisk opsætning

Keypad'en er blevet forbundet til en Atmega Dragon microcontroller på C registeret. 

## Koden

Koden er skrevet i sproget C i programmet Atmel Studio. 
Jeg har aktiveret pull up på PC4-7 kodet dem til at være input pins, samt kodet PC0-3 til at være output porte. 
Derudover har jeg sat alle output porte til at være logisk 1. 

Her er et billede af init: https://imgur.com/a/k9IGj46

## Funktioner 
### ColumnScan()

I funktionen ColumnScan() bliver portene en efter en skiftet til logisk 0 hver gang funktionen bliver kaldt. Der bliver returneret en int der svarer til hvilken kolonne man er nået til, og så bliver en statisk int rettet til, så vi ved hvilken kolonne vi er nået til næste gang funktionen bliver kaldt.

### ReadRows()

I funktionen ReadRows() bliver der kørt en If-statement der tjekker om en PIN er skiftet til logisk 0, som sker ved at der kommer en kortslutning i det man trykker en knap ned, og der kommer forbindelse til en Outport Port. Efter der er blevet tjekket er der indsat et delay på 10ms inden den samme If-statement bliver kørt igen. Dette er blevet implementeret for at undgå "kontakt krel" der kan forekomme når når man trykker på en knap. Hvis If-statement er true, bliver der returneret en int der svarer til den række PIN er forbundet til.

### DecodeKeypad(int, int)
Denne funktion bruges til at udregne hvilken knap der er blevet trykket på. Når funktionen bliver kaldt, sendes 2 ints med; en int man får fra ColumnScan() og en int man får fra ReadRows(). Disse to ints lægges sammen ved brug af formlen **a * 10 + b**. eks. er tallene 3 og 6 blevet sendt med, giver det tallet 36. Fordi vi har kolonnerne 1, 2, 3, 4 og rækkerne 5, 6, 7, 8, kan vi lave 16 mulige kombinationer, som svarer til de 16 knapper der findes på vores Keypad. Derfor er der lavet en switch case med alle 16 kombinationer, som hver især svarer til en bestemt knap. 

## Flowchart
Her er et link til et flowchart der viser hvordan programmet fungerer: https://imgur.com/a/X9J3wOT

## Diverse
Billede af opsætning: https://imgur.com/a/UqAqLp8
Billede af LogiskDiagram der viser hvordan ColumnScan() slukker Portene én efter én: https://imgur.com/a/pegBTof

