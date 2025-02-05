#ifndef NEOPIXELSEGMENT_H
#define NEOPIXELSEGMENT_H

#include <Adafruit_NeoPixel.h>
#include "colors.h"

class NeoPixelSegment {
  private:
    Adafruit_NeoPixel* pixels;
    int startIdx;
    int length;
    /*
    We need a separate place to stash the color since individual LED color is
    dicated by the individual RGB channels
    */
    RgbColor* colors;

  public:
    NeoPixelSegment(Adafruit_NeoPixel* pixels, int startIdx, int length) {
      this->pixels = pixels;
      this->startIdx = startIdx;
      this->length = length;
      colors = new RgbColor[length];
    }

    void fill(String color) {
      for (int i = startIdx; i < startIdx + length; i++) {
        colors[i - startIdx] = getColorByName(color);
        pixels->setPixelColor(i, colors[i-startIdx].getColor());
      }
      pixels->show();
    }

    void setPixelColor(int index, String color) {
      if (index >= 0 && index < length) {
        // Stash the color here so we can restore brightness
        colors[index] = getColorByName(color);
        pixels->setPixelColor(startIdx + index, colors[index].getColor());
        pixels->show();
      }
    }

    void clear() {
      fill("Black");
    }

    void setBrightness(uint8_t brightness) {
        for (int i = 0; i < length; i++) {
            setPixelBrightness(i, brightness);
        }
    }

    // This can't restore brightness tho :/ 
    void setPixelBrightness(int index, uint8_t brightness) {
      if (index >= 0 && index < length) {
        colors[index];

        uint8_t r = (uint8_t)((colors[index].red) & 0xFF);
        uint8_t g = (uint8_t)((colors[index].green) & 0xFF);
        uint8_t b = (uint8_t)((colors[index].blue) & 0xFF);

        r = (r * brightness) / 255;
        g = (g * brightness) / 255;
        b = (b * brightness) / 255;

        pixels->setPixelColor(startIdx + index, pixels->Color(r, g, b));
        pixels->show();
      }
    }

    Adafruit_NeoPixel getPixel(int index) {
        if(index >= 0 && index < length) {
            return pixels[startIdx + index];
        }
    }
};

#endif