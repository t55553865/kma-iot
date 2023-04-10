#include <SoftwareSerial.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial loraSerial(3, 1); // RX, TX

void setup() {
  loraSerial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String data = String(t) + "," + String(h);
  loraSerial.println(data);

  delay(2000);
}
