#include <Arduino.h>
#include <PololuLedStrip.h>
#include "defines.h"

class mode{
  public:
    void rainbow(rgb_color *colors);
    void rainbowAnimate(rgb_color* colors);
    void colorFade();
    void rgb(unsigned long value, byte* red, byte* green, byte* blue);
    void flash(rgb_color* colors);
    int checkMode(unsigned long value);
    void strobe();
    void color(byte red, byte gree, byte blue);
  protected:
};

