#include <Adafruit_APDS9960.h>
#include <Callback.h>

Adafruit_APDS9960 apds;


Signal<uint8_t> proximityMeasurementSignal; 


void proximityMeasurementHandler(uint8_t proximity) {

  Serial.println("proximity: "); Serial.println(proximity);
}

FunctionSlot<uint8_t> proximityMeasurementSlot(proximityMeasurementHandler); 


void setup() {
  
  Serial.begin(115200);

  if(!apds.begin()) { 
    Serial.println("Initialisation failed.");
  }
  else {
    Serial.println("APDS9960 initialized!");
  }
  
  apds.setProxGain(APDS9960_PGAIN_8X);
  // for gesture mode, proximity is required
  apds.enableProximity(true);
  
  proximityMeasurementSignal.Connect(proximityMeasurementSlot);
}



void loop() {

  proximityMeasurementSignal.Emit(apds.readProximity());
}
