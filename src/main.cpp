#include <Arduino.h>
#include <Eventually.h>
#include <Array>

#define BLINK_INTERVAL 75

EvtManager mgr;
std::array<uint8_t, 6> ledSequence  = { D0, D0, D5, D6,  D6, D5 };
uint8_t currentIndex = 0;

void disableLEDs() {
  digitalWrite(D0, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
}

void updateLEDs() {
  disableLEDs();
  digitalWrite(ledSequence[currentIndex], HIGH);
  currentIndex = (currentIndex + 1) % ledSequence.size();
}

void setup() {
  pinMode(D0, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
  mgr.addListener(new EvtTimeListener(BLINK_INTERVAL, true, (EvtAction)updateLEDs));
}

USE_EVENTUALLY_LOOP(mgr)
