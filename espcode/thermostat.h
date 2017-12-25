#ifndef Thermostat_h
#define Thermostat_h

#ifndef DHTTYPE
//what type of sensor is attached
#define DHTTYPE DHT11

#include "DHT.h"
#include "thermostat.cpp"


class Thermostat
{
  public:
  Thermostat();
  Thermostat(int heatPin, int coolPin, int fanPin, int dht11Pin, int high, int low, int maxDifference, bool celsius);
    
  private:
  //external variables
  int High, Low, MaxDifference, HeatPin, CoolPin, FanPin, DHT11Pin;
  bool Celsius;
  //internal variables
  int currTemp, currHumid;
  //private functions
  bool readTemp();
  void systemOff();
}

#endif
#endif
