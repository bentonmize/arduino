// Arduino Uno sketch for driving 12 LED NeoPixel ring with various animations
// 2023 Benton Mize

// Built on:
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include "arc.h"
#include "rainbow.h"
#include "pitches.h"
#include "ring.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NEO_PIN   6
#define NUMPIXELS 12

Adafruit_NeoPixel ring(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  ring.begin(); // init NeoPixel ring object (REQUIRED)

  Serial.begin(115200);
  while(!Serial) {
    delay(10);
  }

  Serial.println("Initialized!");
}

long bored = 0;
String command = "fire";
Pulse pulse(8, true, 4, 32, 1);

void clearRing() {
  ring.clear();
  ring.show();
}

void loop() {
  // Clear the ring
  clearRing();

  // Main loop when we're not taking serial commands
  while(Serial.available() == 0) {
    if(command == "arc") {
      arcReactor(ring);
    } else if(command == "spin") {
      rainbowSpin(ring);
    } else if(command == "rainbow") {
      rainbow(ring);
    } else if(command == "pulse") {
      pulseColor(ring, pulse);
    } else if(command == "fire") {
      fire(ring);
    }else if(command == "") {
      // Idle states
    } else {
      // Reset the arc variables if we stop using it
      arcReset();

      // Clear the ring
      clearRing();

      command = "";
    }
  }

  // Get a command (we'll parse it in the loop above)
  command = Serial.readString();
  command.trim();
  Serial.println(command);
}
