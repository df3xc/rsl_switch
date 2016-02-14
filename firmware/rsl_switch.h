
/*--------------------------------------------------------------------
Sammlung von Funktionen um einen Conrad RSL FunkSchalter zu schalten

Getestet mit einem Particle Photon am 21.12.2015

Der Datenpin des 433MHz Senders wird mit dpin verbunden

Copyright : Carsten Lueck, df3xc@web.de

--------------------------------------------------------------------*/

#ifndef rsl_init_x
#define rsl_init_x

// Funk Dosen 1..3 sind Deine Dosen in Nord Deutchland

#define DOSE1 1
#define DOSE2 2
#define DOSE3 3

// Funk Dosen 4..5 sind meine Dosen in Sued Deutchland

#define DOSE4 4
#define DOSE5 5

#define EIN 1
#define AUS 0

extern void conrad_rsl_init();
extern void conrad_rsl_send(unsigned long code, int SHORT, int LONG);
extern void conrad_rsl_send(char* code, int SHORT, int LONG);

#endif
