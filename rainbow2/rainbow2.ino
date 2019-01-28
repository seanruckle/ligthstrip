#include <PololuLedStrip.h>
#define LED_COUNT 300
#define LED_MAX 300
#define ON 1
#define OFF 2
#define WAVE ON
#define DELAY 5

int y;
int x;
int z;
int i;
byte adder1 = 0;
byte adder2 = 0;

int x1,x2,x3,x4,x5,x6;
int numLeft = LED_COUNT;

rgb_color colors[LED_COUNT];
rgb_color colors2[LED_COUNT];

rgb_color blank[LED_MAX];
PololuLedStrip<12> ledStrip;

void setup() {
  x1 = 0;
  x2 = x1 + (numLeft / 5);
  numLeft = LED_COUNT - x2;
  x3 = x2 + (numLeft / 4);
  numLeft = LED_COUNT - x3;
  x4 = x3 + (numLeft/3);
  numLeft = LED_COUNT -x4;
  x5 = x4 + (numLeft/2);
  x6 = LED_COUNT-1;

  ledStrip.write(blank, LED_MAX);
    
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

  ledStrip.write(colors, LED_COUNT);

}

void loop() {
  if(WAVE == ON){
    colors2[0] = colors[LED_COUNT-1];
    for(i=0; i<LED_COUNT-1; i++){
      colors2[i+1] = colors[i];
      }
    ledStrip.write(colors2, LED_COUNT);
    delay(DELAY);
    colors[0] = colors2[LED_COUNT-1];
    for(i=0; i<LED_COUNT-1; i++){
      colors[i+1] = colors2[i];
      }
    ledStrip.write(colors, LED_COUNT);
    delay(DELAY);   
    }

}
