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
    dictated by the individual RGB channels
    */
    RgbColor* colors;
    uint8_t* brightness;
    void (*animationFunction)(NeoPixelSegment& segment);

  public:
    NeoPixelSegment(Adafruit_NeoPixel* pixels, int startIdx, int length) {
      this->pixels = pixels;
      this->startIdx = startIdx;
      this->length = length;
      colors = new RgbColor[length];
      brightness = new uint8_t[length];

      for (size_t i = 0; i < length; i++){
        brightness[i] = 32;
      }
    }

    void fill(String color) {
      for (int i = startIdx; i < startIdx + length; i++) {
        colors[i - startIdx] = getColorByName(color);
        pixels->setPixelColor(i, colors[i-startIdx].getColor());
        setPixelBrightness(i - startIdx, brightness[i - startIdx]);
      }
    }

    void setPixelColor(int index, String color) {
      RgbColor rgbColor = getColorByName(color);
      setPixelColor(index, rgbColor);
    }

    void setPixelColor(int index, RgbColor color) {
      if (index >= 0 && index < length) {
        colors[index] = color;
        pixels->setPixelColor(startIdx + index, colors[index].getColor());
      }
    }

    void clear() {
      fill("Black");
    }

    void setBrightness(uint8_t setBrightness) {
        for (size_t i = 0; i < length; i++) {
            brightness[i] = setBrightness;
            setPixelBrightness(i, brightness[i]);
        }
    }

    void setPixelBrightness(int index, uint8_t setBrightness) {
      if (index >= 0 && index < length) {
        brightness[index] = setBrightness;

        uint8_t r = (uint8_t)((colors[index].red) & 0xFF);
        uint8_t g = (uint8_t)((colors[index].green) & 0xFF);
        uint8_t b = (uint8_t)((colors[index].blue) & 0xFF);

        r = (r * setBrightness) / 255;
        g = (g * setBrightness) / 255;
        b = (b * setBrightness) / 255;

        pixels->setPixelColor(startIdx + index, pixels->Color(r, g, b));
      }
    }

    Adafruit_NeoPixel getPixel(int index) {
        if(index >= 0 && index < length) {
            return pixels[startIdx + index];
        }
    }

    uint8_t getLength() {
        return length;
    }

    void show() {
        pixels->show();
    }

    void setAnimation(void (*inputAnimation)(NeoPixelSegment& segment)) {
       animationFunction = inputAnimation;
    }

    void animate() {
        animationFunction(*this);
    }
};

#endif