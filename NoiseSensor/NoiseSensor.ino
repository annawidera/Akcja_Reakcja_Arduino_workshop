#include <Callback.h>
#include "NoiseState.h"

#define NOISE_SENSOR_PIN A1


Signal<int> noiseValueChanged;
Signal<Noise> noiseStateValueChanged;
Signal<int> screamSignal;
Signal<int> loudestEverSignal;




void noiseValueHandler(int value) {
  
  Serial.print("noise value "); Serial.println(value); 
}


void noiseStateValueHandler(Noise noise) {

  Serial.print("state "); writeState(noise.state); Serial.print("   value: "); Serial.println(noise.microphoneValue);
}


void screamHandler(int value) {

  Serial.println("SCREEEEAAAAAAAM");
}


void loudestEverHandler(int value) {

  Serial.print("Heeeey! It is wayyy louder than before!!      "); Serial.println(value);
}




FunctionSlot<int> noiseValueFuncSlot(noiseValueHandler);
FunctionSlot<Noise> noiseStateValueFuncSlot(noiseStateValueHandler);
FunctionSlot<int> screamFuncSlot(screamHandler);
FunctionSlot<int> loudestEverFuncSlot(loudestEverHandler);

void setup() {

  pinMode(NOISE_SENSOR_PIN, INPUT); 
  
  noiseValueChanged.Connect(noiseValueFuncSlot);  
  noiseStateValueChanged.Connect(noiseStateValueFuncSlot);
  screamSignal.Connect(screamFuncSlot);
  loudestEverSignal.Connect(loudestEverFuncSlot);
  
  Serial.begin(115200);
} 



void loop() {

  int microphoneValue = analogRead(NOISE_SENSOR_PIN);
  
  if (checkIfNoiseChanged(noiseValueChanged, microphoneValue) == true ) {
    checkIfNoiseStateChanged(noiseStateValueChanged, microphoneValue);
    checkLoudestEver(loudestEverSignal, microphoneValue);
  }
  checkScreaming(screamSignal, microphoneValue);
} 



