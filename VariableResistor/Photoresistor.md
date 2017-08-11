# Fotorezystor
Rezystor, którego rezystancja zmienia się w zależności od natężenia światła. 🕯️🔦💡📱
![Fotorezystor](https://www.piekarz.pl/pl/img/offer/0/9/f_09093.jpg)

## Schemat podłączenia
Na co zwrócić uwagę?
- sygnał przycisku wchodzi na pin **analogowy**, 
- podpinany przez tzw. dzielnik napięcia, 
- rezystor o stałej wartości to 10kΩ

![Schemat-podlaczenia](http://3.bp.blogspot.com/-dAh3w6s2xtU/VbTIDpg4UII/AAAAAAAAABI/jpVwSAE0PDQ/s1600/%255B3%255D%2BPod%25C5%2582%25C4%2585czenie%2Bfotodiody.jpg)

## Obsłużone zdarzenia
Stworzyłam jeden ogólny szkic do wykorzystania przy pracy ze wszystkimi czujnikami będącymi rezystorami o zmiennej rezystancji, która waha się w odpowiedzi na określone czynniki. 
Ten szkic to `VariableResistor.ino`. 

Rezystory o zmiennej rezystancji podłączamy do Arduino przez dzielnik rezystancyjny do wejścia **analogowego**. Wykorzystując funkcję `analogRead(PIN)`, odczytujemy wartość napięcia, odkładającego się na aktualnej rezystancji. 
![Variable resistor events](http://awidera.idl.pl/ArduinoDIYworkshopimages/variableResistorEvents.PNG)
Mam nadzieję, że ten wykres będzie służył pomocą przy analizie kiedy jaki eventHandler jest wywoływany :) 

#### Zmiana wartości
Każda zmiana odczytywanej wartości o więcej niż ustalone `DELTA` powoduje wywołanie zdarzenia: 
``` C++
void resistorValueHandler(int value)
```
Z aktualnie odczytaną wartością w zmiennej `value`. 
Wartość delty można zmienić w pliku `VariableResistorState.h`, podmieniając wartość `3` w tej linijce: 
` #define DELTA 3`


#### Przekroczenie progu
Ustaliłam 5 progów określonych jako `ResistorThreshold`. Zmienna tego typu może mieć następujące wartości: `first`, `second`, `third`, `fourth`, `fifth`. 😁
W pliku `VariableResistorState.h` są zdefiniowane wartości graniczne dla każdego stanu (`first` do 200, `second` do 400 itd.) W zależności od rodzaju rezystora warto przyjrzeć się czy te wartości na pewno mają sens. :) 
``` C++
#define FIRST_THRESHOLD 200
#define SECOND_THRESHOLD 400
#define THIRD_THRESHOLD 550
#define FOURTH_THRESHOLD 700
```
Przekroczenie któregoś z progów w górę bądź w dół odpala zdarzenie: 
``` C++
void resistorThresholdChangedHandler(VariableResistor resistor) {
  Serial.print("threshold "); writeState(resistor.threshold); 
  Serial.print("   value: "); Serial.println(resistor.value);
}
```
Mmy tu dostęp do aktualnego progu i "gołej" wartości odczytanej na pinie analogowym. 

#### Detekcja skrajnych (wysokich i niskich) progów
Kiedy odczytywane wartości zwierają się w dwóch skrajnych dolnych lub górnych progach wywoływana jest jedna z metod: 
``` C++ 
void lowHandler(int value) 
void highHandler(int value) 
```

**Uwaga**: Ta funkcja wywoływana jest tak długo, jak długo wartości utrzymują się w tym progu, a nie tylko jednorazowo przy zmianie. 

#### Detekcja najwyższej (jak dotąd) wartości
Program cały czas zapamiętuje najwyższą odczytaną wartość (jak dotąd). Jeśli jakiś pomiar go przebije, uruchamia zdarzenie (aktualizując jednocześnie wartość): 
``` C++ 
void highestEverHandler(int value)
```
Po jakimś czasie nie tak łatwo wywołać to zdarzenie... 😎


#### Szkic, aby działać potrzebuje
Cały szkic do obsługi przycisków wymaga: 
- pliku `VariableResistorState.h` (w tym samym katalogu co szkic `VariableResistor.ino`), 
- zainstalowanej biblioteki `Callback`
Biblioteka jest dostępna w Menedżerze bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)


## Schemat elektryczny
Być może taki schemat okaże się wygodniejszy. 
[![Schemat-elektryczny](https://ctheds.files.wordpress.com/2007/10/analogin_variableresistor.jpg)](https://www.arduino.cc/en/Tutorial/Button)

##### Menedżer bibliotek
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.