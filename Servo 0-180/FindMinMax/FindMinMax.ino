#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)


void setup() {

  pwm.begin();
  pwm.setPWMFreq(60);

  Serial.begin(115200);
}


int servoId = 0;

void loop() {
  
  Serial.println("go to 0*");
  setServoPosition(servoId, 0); 
  delay(1500);
  
  Serial.println("go to 180*");
  setServoPosition(servoId, 180); 
  delay(1500);
}



void setServoPosition(int servoNmb, int angle) {

  int correctAngle = constrain(angle, 0, 180); 
  int pulseLenght = map(correctAngle, 0, 180, SERVOMIN, SERVOMAX); 
  pwm.setPWM(servoNmb, 0, pulseLenght); 
  
}
