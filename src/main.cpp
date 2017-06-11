#include <Arduino.h>
#include <Eventually.h>
#include <DHT.h>
#include <Array>

#define BLINK_INTERVAL 79
#define SENSING_INTERVAL 60000

EvtManager mgr;
DHT dht;

std::array<uint8_t, 6> ledSequence  = { D0, D0, D5, D6,  D6, D5 };
uint8_t currentIndex = 0;

void disableLEDs() {
  digitalWrite(D0, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
}

bool updateLEDs() {
  disableLEDs();
  digitalWrite(ledSequence[currentIndex], HIGH);
  currentIndex = (currentIndex + 1) % ledSequence.size();

  return true;
}

bool printSensorData() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\n");

  return true;
}

void setup() {
  //Pin Setup
  pinMode(D0, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
  dht.setup(D3);

  //Serial Setup
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)");

  //Start event routines
  //mgr.addListener(new EvtTimeListener(BLINK_INTERVAL, true, (EvtAction)updateLEDs));
  mgr.addListener(new EvtTimeListener(SENSING_INTERVAL, true, (EvtAction)printSensorData));
}

USE_EVENTUALLY_LOOP(mgr)
