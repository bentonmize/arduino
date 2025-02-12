#ifndef ANIMATION_H
#define ANIMATION_H

#include "NeoPixelSegment.h"

struct FireState {
  int rate = 5;
};

struct PulseState {
  int rate = 5;
  bool increasing = true;
  int increment = 3;
  int brightness = 4;
  int max = 16;
  int min = 4;
};

void fire(NeoPixelSegment& segment, unsigned long ticks, FireState& state);
void pulse(NeoPixelSegment& segment, unsigned long ticks, PulseState& state);

#endif