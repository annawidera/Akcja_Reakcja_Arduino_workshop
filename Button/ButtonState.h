enum ButtonState {
  released, 
  pressed, 
  holdDown, 
  holdUp
};

struct Button {
  int index; 
  ButtonState state;
  unsigned long int startTime; // for pressed and released it's point in the time. For pressed it's duration
  unsigned long int duration; 
};




void updateButtonState(Button &button, ButtonState state, unsigned long int startTime) {
  
    button.state = state; 
    button.startTime = startTime; 
    button.duration = 0;  
}

void updateButtonStateDuration(Button &button, ButtonState state, unsigned long int now) {
  
    button.state = state;
    button.duration = now - button.startTime;  
}

void writeState(ButtonState state) {
  
  switch (state) {
    case released:  Serial.print("released"); break;
    case pressed:   Serial.print("pressed"); break;
    case holdDown:  Serial.print("holdDown"); break;
    case holdUp:   Serial.print("holdUp"); break;
  }
}

