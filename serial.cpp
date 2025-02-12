#include <Arduino.h>
#include "serial.h"

void initSerialState(SerialState& state) {
  state.buffer.reserve(128);
}

void checkSerial(SerialState& state) {
  // If we have serial work to do handle it
  if(Serial.available() > 0) {
    char input = Serial.read();

    if(!state.receiving) {
      state.buffer = "";
      state.receiving = true;
    }

    // Commands from the outside are separated by semicolons
    if(input == ';') {
      state.receiving = false;
      state.commandReceived = true;
    }

    if(state.receiving) {
      state.buffer += input;
    }
  }

  if(state.commandReceived) {
    state.receiving = false;

    // Hyphens separate command arguments
    uint8_t hyphenIndex = state.buffer.indexOf('-');
    if(hyphenIndex > 0) {
      state.commands[0] = state.buffer.substring(0, hyphenIndex);
      state.commands[1] = state.buffer.substring(hyphenIndex+1);
    }
  }
}