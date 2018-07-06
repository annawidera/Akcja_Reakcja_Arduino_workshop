#include <Adafruit_APDS9960.h>
#include <Callback.h>

Adafruit_APDS9960 apds;


Signal<uint8_t> gestureDetectedSignal;


void gestureDetectionHandler(uint8_t gesture) {
  
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


FunctionSlot<uint8_t> gestureDetectionSlot(gestureDetectionHandler); 


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
  
  gestureDetectedSignal.Connect(gestureDetectionSlot);
}



void loop() {

  gestureDetectedSignal.Emit(apds.readGesture());
}
