#include "NoiseState.h"

#define NOISE_SENSOR_PIN A1


void setup() {

  pinMode(NOISE_SENSOR_PIN, INPUT); 
  
  Serial.begin(115200);
} 



void loop() {

  int microphoneValue = analogRead(NOISE_SENSOR_PIN);
//  Serial.println(microphoneValue);
  if ( checkIfNoiseChanged(microphoneValue) == true ) {
    NoiseState noise = noiseStateBasedOn(microphoneValue);
    writeEqualizer(noise);
  }
} 
