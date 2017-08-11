#define FIRST_THRESHOLD 200
#define SECOND_THRESHOLD 400
#define THIRD_THRESHOLD 550
#define FOURTH_THRESHOLD 700
#define DELTA 3

enum ResistorThreshold {
  first,
  second,
  third, 
  fourth, 
  fifth
};

struct VariableResistor {
  int value; 
  ResistorThreshold threshold; 
};

ResistorThreshold resistorThresholdBasedOn(int value) {

  if (value > FOURTH_THRESHOLD ) {
    return fifth;
  } else if (value > THIRD_THRESHOLD) {
    return fourth;
  } else if (value > SECOND_THRESHOLD) {
    return third;
  } else if (value > FIRST_THRESHOLD) {
    return second;
  }
  return first;
}


void writeState(ResistorThreshold state) {
  
  switch (state) {
    case first:  Serial.print("first"); break;
    case second:   Serial.print("second"); break;
    case third:  Serial.print("third"); break;
    case fourth:   Serial.print("fourth"); break;
    case fifth:   Serial.print("fifth"); break;
  }
}


bool checkIfResistanceChanged(Signal<int> &resistanceValueChangedEvent, int value) {

  static int resistanceValue = 0;

  if (abs(value - resistanceValue) > DELTA) {
    
      resistanceValueChangedEvent.Emit(value);
      resistanceValue = value;
      return true;
  }
  return false;
}


bool checkIfResistorThresholdChanged(Signal<VariableResistor> &resistorStateChangedEvent, int value) {

  static ResistorThreshold resistorThreshold = first;
  ResistorThreshold newResistorThreshold = resistorThresholdBasedOn(value); 

  if (newResistorThreshold != resistorThreshold) {
        
      VariableResistor resistor = { value, newResistorThreshold };
      resistorStateChangedEvent.Emit(resistor);
      resistorThreshold = newResistorThreshold;
      return true;
  }
  return false;
}


bool checkHighestEver(Signal<int> &highestEverSignal, int value) {
  
  static int highestEver = 0;
  
  if (value > highestEver) {
    
    highestEverSignal.Emit(value);
    highestEver = value;
    return true;
  }
  return false;
}



void checkLowHigh(Signal<int> &lowEvent, Signal<int> &highEvent, int value) {
  
  ResistorThreshold resistorThreshold = resistorThresholdBasedOn(value); 

  if (resistorThreshold >= fourth) {
    highEvent.Emit(value);
  } else if (resistorThreshold <= second) {
    lowEvent.Emit(value);
  }
}

