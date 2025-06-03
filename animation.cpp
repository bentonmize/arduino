#include "animation.h"
#include "colors.h"

RgbColor getFireColor() {
  uint8_t r = random(180, 255);
  uint8_t g = random(64, 128);

  if (g > r) {
    g = r;
  }

  return RgbColor("", r, g, 0);
}

void fire(NeoPixelSegment& segment, unsigned long ticks, FireState& state) {
  if(ticks % state.rate == 0) {
      for (int i = 0; i < segment.getLength(); i++) {
        segment.setPixelColor(i, getFireColor());
        segment.setPixelBrightness(i, random(4, 10));
      }
      // segment.setBrightness(random(4, 10));
      segment.show();
  }
}

void pulse(NeoPixelSegment& segment, unsigned long ticks, PulseState& state) {

  if(ticks % state.rate == 0) {
    if(state.increasing) {
      state.brightness += state.increment;
    } else {
      state.brightness -= state.increment;
    }

    if(state.brightness <= state.min) {
      state.brightness = state.min;
      state.increasing = true;
    } else if (state.brightness >= state.max) {
      state.brightness = state.max;
      state.increasing = false;
    }

    segment.setBrightness(state.brightness);
    segment.show();
  }
}

void progress(NeoPixelSegment& segment, unsigned long ticks, ProgressState& state) {
  if(ticks % state.rate == 0) {
    segment.setBrightness(4);
    if(segment.getLength() == 12) {
      int start_bright = segment.getLength() / 2;
      for(int i = 0; i < 12; i++) {
        if(i < segment.getLength()/2) {
          segment.setPixelBrightness(state.rotationPins[i], min(start_bright + (i), segment.getLength()/2));
        } else {
          segment.setPixelBrightness(state.rotationPins[i], max(start_bright - (i), 1));
        }
      }

      for(int i = 0; i < segment.getLength(); i++) {
        state.rotationPins[i] = state.rotationPins[i] + 1;
        if(state.rotationPins[i] >= segment.getLength()) {
          state.rotationPins[i] = 0;
        }
      }
    }
    segment.show();
  }
}