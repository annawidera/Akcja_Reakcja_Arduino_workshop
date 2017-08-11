#include <Callback.h>

#define MOTION_SENSOR_PIN 2


Signal<bool> isMotionSignal;

void isMotionHandler(bool isMotion) {

  switch (isMotion) {
    case true: Serial.println("Motion detected"); break; 
    case false: Serial.println("Motion disappeared"); break;
  }
}


FunctionSlot<bool> isMotionFuncSlot(isMotionHandler); 
 
void setup() {

  pinMode(MOTION_SENSOR_PIN, INPUT);
  isMotionSignal.Connect(isMotionFuncSlot); 
  Serial.begin(115200);
}

 
void loop(){

  static bool isMotion = false;

  bool checkMotion = digitalRead(MOTION_SENSOR_PIN);

  if (checkMotion != isMotion) {
      isMotionSignal.Emit(checkMotion); 
      isMotion = checkMotion; 
  }
}
