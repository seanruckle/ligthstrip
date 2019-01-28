#include <PololuLedStrip.h>
#define LED_COUNT 300
#define LED_MAX 300

int y;
int x;
int z;
int i;
byte adder1 = 0;
byte adder2 = 0;

rgb_color colors[LED_COUNT];
rgb_color blank[LED_MAX];
PololuLedStrip<12> ledStrip;
PololuLedStrip<12> clearSrip;

void setup() {
  x = LED_COUNT/5;
  y = LED_COUNT-1;
  z = LED_COUNT - 4*x;

  ledStrip.write(blank, LED_MAX);
    
  colors[0] = (rgb_color){255, 0, 0};
  adder1 = 0;
  for(i = 0; i < (x-1); i++){
    adder1 = adder1 + (127/x);
    colors[i+1] = (rgb_color){255, adder1, 0}; 
    }
    
  colors[x] = (rgb_color){255, 127, 0};
  for(i = 0; i < (x-1); i++){
    adder1 = adder1 + (128/x);
    colors[i+x+1] = (rgb_color){255, adder1, 0}; 
    }
  
  colors[2*x] = (rgb_color){255, 255, 0};
  adder1 = 255;
  for(i = 0; i < (x-1); i++){
    adder1 = adder1 - (255/x);
    colors[i+2*x+1] = (rgb_color){adder1, 255, 0}; 
    }
    
  colors[3*x] = (rgb_color){0, 255, 0};
  adder1 = 255;
  adder2 = 0;
  for(i = 0; i < (x-1); i++){
    adder1 = adder1 - (255/x);
    adder2 = adder2 + (255/x);
    colors[i+3*x+1] = (rgb_color){0, adder1, adder2}; 
    }
    
  colors[4*x] = (rgb_color){0, 0, 255};
  adder1 = 0;
  adder2 = 255;
  for(i = 0; i < (z-1); i++){
    adder1 = adder1 + (148/z);
    adder2 = adder2 - (135/z);
    colors[i+4*x+1] = (rgb_color){adder1, 0, adder2}; 
    }
    
  colors[y] = (rgb_color){148, 0, 120};

  ledStrip.write(colors, LED_COUNT);

}

void loop() {
  // put your main code here, to run repeatedly:

}
