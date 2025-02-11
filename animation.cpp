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

void fire(NeoPixelSegment& segment) {
  for (int i = 0; i < segment.getLength(); i++) {
    segment.setPixelColor(i, getFireColor());
    segment.setPixelBrightness(i, random(8, 16));
  }
  segment.setBrightness(random(10, 16));
  segment.show();
}