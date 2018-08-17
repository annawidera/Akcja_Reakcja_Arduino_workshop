#define VARIABLE_RESISTOR_PIN A4


void setup() {

  pinMode(VARIABLE_RESISTOR_PIN, INPUT); 
  Serial.begin(115200);
} 


void loop() {

  checkResistorValue(); 
  delay(500); 

//  if ( getResistorValue() > 450 ) { 
//    Serial.print("Value bigger than 450!");
//  }
} 


void checkResistorValue() { 

    int resistorValue = analogRead(VARIABLE_RESISTOR_PIN);
    Serial.print("resistor value: "); Serial.println(resistorValue);
}


int getResistorValue() { 

  return analogRead(VARIABLE_RESISTOR_PIN);
}

