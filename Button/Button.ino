#include <Bounce2.h>
#include <Callback.h>

#include "ButtonState.h"

#define buttonsCount 3
const int buttonsPins[] = { 2, 3, 4 };

Bounce buttonsDebounced[buttonsCount];
Button buttonsStates[buttonsCount];
Signal<Button> buttonPressed;


void buttonPressedHandler(Button button) {
  if (button.state == holdUp) {
    return;
  }

  Serial.print("button "); Serial.print(button.index); 
  Serial.print("     state: ");  writeState(button.state); 
  Serial.print("  "); Serial.print(button.state);
  Serial.print("     startTime: "); Serial.print(button.startTime);
  Serial.print("     duration: "); Serial.println(button.duration);
}

FunctionSlot<Button> buttonPressedFuncSlot(buttonPressedHandler);




void setup() {
  
  unsigned long int now = millis();
  
  for (int i=0; i < buttonsCount; i++) {
    
    pinMode(buttonsPins[i], INPUT);
    digitalWrite(buttonsPins[i], HIGH); 
    buttonsDebounced[i] = Bounce(); 
    buttonsDebounced[i].attach(buttonsPins[i]); 
    buttonsDebounced[i].interval(150);  

    buttonsStates[i] = {i, released, now, 0 };
  }
  
  buttonPressed.Connect(buttonPressedFuncSlot);
  
  Serial.begin(115200);
}


void loop() {
  
  checkButtons();
}



void checkButtons() {

  unsigned long int now = millis();
  
  for (int i = 0; i < buttonsCount; i++) {
    
    buttonsDebounced[i].update();
    
    if (buttonsDebounced[i].rose() == 1) {
      updateButtonState(buttonsStates[i], pressed, now);

    } else if (buttonsDebounced[i].fell() == 1) {
      updateButtonState(buttonsStates[i], released, now);
      
    } else if (buttonsDebounced[i].read() == HIGH) {
      updateButtonStateDuration(buttonsStates[i], holdDown, now);
      
    } else if (buttonsDebounced[i].read() == LOW) {
      updateButtonStateDuration(buttonsStates[i], holdUp, now);
    }

    buttonPressed.Emit(buttonsStates[i]);
  } 
}




