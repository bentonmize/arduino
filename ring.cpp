#include "ring.h"

Pulse::Pulse(int brightness, boolean rising, int min, int max, int change) {
    _brightness = brightness;
    _rising = rising;
    _min = min;
    _max = max;
    _change = change;
}

uint8_t Pulse::run() {
    if(this->_rising) {
        this->_brightness += this->_change;
    } else {
        this->_brightness -= this->_change;
    }

    if(this->_brightness > this->_max) {
        this->_rising = false;
        this->_brightness = this->_max;
    } else if(this->_brightness < this->_min) {
        this->_rising = true;
        this->_brightness = this->_min;
    }

    return this->_brightness;
}

void pulsePixel(Adafruit_NeoPixel& ring, int color, int pixel) {
    int index = pixel % ring.numPixels();

    ring.setPixelColor(index, color);
    ring.setBrightness(255);
    ring.show();
    delay(20);
}