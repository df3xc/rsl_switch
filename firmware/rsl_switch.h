
/*--------------------------------------------------------------------
Sammlung von Funktionen um einen Conrad RSL FunkSchalter zu schalten

Getestet mit einem Particle Photon am 21.12.2015
Author : Dein grosser Bruder in Stuttgart
--------------------------------------------------------------------*/


/*--------------------------------------------------------------------

  Conrad RSL Fernsteuerung 1520000979 in Sued Deutschland

  Schaltgruppe (Schiebeschalter) : I

  Taster 1
      Decimal: 247473664 Binary: 00001110110000000010011000000000
      Decimal: 29369856  Binary: 00000001110000000010011000000000

  Taster 2
      Decimal: 650126848 Binary: 00100110110000000010011000000000
      Decimal: 784344576 Binary: 00101110110000000010011000000000

  Taster 3
      Decimal: 381691392 Binary: 00010110110000000010011000000000
      Decimal: 515909120 Binary: 00011110110000000010011000000000

  Taster ALL-ON / ALL-OFF
      Decimal: 331359744 Binary: 00010011110000000010011000000000
      Decimal: 599795200 Binary: 00100011110000000010011000000000


  Conrad RSL Wandshalter (mit 2 Tastern)

  Wandschalter links
      Decimal: 419741911 Binary: 00011001000001001100000011010111
      Decimal: 352633047 Binary: 00010101000001001100000011010111

  Wandschalter Rechts
      Decimal:  84197591 Binary: 00000101000001001100000011010111
      Decimal: 218415319 Binary: 00001101000001001100000011010111

--------------------------------------------------------------------*/


#ifndef rsl_init_x
#define rsl_init_x

#define DOSE1 1
#define DOSE2 2
#define DOSE3 3

#define EIN 1
#define AUS 0

void conrad_rsl_init();
void conrad_rsl_set_switch( int which, int state );
void conrad_rsl_send(unsigned long code, int SHORT, int LONG);

#endif
