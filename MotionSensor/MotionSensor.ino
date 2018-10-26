#define MOTION_SENSOR_PIN 2
 
void setup() {

  pinMode(MOTION_SENSOR_PIN, INPUT);
  Serial.begin(115200);
}


bool currentMotionStatus = false; 

void loop(){

  static bool isMotion = false;

  currentMotionStatus = digitalRead(MOTION_SENSOR_PIN);

  if (currentMotionStatus != isMotion) {
      motionStatusChanged(currentMotionStatus);
      isMotion = currentMotionStatus; 
  }
}


void motionStatusChanged(bool isMotion) { 

  switch (isMotion) {
    case true: Serial.println("Motion detected"); break; 
    case false: Serial.println("Motion disappeared"); break;
  }
}

