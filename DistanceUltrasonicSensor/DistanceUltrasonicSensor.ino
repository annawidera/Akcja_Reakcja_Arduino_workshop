#include <HCSR04.h>
#include "Position.h"

#define TRIG_PIN 2
#define ECHO_PIN 3

HCSR04 distanceSensor(TRIG_PIN, ECHO_PIN);


void setup() { 
  
  Serial.begin(115200); 
}


void loop() { 
  
  float currentDistance = distanceSensor.dist();
  Serial.println(currentDistance);
//  Position pos = positionBasedOn(currentDistance); 
//  writePosition(pos);
  delay(300);
}
