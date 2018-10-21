#define MUTE 10
#define QUIETLY 50
#define NOISLY 300
#define SUPER_LOUDLY 600
#define DELTA 3

enum NoiseState {
  mute,
  quietly, 
  noisly, 
  superLoudly, 
  brainInPieces
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
    case mute:  Serial.println("mute"); break;
    case quietly:   Serial.println("quietly"); break;
    case noisly:  Serial.println("noisly"); break;
    case superLoudly:   Serial.println("superLoudly"); break;
    case brainInPieces:   Serial.println("brainInPieces"); break;
  }
}


void writeEqualizer(NoiseState state) {
  
  switch (state) {
    case mute:  Serial.println("▓▓▓"); break;
    case quietly:   Serial.println("▓▓▓▓▓▓▓▓▓"); break;
    case noisly:  Serial.println("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"); break;
    case superLoudly:   Serial.println("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"); break;
    case brainInPieces:   Serial.println("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"); break;
  }
}


bool checkIfNoiseChanged(int value) {

  static int microphoneValue = 0;

  if (abs(value - microphoneValue) > DELTA) {
    
      microphoneValue = value;
      return true;
  }
  return false;
}
