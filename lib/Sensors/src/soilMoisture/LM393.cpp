#include "LM393.h"

#define ANALOG_MAX 1023

/**
 * Initializes the sensor.
 * @param {uint8_t} enablePin The pin connected to the sensors vcc pin
 */
void LM393SoilMoisture::setup(uint8_t enablePin, uint8_t sensePin) {
  LM393SoilMoisture::enablePin = enablePin;
  LM393SoilMoisture::sensePin = sensePin;
  pinMode(enablePin, OUTPUT);
}

/**
 * Measures the soil conductivity.
 * @param  {uint8_t} enablePin The pin connected to the sensors vcc pin
 * @param  {uint8_t} sensePin  The pin connected to the sensors AO pin
 * @return {uint8_t} The measured value in percent relative to  ANALOG_MAX
 */
uint8_t LM393SoilMoisture::measure() {
  digitalWrite(LM393SoilMoisture::enablePin, HIGH);
  uint8_t value = (uint8_t)((analogRead(LM393SoilMoisture::sensePin) * 100) / ANALOG_MAX);
  digitalWrite(LM393SoilMoisture::enablePin, LOW);
  return value;
}
