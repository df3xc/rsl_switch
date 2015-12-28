
/*--------------------------------------------------------------------
Sammlung von Funktionen um einen Conrad RSL FunkSchalter zu schalten

Getestet mit einem Particle Photon am 21.12.2015

Der Datenpin des 433MHz Senders wird mit dpin verbunden

Author : Dein grosser Bruder in Stuttgart

--------------------------------------------------------------------*/

#include "application.h"
#include "conrad_rsl_switch/conrad_rsl_switch.h"

// Timings for Conrad Electronic Radio Wall Switch
#define ST    430   // short duration 500 usec
#define LO    1150  // long duration 1200 usec


// mit diesem Pin wird der sender gesteuert.
// this pin is used tx_code to control the RF transmitter

int dpin = D1;

/*--------------------------------------------------------------------
Diese Funktion muss einmal von setup() aufgerufen werden
call this function once from setup()
--------------------------------------------------------------------*/

void conrad_rsl_init()
{
  pinMode(dpin,OUTPUT);
  digitalWrite(dpin,LOW);
  delay(500);
}

/*------------------------------------------------------------------------------
CONRAD RSL toggle transmitter control using the given data array
------------------------------------------------------------------------------*/

  void conrad_rsl_transmit (int* code)

  {
	   int rep;
	   int i;

		 digitalWrite(dpin,LOW);
	   delayMicroseconds(5000);

		 digitalWrite(dpin,LOW);
	   delayMicroseconds(5000);

		 digitalWrite(dpin,LOW);
	   delayMicroseconds(5000);

	   // repeat sending the entire control data sequence

	  for (rep=0; rep<8; rep++)
		 {
			 // send the bits from data array

			 for (i=0; i < code[0]; i = i+4)
			 {
			   digitalWrite(dpin,HIGH);
			   delayMicroseconds(code[i+1]);
				 digitalWrite(dpin,LOW);
			   delayMicroseconds(code[i+2]);

			   digitalWrite(dpin,HIGH);
			   delayMicroseconds(code[i+3]);
			   digitalWrite(dpin,LOW);
			   delayMicroseconds(code[i+4]);
			 }

    // for RSL switch
		digitalWrite(dpin,HIGH);
		delayMicroseconds(ST);

		// repeat transmitting after given gap

		digitalWrite(dpin,LOW);
		delayMicroseconds(8000);
  	}
		digitalWrite(dpin,LOW);
  }

  /*--------------------------------------------------------------------
  create code sequence from string and send code sequenz

  SHORT : dauer des kurzen Pulses in milliseconds
  LONG : dauer des langen Pulses in milliseconds

  --------------------------------------------------------------------*/

  void conrad_rsl_send(char* code, int SHORT, int LONG)
  {
  	int i = 0;
  	int k = 1;
    int tx_code[70];  // speicher tx code sequenz

  	tx_code[0]=64;   // die lönge des tx codess

  	for(i=0; i<32; i++)
  	{
  		if (code[i]==0x30) // ascii 0
  		{
  			tx_code[k] = SHORT;
  			tx_code[k+1] = LONG;
  		}
  		else
  		{
  			tx_code[k] = LONG;
  			tx_code[k+1] = SHORT;
  		}
  		k=k+2;
  	}
  	conrad_rsl_transmit(&tx_code[0]);
  }

  /*------------------------------------------------------------------------------

  CONRAD RSL Schalter "which" ein- oder ausschalten

  Die Codessequenzen (z.B. "10011001000001001100000011010111" ) wurden
  mit einem Arduino aufgezeichnet.
  Dazu wird der 433hz Empfänger an den Arduino angeschlossen.

  Youtube: https://www.youtube.com/watch?v=9JBkpcDb5wI

  ------------------------------------------------------------------------------*/

  void conrad_rsl_switch ( int which, int state )
  {
  	char es[34];  // code als Zeichenfolge

    memset(es,0,34);

    if (which==1)
    {
      if (state==EIN)  strncpy(es,"00001110011001001011010000000000",32);
      if (state==AUS)  strncpy(es,"00000001011001001011010000000000",32);
      Serial.print("Sende Code : ");
      Serial.println(es);
      conrad_rsl_send(es,430,1150);
    }

    if (which==2)
    {
      if (state==EIN)  strncpy(es,"00100110011001001011010000000000",32);
      if (state==AUS)  strncpy(es,"00101110011001001011010000000000",32);
      Serial.print("Sende Code : ");
      Serial.println(es);
      conrad_rsl_send(es,430,1150);
    }

    if (which==3)
    {
      if (state==EIN)  strncpy(es,"00010110011001001011010000000000",32);
      if (state==AUS)  strncpy(es,"00011110011001001011010000000000",32);
      Serial.print("Sende Code : ");
      Serial.println(es);
      conrad_rsl_send(es,430,1150);
    }

  }

