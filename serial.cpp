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
      state.buffer += input;
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
    uint8_t semicolonIndex = state.buffer.indexOf(';');
    uint8_t lastPosition = 0;
    state.numOfCommands = 0;

    while(hyphenIndex >= 0 && hyphenIndex < semicolonIndex) {
      state.commands[state.numOfCommands] = state.buffer.substring(lastPosition, hyphenIndex);
      lastPosition = hyphenIndex + 1;
      hyphenIndex = state.buffer.indexOf('-', lastPosition);
      state.numOfCommands++;
    }
    // If we have a command without a hyphen or a command at the end of a sequence
    if(lastPosition < semicolonIndex) {
      state.commands[state.numOfCommands] = state.buffer.substring(lastPosition, semicolonIndex);
      state.numOfCommands++;
    }
  }
}