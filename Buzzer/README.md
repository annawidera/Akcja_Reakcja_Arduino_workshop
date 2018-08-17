# Buzzer
Głośnik piezoelektryczny. Może być podłączony do pinu cyfrowego i dla stanu wysokiego po prostu buczy. Modulując sygnał podawany na wejście głośniczka można... próbować odgrywać proste melodie. 
[![Obrazek](https://statics3.seeedstudio.com/images/107020000%201.jpg)](http://wiki.seeed.cc/Grove-Buzzer/)

## Schemat podłączenia
Na co zwrócić uwagę?
- sygnał przycisku wchodzi na pin **~digital** (cyfrowy z ~, tzn. taki, który obsługuje PWM),
- PWM (ang. *pulse with modulation*) omawiam przy okazji LED Bar'a i sterowania jasnością świecenia diod

Wyprowadzenia na płytce głośniczka są od spodu opisane. 

Buzzer | Arduino 
---: | :---
SIG | 9 *(lub inny pin ~digital)*
NC | (ang. *not connected*), pozostaje niepodłączony
VCC | VCC
GND | GND

## Tablica piosenek
Stworzyłam strukturę do opisywania poszczególnych piosenek: 
``` C++
struct Song {
  int length; 
  char notes[25];
  int beats[25];
  int tempo; 
};
```
oraz przykładową tablicę z piosenkami (🏆 dla tego, kto odgadnie drugą piosenkę przed uruchomieniem kodu na Arduino! :))
``` C++ 
#define songsCount 3
Song songs[songsCount] = { 
  { 15, "ccggaagffeeddc ", { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }, 300}, 
  { 20, "geefddceg geefddcec ", { 2, 2, 2, 2, 2, 2, 1, 1, 4, 1, 2, 2, 2, 2, 2, 2, 1, 1, 4, 4 }, 200 }, 
  { 18, "cdefgabC Cbagfedc ", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 }, 300}
}; 
```
## No to gramy!
Piosenki odgrywa funkcja: 
``` C++ 
void playSong(int songIndex)
```
do której podajemy indeks w tablicy `Song songs[]`. 

W przykładowym szkicu znajdziecie w głównej pętli programu zapętlony koncert ze wszystkich piosenek: 
``` C++ 
int song = 0;
void loop() {
  playSong(song);
  song++; 
  if (song >= songsCount ) {
    song = 0; 
  }
}
```