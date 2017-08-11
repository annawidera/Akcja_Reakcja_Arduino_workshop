# Rezystor wrażliwy na nacisk
Rezystor, którego rezystancja zmienia się w odpowiedzi na przyłożoną do jego powierzchni siłę nacisku. 
[![Force resistor-zdjęcie](http://www.continentalee.com.sg/content/images/thumbs/0000779_force-sensitive-resistor-force-sensor-fsr402_390.jpeg)](https://botland.com.pl/czujniki-nacisku/753-czujnik-sily-nacisku-okragly-13mm-06-.html?search_query=force&results=15)

## Schemat podłączenia
Na co zwrócić uwagę?
- sygnał przycisku wchodzi na pin **analogowy** (w przykładowym kodzie: A4)
- rezystor na dzielniku napięcia: 10kΩ, 

[![Schemat-podlaczenia](http://arduinolearning.com/wp-content/uploads/2016/03/arduino-and-force-sensor_bb-1024x701.png)](http://arduinolearning.com/code/force-sensitive-resistor-example.php)

## Obsłużone zdarzenia
Force-resistor zmienia swoją rezystancję w odpowiedzi na nacisk. Podłączony do Arduino przez dzielnik rezystancyjny zmienia w ten sposób wartość napięcia mierzonego na pinie Arduino → wartość odczytaną przez funkcję `analogRead(A4)`.

#### Zmiana wartości siły nacisku
Każda zmiana siły nacisku o wartość większą niż ustalone `DELTA` powoduje wywołanie zdarzenia: 
``` C++
void forceValueHandler(int value) {
  Serial.print("force value "); Serial.println(value); 
}
```
Wartość delty można zmienić w pliku `ForceState.h`, podmieniając wartość `3` w tej linijce: 
` #define DELTA 3`

#### Zmiana poziomu siły nacisku
Ustaliłam 5 progów siły określonych jako `ForceState`. Zmienna tego typu może mieć następujące wartości: `untouched`, `light`, `medium`, `strong`, `superStrong`. 
W pliku `ForceState.h` są zdefiniowane wartości graniczne dla każdego stanu (`untouched` do 10, `light` do 100 itd.)
``` C++
#define UNTOUCHED 10
#define LIGHT 100
#define MEDIUM 300
#define STRONG 600
```
Przekroczenie któregoś z progów w górę bądź w dół odpala zdarzenie: 
``` C++
void forceStateValueHandler(Force force) {
  Serial.print("state "); writeState(force.state); 
  Serial.print("   value: "); Serial.println(force.value);
}
```

#### Detekcja mocnego uścisku
Kiedy poziom nacisku osiągnie bądź przekroczy próg `strong`, wywołane zostanie zdarzenie:
``` C++ 
void clampHandler(int value) {
  Serial.println("squeeeeeeeeeze");
}
```
**Uwaga**: Ta funkcja wywoływana jest tak długo, jak długo nie ustanie silny uścisk, a nie tylko jednorazowo przy zmianie. 

#### Detekcja najsilniejszego uścisku (dotąd)
Program cały czas zapamiętuje najsilniejszy (jak dotąd) uścisk. Jeśli jakiś nacisk go przebije, uruchamia zdarzenie (aktualizując jednocześnie wartość): 
``` C++ 
void hardestEverHandler(int value) {
  Serial.print("Heeeey! It is wayyy harder than before!!"); Serial.println(value);
}
```
Po jakimś czasie nie tak łatwo wywołać to zdarzenie... 😎

#### Szkic, aby działać potrzebuje
Cały szkic do obsługi Siła-Rezystora wymaga: 
- pliku `ForceState.h` (w tym samym katalogu co szkic `ForceSensor.ino`), 
- zainstalowanej biblioteki
  * `Callback`
Biblioteka jest dostępna przez Menedżera bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)

##### Menedżer bibliotek
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.

## Schemat elektryczny połączeń
Być może taki schemat okaże się wygodniejszy. 
[![Schemat-elektryczny](http://arduinolearning.com/wp-content/uploads/2016/03/arduino-and-force-sensor_schem.png)](http://arduinolearning.com/code/force-sensitive-resistor-example.php)
