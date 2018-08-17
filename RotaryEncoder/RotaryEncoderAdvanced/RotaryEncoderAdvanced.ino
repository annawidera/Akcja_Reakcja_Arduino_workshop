-#include <RotaryEncoder.h>
#include <Callback.h>
#include "RotaryCounter.h"


Signal<int> encoderValueChanged;

void encoderValueChangedHandler(int value) {
  
  Serial.print("value "); Serial.println(value); 
  if (value > 150) {
    Serial.println("Go ahead and see what happens");
  }
}

FunctionSlot<int> encoderValueChangedFuncSlot(encoderValueChangedHandler);


void setup() {

  setupEncoder();
  encoderValueChanged.Connect(encoderValueChangedFuncSlot);  
  Serial.begin(115200);
} 



void loop() {
  
  checkEncoderHasNewValue(encoderValueChanged);
} 
