#ifndef ANIMATION_H
#define ANIMATION_H

#include "neopixelsegment.h"

struct FireState {
  int rate = 5;
};

struct PulseState {
  int rate = 8;
  bool increasing = true;
  int increment = 3;
  int brightness = 4;
  int max = 24;
  int min = 8;
};

struct ProgressState {
  int rate = 3;
  uint8_t rotationPins[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
};
struct Animation {
  void (*func);
  void* state;
};

void fire(NeoPixelSegment& segment, unsigned long ticks, FireState& state);
void pulse(NeoPixelSegment& segment, unsigned long ticks, PulseState& state);
void progress(NeoPixelSegment& segment, unsigned long ticks, ProgressState& state);

#endif