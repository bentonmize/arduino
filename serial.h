#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>

struct SerialState {
  String commands[2] = {"", ""};
  String buffer = "";
  boolean commandReceived = false;
  bool receiving = false;
};

void initSerialState(SerialState& state);
void checkSerial(SerialState& state);

#endif