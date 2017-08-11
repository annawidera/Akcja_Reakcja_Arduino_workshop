#include "StepperMotor.h"

StepperMotor motor(8,9,10,11);

void setup(){

  motor.setStepDuration(1);
  motor.setStepsPerRevolution(4096);
}


void loop(){
  
  motor.stepRevolutions(2, ccw);
  delay(500);
  motor.stepRevolutions(1, cw);
  delay(500);

  motor.step(356);
  delay(500);
  motor.step(-800);
  delay(500);
} 
