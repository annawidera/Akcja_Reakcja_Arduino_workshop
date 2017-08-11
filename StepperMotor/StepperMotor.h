#ifndef Stepper_h
#define Stepper_h

enum StepperDirection {
  cw,
  ccw
};

class StepperMotor {
  public:
    StepperMotor(int In1, int In2, int In3, int In4);    // Constructor that will set the inputs
    void setStepDuration(int duration);    // Function used to set the step duration in ms
    void setStepsPerRevolution(int steps);
    void step(int noOfSteps);    // Step a certain number of steps. + for one way and - for the other
    void stepRevolutions(int count, StepperDirection dir);

    int stepsPerRevolution;
    int duration;    // Step duration in ms
    int inputPins[4];    // The input pin numbers
};

#endif
