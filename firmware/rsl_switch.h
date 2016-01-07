
/*--------------------------------------------------------------------
Sammlung von Funktionen um einen Conrad RSL FunkSchalter zu schalten

Getestet mit einem Particle Photon am 21.12.2015

Der Datenpin des 433MHz Senders wird mit dpin verbunden

Copyright : Carsten Lueck, df3xc@web.de

--------------------------------------------------------------------*/

#ifndef rsl_init_x
#define rsl_init_x

#define DOSE1 1
#define DOSE2 2
#define DOSE3 3

#define EIN 1
#define AUS 0

extern void conrad_rsl_init();
extern void conrad_rsl_switch ( int which, int state );
extern void conrad_rsl_switch_code ( int which, int state );

#endif
