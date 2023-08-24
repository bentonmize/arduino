#include "ring.h"

Pulse::Pulse(int brightness, boolean rising, int min, int max, int change) {
    _brightness = brightness;
    _rising = rising;
    _min = min;
    _max = max;
    _change = change;
}

void Pulse::run(Adafruit_NeoPixel& ring) {
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

    ring.setBrightness(this->_brightness);
    ring.show();
}