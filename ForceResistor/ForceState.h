#define UNTOUCHED 10
#define LIGHT 100
#define MEDIUM 300
#define STRONG 600
#define DELTA 3

enum ForceState {
  untouched,
  light,
  medium, 
  strong, 
  superStrong
};

struct Force {
  int value; 
  ForceState state; 
};

ForceState forceStateBasedOn(int value) {

  if (value > STRONG ) {
    return superStrong;
  } else if (value > MEDIUM) {
    return strong;
  } else if (value > LIGHT) {
    return medium;
  } else if (value > UNTOUCHED) {
    return light;
  }
  return untouched;
}


void writeState(ForceState state) {
  
  switch (state) {
    case untouched:  Serial.print("untouched"); break;
    case light:   Serial.print("light"); break;
    case medium:  Serial.print("medium"); break;
    case strong:   Serial.print("strong"); break;
    case superStrong:   Serial.print("superStrong"); break;
  }
}


bool checkIfForceChanged(Signal<int> &forceValueChangedEvent, int value) {

  static int forceValue = 0;

  if (abs(value - forceValue) > DELTA) {
    
      forceValueChangedEvent.Emit(value);
      forceValue = value;
      return true;
  }
  return false;
}


bool checkIfForceStateChanged(Signal<Force> &forceStateChangedEvent, int value) {

  static ForceState forceState = untouched;
  ForceState newForceState = forceStateBasedOn(value); 

  if (newForceState != forceState) {
        
      Force force = { value, newForceState };
      forceStateChangedEvent.Emit(force);
      forceState = newForceState;
      return true;
  }
  return false;
}


bool checkHardestEver(Signal<int> &hardestEverSignal, int value) {
  
  static int hardestEver = 0;
  
  if (value > hardestEver) {
    
    hardestEverSignal.Emit(value);
    hardestEver = value;
    return true;
  }
  return false;
}



bool checkClamp(Signal<int> &clampEvent, int value) {
  
  ForceState forceState = forceStateBasedOn(value); 

  if (forceState >= strong) {
    clampEvent.Emit(value);
    return true;
  }
  return false;
}

