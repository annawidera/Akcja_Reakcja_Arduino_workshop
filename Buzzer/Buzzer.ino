#define SPEAKER_PIN 9

struct Song {
  int length; 
  char notes[25];
  int beats[25];
  int tempo; 
};

Song song1 = { 15, "ccggaagffeeddc ", { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }, 300}; 
Song song2 = { 20, "geefddceg geefddcec ", { 2, 2, 2, 2, 2, 2, 1, 1, 4, 1, 2, 2, 2, 2, 2, 2, 1, 1, 4, 4 }, 200 };
Song song3 = { 18, "cdefgabC Cbagfedc ", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 }, 300};


void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
}

int note = 0;
Song currentSong = song3;

void loop() {

  playNote(currentSong.notes[note], currentSong.beats[note] * currentSong.tempo);
  delay(currentSong.tempo/2);
 
  note++; 

  if (note >= currentSong.length) {
    note = 0; 
  }
}


// Those functions are  from here: https://www.arduino.cc/en/Tutorial/Melody

void playNote(char note, int duration) {
  
  if (note == ' ') {
    delay(duration); 
    return;
  }
  
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void playTone(int tone, int duration) {
  
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(SPEAKER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(SPEAKER_PIN, LOW);
    delayMicroseconds(tone);
  }
}
