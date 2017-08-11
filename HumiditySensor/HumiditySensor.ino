#include <DHT.h>
#include <Callback.h>

#define DHT_DATA_PIN 3

Signal<float> humidityValueChanged; 
Signal<float> temperatureValueChanged;

void humidityValueChangeHandler(float humidity) {

  Serial.print("humidity: "); Serial.println(humidity);
}


void temperatureValueChangedHandler(float temperature) {

  Serial.print("temperature: "); Serial.print(temperature); Serial.println(" *C");
}

FunctionSlot<float> humidityValueChangedFuncSlot(humidityValueChangeHandler); 
FunctionSlot<float> temperatureValueChangedFuncSlot(temperatureValueChangedHandler); 

DHT dht;


void setup() {

  dht.setup(DHT_DATA_PIN);
  Serial.begin(115200);
  humidityValueChanged.Connect(humidityValueChangedFuncSlot);
  temperatureValueChanged.Connect(temperatureValueChangedFuncSlot);
}


void loop() {
  
  delay(dht.getMinimumSamplingPeriod());

  checkHumidity();
  checkTemperature();
}



void checkHumidity() {

  humidityValueChanged.Emit(dht.getHumidity());
}

void checkTemperature() {

  temperatureValueChanged.Emit(dht.getTemperature());
}

