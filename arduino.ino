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

  Serial.println("Huzzah!");
}

long bored = 0;
String command = "spin";

void loop() {
  // rainbow(pixels);  
  // arcReactor(pixels);
  while(Serial.available() == 0) {
    // Do something while data is unavailable
    if(command == "arc") {
      arcReactor(ring);
    } else if(command == "spin") {
      rainbowSpin(ring);
    } else if(command == "rainbow") {
      rainbow(ring);
    } else if(command == "") {
      // Idle states
    } else {
      arcReset();
      ring.clear();
      ring.show();
      command = "";
    }
  }

  command = Serial.readString();
  command.trim();
  Serial.println(command);
}
