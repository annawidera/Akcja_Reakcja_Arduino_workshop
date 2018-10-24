#define IMMEDIATE 10.0
#define NEARBY 50.0

enum Position {
  immediate,
  nearby, 
  far
};


Position positionBasedOn(float currentDistance) {

  if (currentDistance > NEARBY ) {
    return far;
  } else if (currentDistance > IMMEDIATE) {
    return nearby;
  }
  return immediate;
}



void writePosition(Position pos) {
  
  switch (pos) {
    case immediate:  Serial.println("immediate"); break;
    case nearby:   Serial.println("nearby"); break;
    case far:  Serial.println("far"); break;
  }
}

