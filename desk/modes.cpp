#include "modes.h"
#include <PololuLedStrip.h>


PololuLedStrip<12> ledStrip2;

void mode::colorFade(){
  
  rgb_color colors1[LED_COUNT];
  rgb_color colors2[LED_COUNT];
  rgb_color colors3[LED_COUNT];
  int i = 0;
  int j = 0;
  byte x = 255;

  for(i = 0; i < LED_COUNT; i++){
    colors1[i] = (rgb_color){ 0, 0, 255 };
    colors2[i] = (rgb_color){ 255, 0, 0 };
    colors3[i] = (rgb_color){ 0, 255, 0 };
  }
  ledStrip2.write(colors1, LED_COUNT);
    for(i = 255; i > 0; i--){
      x = x - 1;
      for(j = 0; j < LED_COUNT; j++){
        colors1[j] = (rgb_color){255-x, 0, x};
      }
      ledStrip2.write(colors1, LED_COUNT);
      delay(20);  
    }
    x = 255;
  ledStrip2.write(colors2, LED_COUNT);
  for(i = 255; i > 0; i--){
      x = x - 1;
      for(j = 0; j < LED_COUNT; j++){
        colors2[j] = (rgb_color){x, 255-x, 0};
      }
      ledStrip2.write(colors2, LED_COUNT);
      delay(20);  
    }
    x = 255;
  ledStrip2.write(colors3, LED_COUNT);  
  for(i = 255; i > 0; i--){
      x = x - 1;
      for(j = 0; j < LED_COUNT; j++){
        colors3[j] = (rgb_color){0, x, 255-x};
      }
      ledStrip2.write(colors3, LED_COUNT);
      delay(20);   
    }
    x = 255;
}
void mode::rgb(unsigned long value, byte* red1, byte* green1, byte* blue1){
  byte red = *red1;
  byte green = *green1;
  byte blue = *blue1;
  int i = 0;
  rgb_color colors[LED_COUNT];
  if(value == 0x240C){ //vol up
      if(red < 245){
        red = red + 10;
        }
      }
    else if(value == 0x640c){ //vol down
      if(red > 10){
        red = red - 10;
        }
      }
    else if(value == 0xA10C2807){ //up
      if(green < 245){
        green = green + 10;
        }
      }
    else if(value == 0xA10C6807){ //down
      if(green > 10){
        green = green - 10;
        }
      } 
    else if(value == 0xA10C7807){ //chan up
      if(blue < 245){
        blue = blue + 10;
        }
      } 
    else if(value == 0xA10CF807){ //chan down
      if(blue > 10){
        blue = blue - 10;
        }
      }
    for(i=0; i<LED_COUNT; i++){
        colors[i] = (rgb_color){red, green, blue};
      }
      *red1 = red;
      *green1 = green;
      *blue1 = blue;
    ledStrip2.write(colors, LED_COUNT);
}

void mode::rainbow(rgb_color *colors){
  int i;
  byte adder1 = 0;
  byte adder2 = 0;

  int x1,x2,x3,x4,x5,x6;
  int numLeft = LED_COUNT;

  //rgb_color colors[LED_COUNT];
  rgb_color colors2[LED_COUNT];

  rgb_color blank[300];
  
  x1 = 0;
  x2 = x1 + (numLeft / 5);
  numLeft = LED_COUNT - x2;
  x3 = x2 + (numLeft / 4);
  numLeft = LED_COUNT - x3;
  x4 = x3 + (numLeft/3);
  numLeft = LED_COUNT -x4;
  x5 = x4 + (numLeft/2);
  x6 = LED_COUNT-1;

  ledStrip2.write(blank, 300);
    
  colors[x1] = (rgb_color){255, 0, 0};
  adder1 = 0;
  for(i = 0; i < (x2-x1-1); i++){
    adder1 = adder1 + (127/(x2-x1));
    colors[i+1] = (rgb_color){255, adder1, 0}; 
    }
    
  colors[x2] = (rgb_color){255, 127, 0};
  for(i = 0; i < (x3-x2-1); i++){
    adder1 = adder1 + (128/(x3-x2));
    colors[i+x2+1] = (rgb_color){255, adder1, 0}; 
    }
  
  colors[x3] = (rgb_color){255, 255, 0};
  adder1 = 255;
  for(i = 0; i < (x4-x3-1); i++){
    adder1 = adder1 - (255/(x4-x3));
    colors[i+x3+1] = (rgb_color){adder1, 255, 0}; 
    }
    
  colors[x4] = (rgb_color){0, 255, 0};
  adder1 = 255;
  adder2 = 0;
  for(i = 0; i < (x5-x4-1); i++){
    adder1 = adder1 - (255/(x5-x4));
    adder2 = adder2 + (255/(x5-x4));
    colors[i+x4+1] = (rgb_color){0, adder1, adder2}; 
    }
    
  colors[x5] = (rgb_color){0, 0, 255};
  adder1 = 0;
  adder2 = 255;
  for(i = 0; i < (x6-x5-1); i++){
    adder1 = adder1 + (148/(x6-x5));
    adder2 = adder2 - (135/(x6-x5));
    colors[i+x5+1] = (rgb_color){adder1, 0, adder2}; 
    }
    
  colors[x6] = (rgb_color){148, 0, 120};

  ledStrip2.write(colors, LED_COUNT);
  }

void mode::rainbowAnimate(rgb_color *colors){
    int i;
    rgb_color colors2[LED_COUNT];
    rgb_color blank[LED_COUNT];
    colors2[0] = colors[LED_COUNT-1];
    for(i=0; i<LED_COUNT-1; i++){
      colors2[i+1] = colors[i];
      }
    ledStrip2.write(colors2, LED_COUNT);
    for(i=0;i<LED_COUNT;i++){
      colors[i] = colors2[i];
      }
    delay(DELAY);    
  }


int mode::checkMode(unsigned long value){
  if(value == 0xA10C140B){
      return 1;
    }
  if(value == 0xA10C940B){
      return 2;
    }
}

void mode::flash(rgb_color* colors){
    int i = 0;
    rgb_color colors2[LED_COUNT];
    
    for(i=0;i<LED_COUNT;i++){
      colors2[i] = (rgb_color){255,255,255};
    }
    ledStrip2.write(colors2, LED_COUNT);
    delay(DELAY);
    ledStrip2.write(colors, LED_COUNT);
    delay(DELAY);
}

void mode::strobe(){
    int i = 0;
    rgb_color colors2[LED_COUNT];
    rgb_color blank[LED_COUNT];
    
    for(i=0;i<LED_COUNT;i++){
      colors2[i] = (rgb_color){255,255,255};
      blank[i] = (rgb_color){0,0,0};
    }
    ledStrip2.write(colors2, LED_COUNT);
    delay(DELAY);
    ledStrip2.write(blank, LED_COUNT);
    delay(DELAY);  
}
void mode::color(byte red, byte green, byte blue){
  rgb_color colors[LED_COUNT];
  int i;
  
  for(i=0; i<LED_COUNT; i++){
    colors[i] = (rgb_color){red, green, blue};
  }

   ledStrip2.write(colors, LED_COUNT);
}
 
