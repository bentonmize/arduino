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
#include "dht.h"
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

  pinMode(2, INPUT);

  Serial.println("Initialized!");
}

String command = "";
Pulse pulse(8, true, 1, 40, 1);
int count = 0;

int outputState = LOW;
int prevOutputState = LOW;

int prevButtonState = LOW;
int currentButtonState = LOW;
long lastDebounceTime = 0;

int debounceRead(int pin, int delay) {
  currentButtonState = digitalRead(pin);

  if(currentButtonState != prevButtonState) {
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime) > delay) {
      prevOutputState = outputState;
      outputState = currentButtonState;
  }

  prevButtonState = currentButtonState;
}

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
      int index = count % 12;
      pulseColor(ring, pulse, index);
    } else if(command == "ice") {
      ice(ring);
    } else if(command == "fire") {
      if(count % 2 == 0) {
        fire(ring);
      } else {
        ice(ring);
      }
    } else if(command == "pixels") {
      int pixelPulse = pulse.run();
      int color = ring.Color(0, 0, pixelPulse);
      pulsePixel(ring, color, 8);
      pulsePixel(ring, color, 9);
      pulsePixel(ring, color, 10);
    } else if(command == "") {
      // Idle states
    } else {
      // Reset the arc variables if we stop using it
      arcReset();

      // Clear the ring
      clearRing();

      command = "";
    }

    debounceRead(2, 1);

    if(prevOutputState == HIGH && outputState == LOW) {
      if(command != "fire") {
        count++;
        command = "fire";
      } else {
        command = "stop";
      }
      Serial.println(command);
    }
  }

  // Get a command (we'll parse it in the loop above)
  command = Serial.readString();
  command.trim();
  Serial.println(command);
}
