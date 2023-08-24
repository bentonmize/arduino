#include "arc.h"

uint8_t arcCount = 0;
uint16_t arcDelay = ARC_INIT_LOOPS;
int arcBrightness = 0;
int arcMinBrightness = 0;
boolean arcBrightnessRising = true;
boolean arcComplete = false;
uint8_t arcRotationPin[4] = {0, 1, 2, 3};
uint8_t delayCount = 0;

void arcReset() {
  arcCount = 0;
  arcDelay = ARC_INIT_LOOPS;
  arcBrightness = 0;
  arcMinBrightness = 0;
  arcBrightnessRising = true;
  arcComplete = false;
}

void arcReactor(Adafruit_NeoPixel& ring) {
  uint32_t reactorColor = ring.Color(0, 255, 255);
  
  ring.fill(reactorColor, 0, ring.numPixels()); 

  ring.setBrightness(arcBrightness);

  if(!arcComplete) {
    if(arcBrightnessRising) {
      arcBrightness += ARC_BRIGHT_INT;
    } else {
      arcBrightness -= ARC_BRIGHT_INT;
    }
  
    if(arcBrightness > ARC_MAX_BRIGHT) {
      arcBrightnessRising = false;
      arcBrightness = ARC_MAX_BRIGHT;
      if(arcCount >= ARC_INIT_LOOPS) {
        arcComplete = true;
      } else {
        arcDelay -= 1;
      }
    } else if(arcBrightness < arcMinBrightness) {
      arcBrightnessRising = true;
      arcMinBrightness += ARC_MIN_BRIGHT_INT;
      arcBrightness = arcMinBrightness;
      arcCount++;
    }

    delay(arcDelay);
  } else {
    // Do a slight rotation animation here after "pulse start"
    ring.fill(reactorColor, 0, ring.numPixels());
    ring.setPixelColor(arcRotationPin[0], 0, 128, 128);
    ring.setPixelColor(arcRotationPin[1], 0, 128, 128);
    ring.setPixelColor(arcRotationPin[2], 0, 200, 200);
    ring.setPixelColor(arcRotationPin[3], 0, 128, 128);

    for(int i = 0; i < 4; i++) {
      arcRotationPin[i] = arcRotationPin[i] + 1;
      if(arcRotationPin[i] >= ring.numPixels()) {
        arcRotationPin[i] = 0;
      }
    }
    
    if(delayCount < MAX_DELAY_COUNT) {
      if(arcBrightnessRising) {
        arcBrightness += ARC_PULSE_BRIGHT_INT;
      } else {
        arcBrightness -= ARC_PULSE_BRIGHT_INT;
      }

      if(arcBrightness > ARC_PULSE_MAX_BRIGHT) {
        arcBrightnessRising = false;
        arcBrightness = ARC_PULSE_MAX_BRIGHT;
      } else if(arcBrightness < ARC_PULSE_MIN_BRIGHT) {
        arcBrightnessRising = true;
        arcBrightness = ARC_PULSE_MIN_BRIGHT;
      }

      ring.setBrightness(arcBrightness);
    } else {
      delayCount = 0;
    }
    delayCount++;

    delay(15);
  }

  ring.show();
}
