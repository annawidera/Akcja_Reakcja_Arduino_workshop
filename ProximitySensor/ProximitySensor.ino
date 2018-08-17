#include <Adafruit_APDS9960.h>

Adafruit_APDS9960 apds;


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
}



void loop() {

  Serial.print("proximity: "); Serial.println(getProximity());
  delay(300);  
}


uint8_t getProximity() { 

  return apds.readProximity(); 
}

