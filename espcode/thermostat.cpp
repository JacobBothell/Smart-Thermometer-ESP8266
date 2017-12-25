Thermostat::Thermostat()
{
  HeatPin = 0;
  CoolPin = 1;
  FanPin = 2;
  DHT11Pin = 3;
  High = 75;
  Low = 70;
  MaxDifference = 2;
  Celcius = false;
  dht.close();
  // Initialize DHT sensor.
  DHT dht(DHT11Pin, DHTTYPE); 
  //setup dht sensor
  dht.begin();
}

Thermostat::Thermostat(int heatPin = HeatPin, int coolPin = CoolPin, int fanPin = FanPin, int dht11Pin = DHT11P11in, int high = High, int low = Low, int maxDifference = MaxDifference, bool celcius = Celcius)
{
  HeatPin = heatPin;
  CoolPin = coolPin;
  FanPin = fanPin;
  DHT11Pin = dht11Pin;
  High = high;
  Low = low;
  MaxDifference = maxDifference;
  Celcius = celcius;
  dht.close();
  // Initialize DHT sensor.
  DHT dht(DHTPIN, DHTTYPE);
  //setup dht sensor
  dht.begin();  
}

//returns false if sensor read was unsuccessful
Thermostat::bool readTemp()
{
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

  return true
}

Thermostat::void systemOff()
{
  digitalWrite(HEAT, LOW);
  digitalWrite(COOL, LOW);
  digitalWrite(FAN, LOW);
}


//TODO: add interrupt that calls setHVAC
//TODO: rewrite setHVAC with new variables and check logic
void setHVAC()
{
  readTemp();
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

