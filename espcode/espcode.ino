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

#include "thermostat.h"


void setup() {
  Serial.begin(9600);

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
