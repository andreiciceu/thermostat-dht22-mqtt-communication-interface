# MQTT & DHT22 CommunicatioInterface implementation for thermostat
DHT22 reading from RaspberryPI/Odroid and MQTT toggled relay

Check out `temp-reading\dhtXX\readme.md` for details on specific implementation

# Installation
Create `.env` file according to `.env.example`

## Logging
Logging into mysql database provided in `.env`
```SQL
CREATE TABLE state (
  id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  currentTemperature FLOAT,
  desiredTemperature FLOAT,
  heatingOn TINYINT,
  lastTemperatureUpdate DATETIME,
  currentTemperatureProgramName VARCHAR(50),
  someoneIsHome TINYINT
)
```