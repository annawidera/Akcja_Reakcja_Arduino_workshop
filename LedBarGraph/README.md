# LED bar graph
![Obrazek](http://www.hobbytronics.co.uk/image/cache/data/misc/led-bargraph-10-500x500.jpg)


## 🔌 Schemat podłączenia
Na co zwrócić uwagę?
- od strony napisu na obudowie idą kabelki do Arduino 😉
- sygnały sterujące z Arduino wychodzą z pinów **digital** (cyfrowych), 
- użyte rezystory to **220Ω**, 
- piny **0** i **1** są wykorzystywane do komunikacji Arduino z komputerem (`Serial.print("Hello");`) i wykorzystanie ich do świecenia diodami uniemożliwia komunikację.
![Schemat-podlaczenia](http://awidera.idl.pl/schema_bb.png)

## 🖐️ Obsługa
### Konfiguracja pinów Arduino
Piny Arduino, które będą sterowały świeceniem diod muszą być ustawione jako wyjścia. 
Na górze pliku zadeklarowana jest tablica, w której należy uzupełnić numery pinów z podłączonymi diodami: 
``` C++ 
#define BARS_COUNT 10
const int ledPins[BARS_COUNT] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
```
Następnie w funkcji `setup()` w pętli wszystkie piny ustawione są jako `OUTPUT`: 
``` C++
for (int i=0; i < BARS_COUNT; i++) {
  pinMode(ledPins[i], OUTPUT); 
}
```


#### Ustawienie stanu progress baru
Aby zaświecić np. 4 paski z 10, należy wywołać funkcję
``` C++ 
turnOnBars(4); 
```
Aby zgasić wszystkie diody: 
``` C++ 
turnOffAll();
```

#### Zaświecenie wybranej diody
Aby zaświecić (tylko nie zapalić! ;)) wybraną diodę należy wywołać funkcję, podając jej indeks w tablicy (pamiętając, że liczenie indeksów zaczyna się od 0): 
``` C++ 
turnOn(6);
```
Aby następnie zgasić wybraną diodę, analogicznie: 
``` C++ 
turnOff(6);
```

#### 🎬 Animacje
Włączając i wyłączając diody w odpowiednich sekwencjach można uzyskać efekt animacji. Przykładowe animacje można zobaczyć, wywołując funkcje: 
``` C++ 
radialAnimation();
sequenceAnimation();
```
Powyższe funkcje odtworzą animację w całości, tj. od pierwszej do ostatniej klatki i dopiero wtedy program "poleci" dalej. Aby sterować kolejnymi krokami animacji, potrzebna jest funkcja, która przy każdym wywołaniu będzie odtwarzała tylko jedną jej klatkę. Przykład takiej funkcji: 
``` C++ 
void radialAnimationStep(int stepIndex)
```
gdzie argumentem funkcji jest numer kolejnej klatki animacji. 
Można jej użyć np. w taki sposób
``` C++
  if (_tu_jakis_warunek_) {
    
      radialAnimationStep(stepCounter);
    
      stepCounter++; 
      if (stepCounter > _liczba_klatek_animacji) {
        stepCounter = 0;
      }
  }
```
gdzie:
- `_tu_jakis_warunek_` to może być sprawdzenie czy przycisk jest wciśnięty, czy ktoś cały czas krzyczy (Sound detector) albo czy wciąż temperatura jest przekroczona. 
Animacja będzie się odtwarzała płynnie (kolejne klatki animacji) tak długo, jak długo spełniony będzie `_tu_jakis_warunek_`. Jeśli przestanie być prawdziwy - animacja ustanie. 

- `stepCounter` nie powinien przekroczyć `_liczba_klatek_animacji`, ale to zależy od przygotowanej sekwencji. :) 

## 💡 Sterowanie jasnością świecenia
Przekopując się prez przygotowane przeze mnie funkcje dotrzecie w końcu do sedna, czyli do wywołania funkcji, która faktycznie zaświeca diodę (tu: podpiętą na pinie cyfrowym 5): 
``` C++ 
digitalWrite(5, HIGH); 
```
W ten sposób na pinie Arduino wystawiamy 5V i dioda świeci z pełną możliwą (ma na nią wpływ także wybrany rezystor) jasnością. 
Diody mogą również świecić słabiej, z ułamkiem tej maksymalnej jasności. Są piny cyfrowe w Arduino (oznaczone tyldą: ~3, ~5, ~6 itd.), które obsługują tryb tzw. PWM (ang *pulse with modulation*). 
![PWM](https://qph.ec.quoracdn.net/main-qimg-e2d124568f8486e50c681eab5e6ed69a)
Wykres na samym dole, *100% modulation* to właśnie efekt wywołania funkcji `digitalWrite(5, HIGH)`. 
Korzystając z funkcji 
``` C++
analogWrite(5, 128)
```
uzyskamy świecenie diody na pinie 5 z połową maksymalnej jasności. Tam, gdzie w `digitalWrite` było `HIGH` (lub `LOW`), w `analogWrite` podajemy liczbę z zakresu `0...255` (ona określa wypełnienie widoczne na wykresie). 
digitalWrite | analogWrite
---: | :---
LOW | 0
-| 1...254
HIGH | 255

##### Stopniowana moc świecenia diody bardzo fajnie łączy się z wszelkiego rodzaju potencjometrami, rezystorami wrażliwym na nacisk itp. 

