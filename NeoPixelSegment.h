#ifndef NEOPIXELSEGMENT_H
#define NEOPIXELSEGMENT_H

#include <Adafruit_NeoPixel.h>

class NeoPixelSegment {
  private:
    Adafruit_NeoPixel* pixels;
    int startIdx;
    int length;
    /*
    We need a separate place to stash the color since individual LED color is
    dicated by the individual RGB channels
    */
    uint32_t* colors;

  public:
    NeoPixelSegment(Adafruit_NeoPixel* pixels, int startIdx, int length) {
      this->pixels = pixels;
      this->startIdx = startIdx;
      this->length = length;
      colors = new uint32_t[length];

      // Initialize all colors to zero
      for (int i = 0; i < length; i++) {
        colors[i] = 0;
      }
    }

    void fill(uint32_t color) {
      for (int i = startIdx; i < startIdx + length; i++) {
        colors[i - startIdx] = color;
        pixels->setPixelColor(i, color);
      }
      pixels->show();
    }

    void setPixelColor(int index, uint32_t color) {
      if (index >= 0 && index < length) {
        // Stash the color here so we can restore brightness
        colors[index] = color;
        pixels->setPixelColor(startIdx + index, color);
        pixels->show();
      }
    }

    void clear() {
      fill(pixels->Color(0, 0, 0));
    }

    void setBrightness(uint8_t brightness) {
        for (int i = startIdx; i < startIdx + length; i++) {
            setPixelBrightness(i, brightness);
        }
        pixels->show();
    }

    // This can't restore brightness tho :/ 
    void setPixelBrightness(int index, uint8_t brightness) {
      if (index >= 0 && index < length) {
        uint32_t color = colors[index];

        uint8_t r = (uint8_t)((color >> 16) & 0xFF);
        uint8_t g = (uint8_t)((color >> 8) & 0xFF);
        uint8_t b = (uint8_t)(color & 0xFF);

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