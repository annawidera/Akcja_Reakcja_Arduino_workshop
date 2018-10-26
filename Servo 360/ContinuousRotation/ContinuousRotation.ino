#include <Servo.h>

#define SERVO_PIN 9
#define STOP 90
#define SLOWLY 15
#define MEDIUM_SPEED 30
#define FAST 90

enum Direction { 
  forward, 
  backward
};

enum Speed { 
  slowly, 
  mediumSpeed, 
  fast
};

Servo servo; 


void setup() {
  
  Serial.begin(115200);
  servo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
}


void loop() {

  move(forward, slowly); 
  delay(2000);
  move(backward, slowly); 
  delay(2000);

  move(forward, mediumSpeed); 
  delay(2000);
  move(backward, mediumSpeed); 
  delay(2000);

  move(forward, fast); 
  delay(2000);
  move(backward, fast); 
  delay(2000);
}


int pos = 0;

void move(Direction direction, Speed speed) { 

  pos = STOP + getDirectionSign(direction) * getSpeedValue(speed);
    // dla testu, wypisanie kierunku, prędkości i pozycji można usunąć.
      write(direction); 
      write(speed); 
      Serial.println(pos);
    // ----------
  servo.write(pos);
}


int getSpeedValue(Speed speed) { 
  
  switch (speed) { 
    case slowly: return SLOWLY;
    case mediumSpeed: return MEDIUM_SPEED;
    case fast: return FAST;
  }
  return SLOWLY; // default, just in case
}


int getDirectionSign(Direction direction) { 
  
  switch (direction) { 
    case forward: return 1;
    case backward: return -1;
  }
  return 1; // default, just in case
}


void write(Direction direction) { 

  switch (direction) { 
    case forward: Serial.println("forward"); break;
    case backward: Serial.println("backward"); break;
  }
}


void write(Speed speed) { 

  switch (speed) { 
    case slowly: Serial.println("slowly"); break;
    case mediumSpeed: Serial.println("mediumSpeed"); break;
    case fast: Serial.println("fast"); break;
  }
}

