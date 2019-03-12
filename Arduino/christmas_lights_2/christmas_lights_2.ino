#include "MCP23S17.h"

#ifdef __PIC32MX__
// chipKIT uses the DSPI library instead of the SPI library as it's better
#include <DSPI.h>
DSPI0 SPI;
#else
// Everytying else uses the SPI library
#include <SPI.h>
#endif

const uint8_t chipSelect = 53;
MCP23S17 Bank1(&SPI, chipSelect, 0);
int x = 10;
int iter = 100;


void setup() {
  Serial.begin(9600);
  Bank1.begin();
  for(int i=0; i<16; i++){
    Bank1.pinMode(i, OUTPUT);
  }
Bank1.digitalWrite(7, HIGH);
}

void loop() {
//allLoop();
loopLoop();
/*for(int i=0; i<16; i++){
    Serial.print(i);
    Serial.println(":ON");
    Bank1.digitalWrite(i, HIGH);
  }
delay(500);
for(int i=0; i<16; i++){
    Serial.print(i);
    Serial.println(":OFF");
    Bank1.digitalWrite(i, LOW);
  }
delay(500);
*/
}

void turnOn(int val){
  Serial.print(val);
  Serial.println(":ON");
  Bank1.digitalWrite(val, LOW);
  Bank1.digitalWrite(15-val, HIGH);
}
void turnOff(int val){
  Serial.print(val);
  Serial.println(":OFF");
  Bank1.digitalWrite(val, HIGH);
  Bank1.digitalWrite(15-val, LOW);
}

void allLoop(){
  turnOn(7);
  turnOn(6);
  turnOn(5);
  turnOn(4);
  Serial.println("on");
  delay(500);
  
  turnOff(7);
  turnOff(6);
  turnOff(5);
  turnOff(4);
  Serial.println("off");
  delay(500);
}

void loopLoop(){
  int val = 500;
  for(int i=0;i<16;i++){
    turnOn(i);
    delay(val);
    turnOff(i);
    }
}
