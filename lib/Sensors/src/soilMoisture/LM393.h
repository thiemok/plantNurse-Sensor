/*
Library for soil moisture sensors based on the LM393
*/
#ifndef LM393SOILMOISTURESENSOR_H
#define LM393SOILMOISTURESENSOR_H

#include <Arduino.h>

class LM393SoilMoisture {
  public:
    void setup(uint8_t enablePin, uint8_t sensePin);
    uint8_t measure();

  private:
    uint8_t enablePin;
    uint8_t sensePin;
};

#endif
