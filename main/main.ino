#include <PololuLedStrip.h>
#include "modes.h"
#include "IRLib.h"
#include "defines.h"



//Create a receiver object to listen on pin 11
IRrecv My_Receiver(11);

//Create a decoder object
IRdecode My_Decoder;
PololuLedStrip<12> ledStrip;
mode light;


int mode = MODE;


unsigned long value = 0;
unsigned long prev = 0xFFFFAFFF;
byte red = 0;
byte green = 0;
byte blue = 255;
int i = 0;
int first = 0;

#define LED_COUNT 30
rgb_color colors[LED_COUNT];
rgb_color blank[LED_MAX];


void setup()
{
  Serial.begin(9600);
  My_Receiver.enableIRIn(); // Start the receiver
}

void loop() {
  switch (mode){
    case 1: 
      if (My_Receiver.GetResults(&My_Decoder)) {
        My_Decoder.decode();    //Decode the data
        
        value = My_Decoder.getValue(0);
        if(value == 0xFFFFFFFF){
          value = prev;
          }
        else{
          prev = value;
          }
          Serial.println(value, HEX);
          
          light.rgb(value, &red, &green, &blue);
          
          My_Receiver.resume();     //Restart the receiver
      }
      break;
  
    case 2:
      light.colorFade();
      break;
      
    case 3:
      if (first == 0){
        light.rainbow(colors);
        first = 1;
      }
      else{
        light.rainbowAnimate(colors);
      }
      break;
    case 4:
        light.strobe();
      break;
    default:
      ledStrip.write(blank, LED_MAX);
      break;
  }
}

