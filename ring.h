#ifndef RING_H
#define RING_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

class Pulse {
    public:
        Pulse(int brightness, boolean rising, int min, int max, int change);
        uint8_t run();
    
    private:
        int _brightness;
        boolean _rising;
        int _max;
        int _min;
        int _change;
};

#endif