#include <Callback.h>
#include "VariableResistorState.h"

#define VARIABLE_RESISTOR_PIN A4


Signal<int> resistorValueChanged;
Signal<VariableResistor> resistorThresholdChanged;
Signal<int> highSignal;
Signal<int> lowSignal; 
Signal<int> highestEverSignal;




void resistorValueHandler(int value) {
  
  Serial.print("value "); Serial.println(value); 
}


void resistorThresholdChangedHandler(VariableResistor resistor) {

  Serial.print("threshold "); writeState(resistor.threshold); Serial.print("   value: "); Serial.println(resistor.value);
}


void highHandler(int value) {

  Serial.println("VERY HIGH!");
}

void lowHandler(int value) {

  Serial.println("LOW VALUES");
}


void highestEverHandler(int value) {

  Serial.print("Heeeey! It is wayyy higher than before!!      "); Serial.println(value);
}




FunctionSlot<int> resistorValueFuncSlot(resistorValueHandler);
FunctionSlot<VariableResistor> resistorThresholdChangedFuncSlot(resistorThresholdChangedHandler);
FunctionSlot<int> highFuncSlot(highHandler);
FunctionSlot<int> lowFuncSlot(lowHandler);
FunctionSlot<int> highestEverFuncSlot(highestEverHandler);

void setup() {

  pinMode(VARIABLE_RESISTOR_PIN, INPUT); 
  
  resistorValueChanged.Connect(resistorValueFuncSlot);  
  resistorThresholdChanged.Connect(resistorThresholdChangedFuncSlot);
  highSignal.Connect(highFuncSlot);
  lowSignal.Connect(lowFuncSlot);
  highestEverSignal.Connect(highestEverFuncSlot);
  
  Serial.begin(115200);
} 



void loop() {

  int resistorValue = analogRead(VARIABLE_RESISTOR_PIN);
  
  if (checkIfResistanceChanged(resistorValueChanged, resistorValue) == true ) {
    checkIfResistorThresholdChanged(resistorThresholdChanged, resistorValue);
    checkHighestEver(highestEverSignal, resistorValue);
  }
  checkLowHigh(lowSignal, highSignal, resistorValue);
} 



