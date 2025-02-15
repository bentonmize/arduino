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
#include "neopixelsegment.h"
#include "colors.h"
#include "animation.h"
#include <pins_arduino.h>
#include "serial.h"

#define NEO_PIN   6   // Pin where I2C is setup
#define NUMPIXELS 13  // One ring and then an additional

Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);
NeoPixelSegment* ring;
NeoPixelSegment* single;

unsigned previousMs = -1;
unsigned buttonTriggerMs = -1;
int deltaMs = 0;

unsigned long iterations = 0;

bool tick = false;
bool buttonPressed = false;

FireState fireState;
PulseState pulseState;
PulseState ringPulseState;
ProgressState progressState;

SerialState serialState = SerialState();

void setup() {
  pixels.begin(); // init NeoPixel array object (REQUIRED)
  ring = new NeoPixelSegment(&pixels, 0, 12);
  single = new NeoPixelSegment(&pixels, 12, 1);

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), handleButtonPressIsr, FALLING);

  initSerialState(serialState);
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
  pulseState.max = 128;
  pulseState.min = 32;
  pulseState.increment = 5;
  pulseState.rate = 6;

  ringPulseState = PulseState();
  ringPulseState.rate = 10;

  single->fill("red");
  ring->fill("blue");
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
    // single->fill(getRandomColor().name);
    single->setAnimating(!single->getAnimating());
    ring->setAnimating(!ring->getAnimating());
  }

  // Running every 10ms
  if(tick) {
    // ring->animate(pulse, iterations, ringPulseState);
    ring->animate(progress, iterations, progressState);
    single->animate(pulse, iterations, pulseState);
  } 

  checkSerial(serialState);

  if(serialState.commandReceived) {
    serialState.commandReceived = false;
    Serial.println("Command received!");
    Serial.println(serialState.commands[0] + " " + serialState.commands[1]);
    processCommands(serialState.commands);
  }
}

void processCommands(String commands[]) {
  if(commands[0].equalsIgnoreCase("onair")) {
    single->fill(commands[1]);
    single->show();
  } else if(commands[0].equalsIgnoreCase("ring")) {
    ring->fill(commands[1]);
    single->show();
  }
}

// Do something interesting with this button press :D
void handleButtonPressIsr() {
  if(millis() - buttonTriggerMs > 500) {
    buttonPressed = true;
  }
  buttonTriggerMs = millis();
}