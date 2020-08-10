


#include "rsl.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(" HELLO ");
  Serial.println(sizeof(int));
  Serial.println(sizeof(long));
  Serial.println(" ----- ");
  conrad_rsl_init();
}

void loop() {

  Serial.println("ON");
  conrad_rsl_set_switch ( 3, 1 );
  //conrad_rsl_send(2394957312,430,1150);
  
  delay(5000);
  Serial.println("OFF");  
  conrad_rsl_set_switch ( 3, 0 );  
  //conrad_rsl_send(2176853504 ,430,1150);  
  delay(5000); 

//  conrad_rsl_set_switch ( 4, 1 );
//  delay(5000);
//  conrad_rsl_set_switch ( 4, 0 );  
//  delay(5000); 
//
//  conrad_rsl_set_switch ( 5, 1 );
//  delay(5000);
//  conrad_rsl_set_switch( 5, 0 );  
//  delay(5000); 

}
