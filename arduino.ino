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
#include "animation.h"
#include <pins_arduino.h>

#define NEO_PIN   6   // Pin where I2C is setup
#define NUMPIXELS 13  // One ring and then an additional

Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);
NeoPixelSegment* ring;
NeoPixelSegment* single;

String command = "";
String subcommand = "";
String originalCommand = "";

unsigned previousMs = -1;
unsigned buttonTriggerMs = -1;
int deltaMs = 0;

unsigned long iterations = 0;

bool tick = false;
bool buttonPressed = false;

FireState fireState;
PulseState pulseState;

void setup() {
  pixels.begin(); // init NeoPixel array object (REQUIRED)
  ring = new NeoPixelSegment(&pixels, 0, 12);
  single = new NeoPixelSegment(&pixels, 12, 1);

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), handleButtonPressIsr, FALLING);

  Serial.begin(230400);
  while(!Serial) {
    delay(10);
  }

  setupAnimations();

  Serial.println("Initialized!");
}

void setupAnimations() {
  fireState = FireState();
  pulseState = PulseState();  
}

void loop() {
  // Get the delta, trying to make a 5ms clock here for driving LEDs
  deltaMs = millis() - previousMs;
  if(deltaMs >= 10) {
    previousMs = millis();
    iterations++;
    tick = true;
  } else {
    tick = false;
  }

  // Check button presses
  if(buttonPressed) {
    buttonPressed = false;
    single->fill(getRandomColor().name);
  }

  // Running every 10ms
  if(tick) {
    ring->animate(fire, iterations, fireState);
    single->animate(pulse, iterations, pulseState);
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
void handleButtonPressIsr() {
  if(millis() - buttonTriggerMs > 500) {
    buttonPressed = true;
  }
  buttonTriggerMs = millis();
}