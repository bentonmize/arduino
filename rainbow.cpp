#include "rainbow.h"

Color colors[] = {
    {255, 0, 0},        // red
    {255, 128, 0},      // orange
    {255, 255, 0},      // yellow
    {128, 255, 0},      // light green
    {0, 255, 0},        // green
    {255, 128, 0},      // teal
    {0, 255, 255},      // marine
    {0, 0, 255},        // blue
    {127, 0, 255},      // purple
    {255, 0, 255},      // magenta
    {255, 0, 127},      // pink
};

uint32_t getRandomColor(Adafruit_NeoPixel& ring) {
  int colorIndex = random(0, NUM_COLORS - 1);

  Color c = colors[colorIndex];

  uint32_t color = ring.Color(
      c.r,
      c.g,
      c.b
  );

  return color;
}

void rainbow(Adafruit_NeoPixel& ring) {
  ring.setBrightness(64);

  ring.fill(getRandomColor(ring), 0, ring.numPixels());

  ring.show();

  delay(500);
}

void rainbowSpin(Adafruit_NeoPixel& ring) {
  ring.setBrightness(64);

  for(int i=0; i<ring.numPixels(); i++) {
    ring.setPixelColor(i, getRandomColor(ring));
  }

  ring.show();

  delay(50);
}