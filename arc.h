#ifndef ARC_H
#define ARC_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define ARC_BRIGHT_INT 1
#define ARC_MAX_BRIGHT 16   // Pretty sure max is 128
#define ARC_MIN_BRIGHT_INT ARC_MAX_BRIGHT / 16
#define ARC_INIT_LOOPS 20

#define ARC_PULSE_BRIGHT_INT 2
#define ARC_PULSE_MAX_BRIGHT 32
#define ARC_PULSE_MIN_BRIGHT 10
#define MAX_DELAY_COUNT 3

void arcReactor(Adafruit_NeoPixel& pixels);
void arcReset();

#endif