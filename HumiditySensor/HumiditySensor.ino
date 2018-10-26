#include <DHT.h>

#define DHT_DATA_PIN 2

DHT sensor;
float currentHumidity = 0; 
float currentTemperature = 0; 


void setup() {

  sensor.setup(DHT_DATA_PIN);
  Serial.begin(115200);
}


void loop() {
  
  delay(sensor.getMinimumSamplingPeriod());

  checkHumidity();
  checkTemperature();
}



void checkHumidity() {

  currentHumidity = sensor.getHumidity();
  Serial.print("hum: "); Serial.print(currentHumidity); Serial.println("%");
}


void checkTemperature() {

  currentTemperature = sensor.getTemperature();
  Serial.print("\t\t temp: "); Serial.print(currentTemperature); Serial.println("*C");
}

