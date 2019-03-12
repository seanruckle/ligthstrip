#include <SPI.h>
#include "MCP23S17.h"

MCP lights(1, 53);

void setup() {
  Serial.begin(9600);
  lights.begin();

  for(int i=1; i<=16; i++){
    lights.pinMode(i, LOW); 
     
    Serial.print("init pin ");
    Serial.println(i);

}

}

void loop() {
  lights.digitalWrite(1,HIGH);
//  for (int i=1; i<=16; i++){
//    lights.digitalWrite(i, 1);
//    Serial.print("set pin ");
//    Serial.println(i);
//  }

}
