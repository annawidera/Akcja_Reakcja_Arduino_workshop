#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define servosCount 1
const int servosIds[servosCount] = { 0 };
const int servosMin[servosCount] = { 150 };
const int servosMax[servosCount] = { 600 };

// Dla 3 serwomechanizmów deklaracje wyglądają tak: 
//#define servosCount 3
//const int servosIds[servosCount] = { 0, 1, 2 };
//const int servosMin[servosCount] = { 150, 150, 150 };
//const int servosMax[servosCount] = { 600, 600, 550 };

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void setup() {

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  Serial.begin(115200);
}


int servoIndex = 0;

void loop() {

  for (int i = 0; i <= 180; i += 180/10) {
    
    Serial.print("go to "); Serial.println(i);
    setServoPosition(servoIndex, i); 
    delay(500);
  }

  servoIndex++; 
  if (servoIndex >= servosCount) { 
    servoIndex = 0; 
  }
}


void setServoPosition(int servoIndex, int angle) {

  int correctAngle = constrain(angle, 0, 180); 
  int pulseLenght = map(correctAngle, 0, 180, servosMin[servoIndex], servosMax[servoIndex]); 
  pwm.setPWM(servosIds[servoIndex], 0, pulseLenght); 
  
}

