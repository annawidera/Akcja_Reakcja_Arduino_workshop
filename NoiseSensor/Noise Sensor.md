# Detektor dźwięków
[![Mikrofon-zdjęcie](https://cdn.sparkfun.com//assets/parts/9/3/3/0/12642-01.jpg)](https://www.sparkfun.com/products/12642)

## Schemat podłączenia
Na co zwrócić uwagę?
- sygnał przycisku wchodzi na pin **analogowy** (w przykładowym kodzie: A1), 
- kabelki można wpiąć bezpośrednio do slotów na Arduino

Sound Detector | Arduino
---: | :---
VCC | VCC
GND | GND
ENVELOPE | pin analogowy (w przykładowym kodzie: A1)
pozostałe | niepodłączone
[![Schemat-podlaczenia](https://cdn.sparkfun.com/assets/learn_tutorials/4/9/2/Exp_16_Sound_Detector_bb_2.png)](https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-the-arduino-101genuino-101-board/experiment-15-using-the-sound-detector-board)

[Kompletny hook-up-guide na stronie Sparkfun](https://learn.sparkfun.com/tutorials/sound-detector-hookup-guide)

## Obsłużone zdarzenia
Mikrofon zbiera dźwięki z otoczenia, które przetwarza układ na płytce "Sound detectora" i udostępnia Arduino. Arduino w głównej pętli programu odczytuje ten sygnał na pinie analogowym (stąd wartości są z zakresu 0...1024) i w odpowiedzi na niego uruchamia poniższe zdarzenia. 
**Uwaga**: odczytywane wartości nie są wyrażone w decybelach. Odpowiadają zmianom napięcia w zakresie 0...5V. Można je porównywać ze sobą uznając, że np. 100 to znacznie ciszej niż 1000. 
#### Zmiana natężenia dźwięków otoczenia
Jeśli natężenie dźwięków zmieniło się od ostatniego pomiaru o wartość większą niż ustalona ```DELTA``` wywoływane jest zdarzenie (z aktualną wartością natężenia dźwięku):
``` C++
void noiseValueHandler(int value)
```
Wartość delty można zmienić w pliku `NoiseState.h`, podmieniając wartość `3` w tej linijce: 
` #define DELTA 3`
#### Zmiana poziomu hałasu
Ustaliłam 5 progów dźwięku określonych jako `NoiseState`. Zmienna tego typu może mieć następujące wartości: `mute`, `quietly`, `noisly`, `superLoudly`, `brainInPieces`. 
W pliku `NoiseState.h` są zdefiniowane konkretne wartości progów. To są wartości przykładowe, warto je dopasować do panującego na miejscu natężenia dźwięków. 
``` C++
#define MUTE 15
#define QUIETLY 40
#define NOISLY 200
#define SUPER_LOUDLY 400
```
Jeśli z wartości określającej aktualne natężenie dźwięku wynika inny niż poprzednio próg hałasu, wywoływane jest zdarzenie: 
``` C++ 
void noiseStateValueHandler(Noise noise) {
  Serial.print("state "); writeState(noise.state); 
  Serial.print("   value: "); Serial.println(noise.microphoneValue);
}
```
#### Detekcja krzyku
Kiedy poziom hałasu osiągnie bądź przekroczy próg `superLoudly`, odpala się zdarzenie: 
``` C++ 
void screamHandler(int value) {
  Serial.println("SCREEEEAAAAAAAM");
}
```
**Uwaga**: Ta funkcja wywoływana jest tak długo, jak długo nie ustanie krzyk (bardzo głośny dźwięk), a nie tylko jednorazowo przy zmianie. 
#### Detekcja najgłośniejszego dźwięku (dotąd)
Program cały czas zapamiętuje nagłośniejszy (jak dotąd) zasłyszany dźwięk. Jeśli jakiś hałas go przebije, uruchamia zdarzenie (aktualizując jednocześnie wartość): 
``` C++ 
void loudestEverHandler(int value) 
```
Po jakimś czasie nie tak łatwo wywołać to zdarzenie... 😎
#### Szkic, aby działać potrzebuje
Cały szkic do obsługi mikrofonu wymaga: 
- pliku `NoiseState.h` (w tym samym katalogu co szkic `NoiseSensor.ino`), 
- zainstalowanej biblioteki
  * `Callback`
Biblioteka jest dostępna przez Menedżera bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)


##### Menedżer bibliotek
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.

##### Linki
[producent - sparkfun - strona produktu](https://www.sparkfun.com/products/12642)