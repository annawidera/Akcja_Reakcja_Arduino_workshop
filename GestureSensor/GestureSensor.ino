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
  
  // for gesture mode, proximity is required
  apds.enableProximity(true);
  apds.enableGesture(true);
}



void loop() {

  checkGesture();
}


void checkGesture() { 

    uint8_t gesture = apds.readGesture();
    if(gesture == APDS9960_DOWN) {
      Serial.println("v");
    } else if(gesture == APDS9960_UP) {
      Serial.println("^");
    } else if(gesture == APDS9960_LEFT) {
      Serial.println("<");
    } else if(gesture == APDS9960_RIGHT) {
      Serial.println(">");
    }
}

