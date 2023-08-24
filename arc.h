#ifndef ARC_H
#define ARC_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define ARC_BRIGHT_INT 5
#define ARC_MAX_BRIGHT 32   // Max I think is 128 (its really stinkin' bright)
#define ARC_MIN_BRIGHT_INT ARC_MAX_BRIGHT / 16
#define ARC_INIT_LOOPS 20

void arcReactor(Adafruit_NeoPixel& pixels);
void arcReset();

#endif