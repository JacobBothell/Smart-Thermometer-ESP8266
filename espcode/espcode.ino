//Jacob Bothell
//  Smart Thremostat
//    Using NodeMCU 2 board from AMICA
//
//  Other boards used:
//    DHT11 sensor
//    generic 4 relay board
//
//  connections:
//    DHT11 sensor == D4 (pull up resistor used)
//    Relay == D5, D6, D7, D8 respectfully

#include "DHT.h"

//these are for the realy board that controls HVAC unit
#define RELAY_1 14
#define RELAY_2 12
#define RELAY_3 13
#define RELAY_4 15

//digital pin for dht11
#define DHTPIN 2
//define type could be 21 or 22 depending on sensor
#define DHTTYPE DHT11
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
