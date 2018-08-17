#include <Adafruit_NeoPixel.h>

#define LED_STRIP_PIN 6
#define NUM_LEDS 4
#define BRIGHTNESS 100
#define NUM_COLORS 4
// ta zmienna reprezentuje pasek diod LED na plytce stykowej.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_STRIP_PIN, NEO_RGB + NEO_KHZ400);


// tablica kolorow, wykorzystywana w funkcji: colorsFromArray()
uint32_t colors[NUM_COLORS] = {
  strip.Color(113, 149, 206), 
  strip.Color(206, 113, 169), 
  strip.Color(113, 206, 158), 
  strip.Color(206, 186, 113)
};

void setup() {

  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {

  colorsFromArray(500);
  delay(1000); 
  rainbow(300); 
  delay(1000);
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


void colorsFromArray(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<NUM_COLORS; j++) {
    
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, colors[j]);      
//      strip.show();
//      delay(wait);
    }
    // zakomentuj poniższe dwie linijki i odkomentuj identyczne dwie powyżej, 
    // jaka jest różnica w świeceniu diod? Dlaczego?
    strip.show();
    delay(wait);
  }
}


// Function from Adafruit_Neopixel examples
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}
