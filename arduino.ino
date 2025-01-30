// Arduino Uno sketch for driving 12 LED NeoPixel ring with various animations
// 2023 Benton Mize

// Built on:
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include "arc.h"
#include "rainbow.h"
#include "ring.h"

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include "NeoPixelSegment.h"

#define NEO_PIN   6
#define NUMPIXELS 13  // One ring and then an additional

Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

NeoPixelSegment* ring;
NeoPixelSegment* single;

int bright = 4;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // init NeoPixel array object (REQUIRED)
  ring = new NeoPixelSegment(&pixels, 0, 12);
  single = new NeoPixelSegment(&pixels, 12, 1);

  Serial.begin(115200);
  while(!Serial) {
    delay(10);
  }

  pinMode(2, INPUT);

  Serial.println("Initialized!");

  ring->fill(pixels.Color(150, 0, 0));
  single->fill(pixels.Color(0, 0, 150));
  ring->setPixelBrightness(3, bright);
  ring->setBrightness(12);
}

String command = "";
String subcommand = "";
String originalCommand = "";

void loop() {
  // Clear the ring
  // ring->clear();

  // Main loop when we're not taking serial commands
  while(Serial.available() == 0) {
    delay(200);

    ring->setPixelBrightness(3, bright++);

    // if(command == "arc") {
    //   arcReactor(ring);
    // } else if(command == "spin") {
    //   rainbowSpin(ring);
    // } else if(command == "rainbow") {
    //   rainbow(ring);
    // } else if(command == "pulse") {
    //   if(subcommand == "green") {
    //     pulseColor(ring, pulse, 4);
    //   } else if(subcommand == "red") {
    //     pulseColor(ring, pulse, 0);
    //   }
    // } else if(command == "ice") {
    //   ice(ring);
    // } else if(command == "fire") {
    //   if(count % 2 == 0) {
    //     fire(ring);
    //   } else {
    //     ice(ring);
    //   }
    // } else if(command == "pixels") {
    //   int pixelPulse = pulse.run();
    //   int color = ring.Color(0, 0, pixelPulse);
    //   pulsePixel(ring, color, 8);
    //   pulsePixel(ring, color, 9);
    //   pulsePixel(ring, color, 10);
    // } else if(command == "progress") {
    //   if(subcommand == "red") {
    //     arcProgress(ring, 255, 0, 0);
    //   } else if(subcommand == "purple") {
    //     arcProgress(ring, 127, 0, 255);
    //   }else if(subcommand == "green") {
    //     arcProgress(ring, 0, 255, 0);
    //   } else if(subcommand == "yellow") {
    //     arcProgress(ring, 255, 255, 0);
    //   } else if(subcommand == "blue") {
    //     arcProgress(ring, 0, 0, 255);
    //   } else if(subcommand == "white") {
    //     arcProgress(ring, 255, 255, 255);
    //   }
    // } else if(command == "") {
    //   // Idle states
    // } else {
    //   // Reset the arc variables if we stop using it
    //   arcReset();

    //   // Clear the ring
    //   clearRing();

    //   command = "";
    // }
  }

  // Get a command (we'll parse it in the loop above)
  command = Serial.readString();
  command.trim();

  originalCommand = command;

  uint8_t spaceIndex = command.indexOf('-');
  if(spaceIndex > 0) {
    subcommand = command.substring(spaceIndex+1);
    command = command.substring(0, spaceIndex);
  }

  Serial.println(originalCommand);
}
