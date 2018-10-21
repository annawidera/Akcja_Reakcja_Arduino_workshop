# Buzzer
Głośnik piezoelektryczny. Może być podłączony do pinu cyfrowego i dla stanu wysokiego po prostu buczy. Modulując sygnał podawany na wejście głośniczka można... próbować odgrywać proste melodie. 
[![Obrazek](https://statics3.seeedstudio.com/images/107020000%201.jpg)](http://wiki.seeed.cc/Grove-Buzzer/)

## Schemat podłączenia
Na co zwrócić uwagę?
- buzzer jest sterowany przez pin **~digital** (cyfrowy z ~, tzn. taki, który obsługuje PWM),
- PWM (ang. *pulse with modulation*) omawiam w części dotyczącej LED Bar'a i sterowania jasnością świecenia diod

Wyprowadzenia na płytce głośniczka są od spodu opisane. 
🔥🔥🔥 Uważajcie proszę przy podłączeniu zasilania (GND i VCC) - zamiana tych kabli powoduje usmażenie buzzera. 

| Buzzer | Arduino |
| ---: | :--- |
| SIG | 9 *(lub inny pin ~digital)* |
| NC | (ang. *not connected*), pozostaje niepodłączony |
| VCC | VCC (5V) |
| GND | GND |

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
oraz przykładowe piosenki (🏆 dla tego, kto odgadnie drugą piosenkę przed uruchomieniem kodu na Arduino! :))
``` C++ 
Song song1 = { 15, "ccggaagffeeddc ", { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }, 300}; 
Song song2 = { 20, "geefddceg geefddcec ", { 2, 2, 2, 2, 2, 2, 1, 1, 4, 1, 2, 2, 2, 2, 2, 2, 1, 1, 4, 4 }, 200 };
Song song3 = { 18, "cdefgabC Cbagfedc ", { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 }, 300}; 
```

## No to gramy!
Aktualnie odgrywana piosenka znajduje się w zmiennej: `Song currentSong` i jej początkowa wartość to `song3`. 
W pętli `loop` odgrywane są kolejne nuty piosenki: 
``` C++ 
playNote(currentSong.notes[note], currentSong.beats[note] * currentSong.tempo);
```

Następnie potrzebne jest opóźnienie: `delay(currentSong.tempo/2);` zachowujące rytm piosenki (kolejne nuty nie zostaną odegrane zbyt szybko). 

Na końcu pętli `loop` przechodzimy do kolejnej nuty piosenki, upewniając się jednocześnie, że piosenka się nie skończyła. Jeśli tak, to wracamy na początek: 
``` C++ 
note++; 

if (note >= currentSong.length) {
  note = 0; 
}
```
😎 Tu można pokusić się o eksperyment i spróbować odegrać piosenkę od końca do początku, zamiast zaczynać do pierwszej nuty.