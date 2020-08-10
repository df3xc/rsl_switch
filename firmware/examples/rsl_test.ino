


#include "rsl.h"

char ch;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(" HELLO ");
  Serial.println(sizeof(int));
  Serial.println(sizeof(long));
  Serial.println(" ----- ");
  conrad_rsl_init();
  help();
}

void help()
{
  Serial.println(" 7 : RSL1 ON  8 : RSL1 OFF");
  Serial.println(" 4 : RSL2 ON  5 : RSL2 OFF");
  Serial.println(" 1 : RSL3 ON  2 : RSL3 OFF");  
}

void loop() {

  if (Serial.available() > 0) 
    {
      ch = (char)Serial.read();

      if(ch=='h'){
        help();
      }

      if(ch=='7') {
        Serial.println(" RSL1 ON ");
        conrad_rsl_set_switch ( 3, 1 );
      }
       if(ch=='8') {
        Serial.println(" RSL1 OFF ");
        conrad_rsl_set_switch ( 3, 0 );
      }  

      if(ch=='4') {
        Serial.println(" RSL2 ON ");
        conrad_rsl_set_switch ( 4, 1 );
      }
       if(ch=='5') {
        Serial.println(" RSL2 OFF ");
        conrad_rsl_set_switch ( 4, 0 );
      }  

      if(ch=='1') {
        Serial.println(" RSL3 ON ");
        conrad_rsl_set_switch ( 5, 1 );
      }
       if(ch=='2') {
        Serial.println(" RSL3 OFF ");
        conrad_rsl_set_switch ( 5, 0 );
      } 
          
    }

}
