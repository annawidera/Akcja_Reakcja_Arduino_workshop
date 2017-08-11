#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define servosCount 1
const int servosId[servosCount] = { 0 };

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

int quater = (SERVOMAX - SERVOMIN)*0.25;
int low = SERVOMIN + quater;
int middle = SERVOMIN + 2*quater;
int high = SERVOMAX - quater;

void setup() {

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  Serial.begin(115200);
}


void loop() {

  int servoId = 0;

  for (int i = 0; i <= 180; i += 180/10) {
    Serial.print("go to "); Serial.println(i);
    setServoPosition(servoId, i); 
    delay(1000);
  }
}

void setServoPosition(int servoNmb, int angle) {

  int correctAngle = constrain(angle, 0, 180); 
  int pulseLenght = map(correctAngle, 0, 180, SERVOMIN, SERVOMAX); 
  pwm.setPWM(servoNmb, 0, pulseLenght); 
  
}

