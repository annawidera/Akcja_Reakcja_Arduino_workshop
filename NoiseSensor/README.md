# Detektor dźwięków
[![Mikrofon-zdjęcie](https://cdn.sparkfun.com//assets/parts/9/3/3/0/12642-01.jpg)](https://www.sparkfun.com/products/12642)

## Schemat podłączenia
Na co zwrócić uwagę?
- sygnał `ENVELOPE` wchodzi na pin **analogowy** (w przykładowym kodzie: A1), 
- kabelki można wpiąć bezpośrednio do slotów na Arduino

Sound Detector | Arduino
---: | :---
VCC | VCC (5V)
GND | GND
ENVELOPE | pin analogowy (w przykładowym kodzie: A1)
pozostałe | niepodłączone

![Schemat-podlaczenia](http://www.awidera.idl.pl/ArduinoDIYworkshopimages/sound_detector.png)

[Kompletny hook-up-guide na stronie Sparkfun](https://learn.sparkfun.com/tutorials/sound-detector-hookup-guide)

## Obsłużone zdarzenia
Mikrofon zbiera dźwięki z otoczenia, które przetwarza układ na płytce "Sound detectora" i udostępnia Arduino. Arduino w głównej pętli programu odczytuje ten sygnał na pinie analogowym (stąd wartości są z zakresu 0...1024).
**Uwaga**: odczytywane wartości nie są wyrażone w decybelach. Odpowiadają zmianom napięcia w zakresie 0...5V. Można je porównywać ze sobą uznając, że np. 100 to znacznie ciszej niż 1000. 
#### Zmiana natężenia dźwięków otoczenia
Wartości odczytywane z czujnika mogą nieco fluktuować (zmieniać się np. +/- 1), bez specjalnej zmiany głośności otoczenia. Żeby odfiltrować takie nieznaczne zmiany, możemy skorzystać z funkcji: 
``` C++
  if ( checkIfNoiseChanged(microphoneValue) == true ) {
    ...
  }
```
Domyślnie zmiany o +/-3 będą ignorowane. Wartość 3 jest zdefiniowana jako `DELTA` w pliku `NoiseState.h`: 

`#define DELTA 3`. 
czułość | `DELTA`
---: | :---
⬆️  | ⬇️
⬇️ | ⬆️ 

#### Zmiana poziomu hałasu
_dalej jesteśmy w pliku `NoiseState.h`_

Ustaliłam 5 progów dźwięku określonych jako `NoiseState`. Zmienna tego typu może mieć następujące wartości: `mute`, `quietly`, `noisly`, `superLoudly`, `brainInPieces`. 
W pliku `NoiseState.h` są zdefiniowane konkretne wartości progów. To są wartości przykładowe, warto je dopasować do panującego na miejscu natężenia dźwięków. 
``` C++
#define MUTE 10
#define QUIETLY 50
#define NOISLY 300
#define SUPER_LOUDLY 600
```

Dla Waszej wygody jest dostępna funkcja: 
``` C++
NoiseState noiseStateBasedOn(int value) {

  if (value > SUPER_LOUDLY ) {
    return brainInPieces;
  } else if (value > NOISLY) {
    return superLoudly;
  } else if (value > QUIETLY) {
    return noisly;
  } else if (value > MUTE) {
    return quietly;
  }
  return mute;
}
```
która porównuje wartość przekazaną do funkcji (wartość odczytana z czujnika), z podanymi programi i zwraca aktualny poziom hałasu (`NoiseState`).

Otrzymany `NoiseState` możecie na początek wypisać na Serial Monitorze. Są do tego dwie funkcje. Pierwsza wypisuje nazwę stanu, druga rysuje coś w rodzaju obróconego o 90* equalizera. 
``` C++
void writeState(NoiseState state)
```
``` C++
void writeEqualizer(NoiseState state) 
```

#### Szkic, aby działać potrzebuje
Cały szkic do obsługi mikrofonu wymaga: 
- pliku `NoiseState.h` (w tym samym katalogu co szkic `NoiseSensor.ino`), 

##### Linki
[producent - sparkfun - strona produktu](https://www.sparkfun.com/products/12642)