#include <Arduino.h>
#include <TaskScheduler.h>
#include <DHT.h>
#include <Array>
#include <Sensors.h>

#define BLINK_INTERVAL 79
#define SENSING_INTERVAL 60000

void updateLEDs();
void printSensorData();

Scheduler runner;
DHT dht;
LM393SoilMoisture soilSensor;

Task ledUpdateTask(BLINK_INTERVAL, TASK_FOREVER, &updateLEDs, &runner, true);
Task sensingTask(SENSING_INTERVAL, TASK_FOREVER, &printSensorData, &runner, true);

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

void printSensorData() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  uint8_t moisture = soilSensor.measure();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(moisture, 1);
  Serial.print("\n");
}

void setup() {
  //Pin Setup
  pinMode(D0, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
  dht.setup(D3);
  soilSensor.setup(D2, A0);

  //Serial Setup
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t Moisture (%)");

  //Start task routines
  runner.startNow();
}

void loop () {
  runner.execute();
}
