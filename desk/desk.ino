#include <PololuLedStrip.h>
#define LED_COUNT 300
#define LED_MAX 300
#include "modes.h"


//rgb_color colors[LED_COUNT];
rgb_color blank[LED_MAX];
PololuLedStrip<12> ledStrip;
//PololuLedStrip<12> clearSrip;

byte red = 0;
byte green = 0;
byte blue = 255;

String  inS;
char term = '#';
bool recString = false;
String inData;
bool animate = false;
int h = 0;
int iter = 2;

mode light;

void setup() {
  ledStrip.write(blank, LED_MAX);
   Serial.begin(115200);
}

void loop() {
  //light.strobe();
  while (Serial.available() > 0) {
    delay(1);
    char c = Serial.read();
    
    if(c == term){
      Serial.println("Got Data");
      recString = true;
      inData = "";
      for(int i=0; i<inS.length(); i++){
        inData += inS[i];
      }
      inS = ""; //clear the string after we use it
      break;
    }
    inS += c;
    
  }
  if (recString == true){
    animate = false;
    recString = false;
    if(inData[0] == 'r'){
      Serial.println("red");
      light.color(255,000,000);
    }
    else if(inData[0] == 'g'){
      Serial.println("green");
      light.color(0,255,0);
    }
    else if(inData[0] == 'b'){
      Serial.println("blue");
      light.color(0,0,255);
    }
    else if(inData[0] == 'c'){
      Serial.println("custom");
      byte red = 0;
      byte green = 0;
      byte blue = 0;
      int index1 = inData.indexOf(',');
      int index2 = inData.indexOf(',', index1+1);
      String r = inData.substring(1,index1);
      String g = inData.substring(index1+1,index2);
      String b = inData.substring(index2+1);

      red = r.toInt();
      green = g.toInt();
      blue = b.toInt();
      
      light.color(red,green,blue);
    }
     else if(inData[0] == 'a'){
      Serial.println("animate");
      animate = true;
    }
     else if(inData[0] == 'o'){
      Serial.println("off");
      animate = false;
      light.color(0, 0, 0);
    }
  }
  else if (animate == true){ 
      light.color(0, 0, h);
      h += iter;
      if(h>255){
        h = 255; 
        iter = iter*-1;
      }
      if(h<0){
        h = 0; 
        iter = iter*-1;
      }
      //updateString = false;
    }
}



