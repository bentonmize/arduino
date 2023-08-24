#include "rainbow.h"
#include "ring.h"

Color colors[] = {
    {255, 0, 0},        // red 0
    {255, 128, 0},      // orange 1
    {255, 255, 0},      // yellow 2
    {128, 255, 0},      // light green 3
    {0, 255, 0},        // green 4
    {255, 128, 0},      // teal 5
    {0, 255, 255},      // marine 6
    {0, 0, 255},        // blue 7
    {127, 0, 255},      // purple 8
    {255, 0, 255},      // magenta 9
    {255, 0, 127},      // pink 10
    {255, 255, 255},    // white 11
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

uint32_t getFireColor(Adafruit_NeoPixel& ring) {
  uint8_t r = random(128, 255);
  uint8_t g = random(64, 128);

  if(g > r) {
    g = r;
  }

  return ring.Color(r, g, 0);
}

void fire(Adafruit_NeoPixel&ring) {
  for(int i=0; i<ring.numPixels(); i++) {
    ring.setPixelColor(i, getFireColor(ring));
  }

  ring.setBrightness(random(8, 32));
  ring.show();
  delay(100);
}

void pulseColor(Adafruit_NeoPixel& ring, Pulse& pulse) {
  Color c = colors[4];

  ring.fill(ring.Color(c.r, c.g, c.b), 0, ring.numPixels());

  uint8_t brightness = pulse.run();

  ring.setBrightness(brightness);
  ring.show();

  delay(50);
}

void rainbow(Adafruit_NeoPixel& ring) {
  ring.setBrightness(BRIGHTNESS);

  // ring.fill(getRandomColor(ring), 0, ring.numPixels());
  ring.fill(ring.Color(random(0, 255), random(0, 255), random(0, 255)), 0, ring.numPixels());

  ring.show();

  delay(200);
}

void rainbowSpin(Adafruit_NeoPixel& ring) {
  ring.setBrightness(BRIGHTNESS);

  for(int i=0; i<ring.numPixels(); i++) {
    ring.setPixelColor(i, getRandomColor(ring));
  }

  ring.show();

  delay(50);
}