#define SPEAKER_PIN 9

struct Song {
  int length; 
  char notes[25];
  int beats[25];
  int tempo; 
};

#define songsCount 3
Song songs[songsCount] = { 
  { 15, "ccggaagffeeddc ", { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }, 300}, 
  { 20, "geefddceg geefddcec ", { 2, 2, 2, 2, 2, 2, 1, 1, 4, 1, 2, 2, 2, 2, 2, 2, 1, 1, 4, 4 }, 200 }, 
  { 18, "cdefgabC Cbagfedc ", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 }, 300}
}; 

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
}


int song = 0;

void loop() {

  playSong(song);
 
  song++; 

  if (song >= songsCount ) {
    song = 0; 
  }
}


void playSong(int songIndex) {
  
  Song song = songs[songIndex];
  int length = song.length; 
  
  for (int note = 0; note < length; note++ ) {
    
     playNote(song.notes[note], song.beats[note] * song.tempo);
     delay(song.tempo/2);
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
