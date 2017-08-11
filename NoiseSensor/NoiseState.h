#define MUTE 15
#define QUIETLY 40
#define NOISLY 200
#define SUPER_LOUDLY 400
#define DELTA 3

enum NoiseState {
  mute,
  quietly, 
  noisly, 
  superLoudly, 
  brainInPieces
};

struct Noise {
  int microphoneValue; 
  NoiseState state; 
};

NoiseState noiseStateBasedOn(int value) {

  if (value > SUPER_LOUDLY ) {
    return brainInPieces;
  } else if (value > NOISLY) {
    return superLoudly;
  } else if (value > QUIETLY) {
    return noisly;
  } else if (value > MUTE) {
    return quietly;
  }
  return mute;
}


void writeState(NoiseState state) {
  
  switch (state) {
    case mute:  Serial.print("mute"); break;
    case quietly:   Serial.print("quietly"); break;
    case noisly:  Serial.print("noisly"); break;
    case superLoudly:   Serial.print("superLoudly"); break;
    case brainInPieces:   Serial.print("brainInPieces"); break;
  }
}


bool checkIfNoiseChanged(Signal<int> &noiseValueChangedEvent, int value) {

  static int microphoneValue = 0;

  if (abs(value - microphoneValue) > DELTA) {
    
      noiseValueChangedEvent.Emit(value);
      microphoneValue = value;
      return true;
  }
  return false;
}


bool checkIfNoiseStateChanged(Signal<Noise> &noiseStateChangedEvent, int value) {

  static NoiseState noiseState = mute;
  NoiseState newNoiseState = noiseStateBasedOn(value); 

  if (newNoiseState != noiseState) {
        
      Noise noise = { value, newNoiseState };
      noiseStateChangedEvent.Emit(noise);
      noiseState = newNoiseState;
      return true;
  }
  return false;
}


bool checkLoudestEver(Signal<int> &loudestEverSignal, int value) {
  
  static int loudestEver = 0;
  
  if (value > loudestEver) {
    
    loudestEverSignal.Emit(value);
    loudestEver = value;
    return true;
  }
  return false;
}



bool checkScreaming(Signal<int> &screamEvent, int value) {
  
  NoiseState noiseState = noiseStateBasedOn(value); 

  if (noiseState >= superLoudly) {
    screamEvent.Emit(value);
    return true;
  }
  return false;
}

