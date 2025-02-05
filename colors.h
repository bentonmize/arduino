#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>

class RgbColor {
  public:
    int red;
    int green;
    int blue;
    String name;

    RgbColor() {
      name = "Black";
      red = 0;
      green = 0;
      blue = 0;
    }

    RgbColor(String n, int r, int g, int b) {
      name = n;
      red = r;
      green = g;
      blue = b;
    }

    uint32_t getColor() {
      return ((uint32_t)red << 16) | ((uint32_t)green << 8) | (uint32_t)blue;
    }
};

RgbColor getColorByName(String colorName);

#endif