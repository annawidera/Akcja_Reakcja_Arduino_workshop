#define BARS_COUNT 10
const int ledPins[BARS_COUNT] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };



void setup() {
  
  Serial.begin(115200);
  for (int i=0; i < BARS_COUNT; i++) {
    pinMode(ledPins[i], OUTPUT); 
  }
}


int stepCounter = 0; 
bool condition = true;


void loop() {

   radialAnimation();
//   sequenceAnimation();

//  long int timeCondition = millis(); 
//  long int maxTime = 10000;
//  int bars = map(timeCondition, 0, maxTime, 0, BARS_COUNT);
//  turnOnBars(bars);
  
//  if (condition) {
//    
//      radialAnimationStep(stepCounter);
//    
//      stepCounter++; 
//      if (stepCounter > 9) {
//        stepCounter = 0;
//      }
//      delay(300);
//  }
}



void turnOn(int index) {
  digitalWrite(ledPins[index], HIGH); 
}

void turnOff(int index) {
  digitalWrite(ledPins[index], LOW); 
}



void turnOnBars(int bars) {

  turnOffAll();
  int constrainedBars = constrain(bars, 0, BARS_COUNT);
  
  for (int bar = 0; bar < constrainedBars; bar++) {
    
    turnOn(bar);
  }
}


void turnOffAll() {
  
  for (int bar = 0; bar < BARS_COUNT; bar++) {
    
    turnOff(bar);
  }
}





void sequenceAnimation() {

   for (int thisPin = 0; thisPin < BARS_COUNT; thisPin++) {
    
    turnOn(thisPin);
    delay(500);
    turnOff(thisPin);
  }
}


void radialAnimation() {

  int stepDelay = 100; 
  
  for (int i = 0; i < BARS_COUNT/2+1; i++) {
    
    turnOn(i); 
    turnOn(BARS_COUNT-1-i);
    delay(stepDelay); 
  }

  delay(2000); 

  for (int i = BARS_COUNT/2; i >= 0; i--) {
    
    turnOff(i); 
    turnOff(BARS_COUNT-1-i);
    delay(stepDelay); 
  }
  
  delay(1000);
}


void radialAnimationStep(int stepIndex) {

  if (stepIndex <= 4) {

    turnOn(stepIndex); 
    turnOn(BARS_COUNT-1-stepIndex);
    
  } else if (stepIndex <= 9) { 
    
    turnOff(BARS_COUNT-(stepIndex+1)); 
    turnOff(stepIndex);
  }
}



