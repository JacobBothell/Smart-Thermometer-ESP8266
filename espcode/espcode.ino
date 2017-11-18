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
#define HEAT 14
#define COOL 12
#define FAN 13
#define RELAY_4 15

//digital pin for dht11
#define DHTPIN 2
//define type could be 21 or 22 depending on sensor
#define DHTTYPE DHT11
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

//related to the DHT11 sensor
float Humidity = 0;
float Temperature = 0;
bool Celsius = true;
long lastReadTime = 0;
long currReadTime = 0;

//sets the state of the HVAC system
//  0 OFF
//  1 HEAT
//  2 COOL
int hvacSystem = 0;
//tells if system is active
bool hvacActive = false;

//temperature set points
int setPoint = 75;
#define DIFF 2

//returns false if there is a sensor problem
bool readTemp() {
  //read sensor
  Humidity = dht.readHumidity();
  //reads either C or F
  if(Celsius)
  {
    Temperature = dht.readTemperature();
  }
  else
  {
    Temperature = dht.readTemperature(true);
  }

  // Check if any reads failed and exit early (to try again).
//TODO text number if sensor stops working
  if (isnan(Humidity) || isnan(Temperature))
  {
    Serial.println("Failed to read from DHT sensor!");
    return false;
  }

  return true;
  
}

void setHVAC()
{
  //setting state of HVAC based uppon reading
  
  //turns heat on
  if(hvacSystem == 1 && !(hvacActive) && setPoint - DIFF > Temperature)
  {
    digitalWrite(HEAT, HIGH);
    hvacActive = true;
  }
  //turns heat off
  if(hvacSystem == 1 && hvacActive && setPoint < Temperature)
  {
    digitalWrite(HEAT, LOW);
    hvacActive = false;
  }
  //turns AC on
  if(hvacSystem == 2 && !(hvacActive) && setPoint + DIFF < Temperature)
  {
    digitalWrite(COOL, HIGH);
    hvacActive = true;
  }
  //turns AC off
  if(hvacSystem == 2 && hvacActive && setPoint > Temperature)
  {
    digitalWrite(COOL, LOW);
    hvacActive = false;
  }
}

void systemOff()
{
  digitalWrite(HEAT, LOW);
  digitalWrite(COOL, LOW);
  digitalWrite(FAN, LOW);
}

void setup() {
  Serial.begin(9600);
  
  //setup dht sensor
  dht.begin();

  //used for a timmer
  lastReadTime = millis();
}

void loop() {
  
  currReadTime = millis();
  if(currReadTime-lastReadTime >= 1000)
  {
    if(readTemp())
    {
      setHVAC();
    }
    else
    {
      systemOff();
    }
  }
  
}
