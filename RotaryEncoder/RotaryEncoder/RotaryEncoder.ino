#include <RotaryEncoder.h>
#include "RotaryCounter.h"


void setup() {

  setupEncoder();
  Serial.begin(115200);
} 


void loop() {
  
 static int pos = 0;

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    pos = newPos;
    Serial.print("new pos:"); Serial.println(pos);
  }
} 
