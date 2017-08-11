#include <Callback.h>
#include "ForceState.h"

#define FORCE_RESISTOR_PIN A4


Signal<int> forceValueChanged;
Signal<Force> forceStateValueChanged;
Signal<int> clampSignal;
Signal<int> hardestEverSignal;




void forceValueHandler(int value) {
  
  Serial.print("force value "); Serial.println(value); 
}


void forceStateValueHandler(Force force) {

//  Serial.print("state "); writeState(force.state); Serial.print("   value: "); Serial.println(force.value);
}


void clampHandler(int value) {

//  Serial.println("squeeeeeeeeeze");
}


void hardestEverHandler(int value) {

//  Serial.print("Heeeey! It is wayyy harder than before!!      "); Serial.println(value);
}




FunctionSlot<int> forceValueFuncSlot(forceValueHandler);
FunctionSlot<Force> forceStateValueFuncSlot(forceStateValueHandler);
FunctionSlot<int> clampFuncSlot(clampHandler);
FunctionSlot<int> hardestEverFuncSlot(hardestEverHandler);

void setup() {

  pinMode(FORCE_RESISTOR_PIN, INPUT); 
  
  forceValueChanged.Connect(forceValueFuncSlot);  
  forceStateValueChanged.Connect(forceStateValueFuncSlot);
  clampSignal.Connect(clampFuncSlot);
  hardestEverSignal.Connect(hardestEverFuncSlot);
  
  Serial.begin(115200);
} 



void loop() {

  int forceValue = analogRead(FORCE_RESISTOR_PIN);
  
  if (checkIfForceChanged(forceValueChanged, forceValue) == true ) {
    checkIfForceStateChanged(forceStateValueChanged, forceValue);
    checkHardestEver(hardestEverSignal, forceValue);
  }
  checkClamp(clampSignal, forceValue);
} 



