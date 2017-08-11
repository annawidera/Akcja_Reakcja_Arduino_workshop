#include <Bounce2.h>
#include <Callback.h>

#define tiltCount 1
const int tiltPins[] = {9};// { 2, 3, 4 };
#define LED_PIN 13

Bounce tiltDebounced[tiltCount];
Signal<bool> tiltStateChangedSignal;


void tiltStateChangedHandler(bool tiltPressed) {

  digitalWrite(LED_PIN, tiltPressed);
}

FunctionSlot<bool> tiltStateChangedFuncSlot(tiltStateChangedHandler);




void setup() {
  
  pinMode(LED_PIN, OUTPUT);
  
  for (int i=0; i < tiltCount; i++) {
    
    pinMode(tiltPins[i], INPUT);
    digitalWrite(tiltPins[i], HIGH);   // turn on the built in pull-up resistor
    tiltDebounced[i] = Bounce(); 
    tiltDebounced[i].attach(tiltPins[i]); 
    tiltDebounced[i].interval(100);  
  }
  
  tiltStateChangedSignal.Connect(tiltStateChangedFuncSlot);
  
  Serial.begin(115200);
}


void loop() {
  
  for (int i = 0; i < tiltCount; i++) {
    
    tiltDebounced[i].update();
    tiltStateChangedSignal.Emit(tiltDebounced[i].read());
  }
}


