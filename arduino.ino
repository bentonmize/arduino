// Arduino Uno sketch for driving LEDs for profit
// 2023 Benton Mize

// Built on:
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "arc.h"
#include "rainbow.h"
#include "ring.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include "animation.h"
#include "NeoPixelSegment.h"
#include "colors.h"
#include <pins_arduino.h>

#define NEO_PIN   6   // Pin where I2C is setup
#define NUMPIXELS 13  // One ring and then an additional

Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);
NeoPixelSegment* ring;
NeoPixelSegment* single;

void setup() {
  pixels.begin(); // init NeoPixel array object (REQUIRED)
  ring = new NeoPixelSegment(&pixels, 0, 12);
  single = new NeoPixelSegment(&pixels, 12, 1);

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), handleButtonPress, RISING);

  Serial.begin(230400);
  while(!Serial) {
    delay(10);
  }

  pinMode(2, INPUT);

  Serial.println("Initialized!");

  ring->fill("green");
  single->fill("blue");

  single->setBrightness(4);
  ring->setBrightness(8);

  ring->setAnimation(fire);
}

String command = "";
String subcommand = "";
String originalCommand = "";

unsigned previousMillis = -1;
unsigned long iterations = 0;
int delta = 0;
bool tick = false;
bool buttonPressed = false;

void loop() {
  // Get the delta, trying to make a 5ms clock here for driving LEDs
  delta = millis() - previousMillis;
  if(delta >= 10) {
    previousMillis = millis();
    iterations++;
    tick = true;
  } else {
    tick = false;
  }

  if(tick) {
    if(buttonPressed && (iterations % 10 == 0)) {
      buttonPressed = false;
      single->fill(getRandomColor().name);
    }

    if(iterations % 5 == 0) {
      ring->animate();
    }
  } 

  // If we have serial work to do handle it
  if(Serial.available() > 0) {
    command = Serial.readString();
    command.trim();

    originalCommand = command;

    uint8_t hyphenIndex = command.indexOf('-');
    if(hyphenIndex > 0) {
      subcommand = command.substring(hyphenIndex+1);
      command = command.substring(0, hyphenIndex);
    }

    Serial.println(originalCommand);
    command = "";
  }
}

// Do something interesting with this button press :D
void handleButtonPress() {
  buttonPressed = true;
}

RgbColor getFireColor() {
  uint8_t r = random(180, 255);
  uint8_t g = random(64, 128);

  if (g > r) {
    g = r;
  }

  return RgbColor("", r, g, 0);
}

void fire(NeoPixelSegment& segment) {
  for (int i = 0; i < segment.getLength(); i++) {
    segment.setPixelColor(i, getFireColor());
    segment.setPixelBrightness(i, random(8, 16));
  }
  segment.show();
}