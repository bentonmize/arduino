#ifndef RAINBOW_H
#define RAINBOW_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

class Color {
    public:
        uint32_t r;
        uint32_t g;
        uint32_t b;
};

#define NUM_COLORS 11

void rainbow(Adafruit_NeoPixel& pixels);
void rainbowSpin(Adafruit_NeoPixel& pixels);

#endif