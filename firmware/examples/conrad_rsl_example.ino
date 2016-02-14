/*--------------------------------------------------------------------
Mit der BLYNK APP Conrad RSL FunkSchalter schalten

Getestet mit einem Particle Photon am 21.12.2015
Author : Dein grosser Bruder in Stuttgart

Diese Datei ist das Hauptprogram mit den Funktionen
setup() und loop(). Diese darf es nur einmal geben.

Die virtuellen Pins V1..V6 schalten die Dosen ein bzw. aus
Verbinde sie mit den BLYNK APP buttons auf dem Smartphone

Die virtuellen Pins V11, V12 und V13 zeigen an, ob eine Dose ein
bzw. ausgeschaltet wurde. Verbinde sie mit Leuchtdioden der
BLYNK APP auf dem Smartphone

Die Ausgaben mit Serial.println() sieht man wenn der Particle
mit USB an den Computer angeschlossen ist. Particle stellt einen
seriellen Port zu verfügung.

Hinweis zur IDE Particle Dev: Alle Dateien müssen in dem gleichen
Verzeichnis liegen. Unterverzeichnisse werden nicht unterstützt.


Programm erstellen

Ein neues PRogrammverzeichnis erstellen

Die BLYNK library herunterladen:

https://github.com/vshymanskyy/blynk-library-spark.git

Die Dateien in FIRMWARE in Dein Programmverzeinhnis kopieren

Ein neue Datei mit den Funkktionen setup() und loop() erstellen.

--------------------------------------------------------------------*/

#define BLYNK_PRINT Serial
#include <time.h>
#include "blynk/BlynkSimpleParticle.h"
#include "rsl_switch/rsl_switch.h"



// Ersetze "..." mit dem Token aus der Email
char auth[] = "the token from BLYNK APP on your smartphone ";

char timebuffer[80]; // speicher für dem Zeitstempel (timeStamp)

// Ein BLYNK APP Terminal an virtuel pin V22
WidgetTerminal terminal(V22);

// gebe Datum und Uhrzeit am seriellen Port aus
// serial print the timestamp

void timeStamp()
{
  sprintf(timebuffer," %.2d-%.2d-%d %.2d:%.2d:%.2d ",
  Time.day(),
  Time.month(),
  Time.year(),
  Time.hour(),
  Time.minute(),
  Time.second());
  Serial.print(timebuffer);
}

// gebe Zeitstempel und text an serieller SChnittstelle aus (uber USB)

void println( char* text)

{
  timeStamp();
  Serial.println(text);

  // Ausgabe an BLYNK APP terminal
  terminal.println(text);
  terminal.flush();
}


void setup()
{
    Serial.begin(9600);
    delay(5000);        // Allow board to settle

    conrad_rsl_init();  // 433 MHz Sender abschalten
    Blynk.begin(auth);  // bei BLNYC Server anmelden
    Time.zone(+1);      // Zeitzone Berlin = GMT + 1Stunde (für Sommerzeit GMT + 2Stunden)

    println(" DosenFunk startet ... ");
}

  /*------------------------------------------------------------------------------

  CONRAD RSL Schalter "which" ein- oder ausschalten

  which : Die Nummer der Dose, die Du festlegts
  state : 0 = dose ausschalten. 1 = dose einschalten

  Die Codessequenzen (z.B. "10011001000001001100000011010111" ) wurden
  zuvor aufgezeichnet.
  Dazu wird der 433hz Empfänger angeschlossen.

  ------------------------------------------------------------------------------*/

  void conrad_rsl_switch ( int which, int state )
  {
    char es[34];  // code als Zeichenfolge

    memset(es,0,34);

    switch (which) {
     case 1: // schalter in nord deutschland
       if (state==EIN)  strncpy(es,"00001110011001001011010000000000",32);
       if (state==AUS)  strncpy(es,"00000001011001001011010000000000",32);
       break;
       
     case 2: // schalter in nord deutschland
       if (state==EIN)  strncpy(es,"00100110011001001011010000000000",32);
       if (state==AUS)  strncpy(es,"00101110011001001011010000000000",32);
       break;

     case 3: // schalter in nord deutschland
       if (state==EIN)  strncpy(es,"00010110011001001011010000000000",32);
       if (state==AUS)  strncpy(es,"00011110011001001011010000000000",32);
       break;

     case 4: // schalter in sued deutschland
       if (state==EIN)  strncpy(es,"00011001000001001100000011010111",32);
       if (state==AUS)  strncpy(es,"00010101000001001100000011010111",32);
       break;

     case 5: // schalter in sued deutschland
       if (state==EIN)  strncpy(es,"00000101000001001100000011010111",32);
       if (state==AUS)  strncpy(es,"00001101000001001100000011010111",32);
       break;
       
     default: 
      Serial.print(" Fehler : konnte Code nicht finden ");
     break;
   }

   Serial.print("Sende Code : ");
   Serial.println(es);
   conrad_rsl_send(es,430,1150);
  }


 /*------------------------------------------------------------------------------

  CONRAD RSL Schalter "which" ein- oder ausschalten

  which : Die Nummer der Dose, die Du festlegts
  state : 0 = dose ausschalten. 1 = dose einschalten

  Die Codes als Dezimalzahl (z.B. 241480704 ) wurden
  zuvor aufgezeichnet.
  Dazu wird der 433hz Empfänger angeschlossen.


  which = 4,  on   : Decimal: 419741911 (32Bit) Binary: 00011001000001001100000011010111
  which = 4, off   : Decimal: 352633047 (32Bit) Binary: 00010101000001001100000011010111
 
  which = 5,  on   : Decimal:  84197591 (32Bit) Binary: 00000101000001001100000011010111
  which = 5,  off  : Decimal: 218415319 (32Bit) Binary: 00001101000001001100000011010111

  ------------------------------------------------------------------------------*/

  

  void conrad_rsl_switch_code ( int which, int state )
  {

    unsigned long code = 0;

    switch (which) {

    case 1: // schalter in nord deutschland
       if (state==EIN) code = 241480704; 
       if (state==AUS) code = 23376896; 
       break;

    case 2: // schalter in nord deutschland
       if (state==EIN) code = 322066944;
       if (state==AUS) code = 778351616; 
       break;

    case 3: // schalter in nord deutschland
       if (state==EIN) code = 375698432; 
       if (state==AUS) code = 509916160; 
       break;

     case 4: // schalter in sued deutschland
       if (state==EIN) code = 419741911; 
       if (state==AUS) code = 352633047; 
       break;

     case 5: // schalter in sued deutschland
       if (state==EIN) code = 84197591;
       if (state==AUS) code = 218415319; 
       break;       

     default: 
       Serial.print(" Fehler : konnte Code nicht finden ");
       break; 
    }
    
    if (code != 0)
    {
      Serial.print("Sende Code : ");
      Serial.println(code);
      conrad_rsl_send(code,430,1150);
    } 
    else
    {
      Serial.print(" Fehler : konnte Code nicht finden ");      
    }
    
  }

// Verbinde auf der BLYNC APP den Button mit Virtual pin 1
BLYNK_WRITE(V1)
{
    if (param.asInt() == 1) // Schalter nieder gedrückt ?
    {
      println(" rsl dose 1 ein ");
      conrad_rsl_switch(DOSE1,1);
      Blynk.virtualWrite(V11,255);  // V11 ist eine BLYNC APP LED
      Blynk.virtualWrite(V23,23);

    }
}

// Verbinde auf der BLYNC APP den Button mit Virtual pin 2
BLYNK_WRITE(V2)
{
    if (param.asInt() == 1) // Schalter nieder gedrückt ?
    {
      println(" rsl dose 1 aus ");
      conrad_rsl_switch(DOSE1,0);
      Blynk.virtualWrite(V11,0); // V11 ist eine BLYNC APP LED4

      Blynk.virtualWrite(V23,45);

    }
}

BLYNK_WRITE(V3)
{
    if (param.asInt() == 1) // Schalter nieder gedrückt ?
    {
      println(" rsl dose 2 ein ");
      conrad_rsl_switch(DOSE2,1);
      Blynk.virtualWrite(V12,255); // V12 ist eine BLYNC APP LED
    }
}

BLYNK_WRITE(V4)
{
    if (param.asInt() == 1) // Schalter nieder gedrückt ?
    {
      println(" rsl dose 2 aus ");
      conrad_rsl_switch(DOSE2,0);
      Blynk.virtualWrite(V12,0); // V12 ist eine BLYNC APP LED
    }
}


BLYNK_WRITE(V5)
{
    if (param.asInt() == 1) // Schalter nieder gedrückt ?
    {
      println(" rsl dose 3 ein ");
      conrad_rsl_switch(DOSE3,1);
      Blynk.virtualWrite(V13,255); // V13 ist eine BLYNC APP LED
    }
}

BLYNK_WRITE(V6)
{
    if (param.asInt() == 1) // Schalter nieder gedrückt ?
    {
      println(" rsl dose 3 aus ");
      conrad_rsl_switch(DOSE3,0);
      Blynk.virtualWrite(V13,"0"); // V13 ist eine BLYNC APP LED
    }
}

// Diese loop wird für immer ausgeführt

void loop()
{
    Blynk.run();
}
