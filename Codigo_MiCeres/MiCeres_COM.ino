#include <SoftwareSerial.h>
#iclude <Wire.h>

int airQuality;

void setup() {

  Serial.begin(9600);
  Serial.flush();

}

void loop () {

}

int readAtmSensor () {

  airQuality = analogread();
  return airQuality;

}
