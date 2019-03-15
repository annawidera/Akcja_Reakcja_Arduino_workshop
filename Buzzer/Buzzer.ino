#include "Notes.h"
#include "MarioSong.h"
#include "PirattesSong.h"
#define SPEAKER_PIN 9

int note = 0;
int songLength = sizeof(pirattes)/sizeof(Sound);
float tempo = 1.5;


void setup() {
  
  pinMode(SPEAKER_PIN, OUTPUT);
  Serial.begin(115200);
}


void loop() {

  playNote(pirattes[note].note, pirattes[note].beat * tempo);
  
  note++; 
  Serial.println(songLength);
  if (note >= songLength) {
    note = 0; 
  }
}


void playNote(int note, int duration) {
  
  tone(SPEAKER_PIN, note, duration);  //tone(pin,frequency,duration)
  delay(duration);
}


