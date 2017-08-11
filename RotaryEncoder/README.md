# Enkoder
![Enkoder-przód](https://raw.githubusercontent.com/SeeedDocument/Grove-Encoder/master/img/Encoder2.jpg)
[![Enkoder-tył](https://raw.githubusercontent.com/SeeedDocument/Grove-Encoder/master/img/Encoder_back.jpg)](http://wiki.seeed.cc/Grove-Encoder/)



## Schemat podłączenia
Na co zwrócić uwagę?
- wykorzystuje piny **analogowe**

Enkoder | Arduino
---: | :---
SIGA | A2 *(lub inny pin analogowy)*
SIGB | A3 *(lub inny pin analogowy)*
VCC | VCC 
GND | GND

**Uwaga!** Jeśli podłączacie do innych pinów analogowych, musicie wprowadzić również zmianę w kodzie programu. 

## Obsłużone zdarzenia
Przy każdej zmianie wartości enkodera wywoływana jest funkcja `encoderValueChangedHandler(int value)` z aktualną wartością. Można tą wartość dowolnie wykorzystać. 

``` C++ 
void encoderValueChangedHandler(int value) {
  
  Serial.print("value "); Serial.println(value); 
  if (value > 150) {
    Serial.println("Go ahead and see what happens");
  }
}
```

#### Szkic, aby działać potrzebuje
Cały szkic do obsługi enkodera wymaga: 
- pliku `RotaryCounter.h` (w tym samym katalogu co szkic `RotaryEncoder.ino`), 
- zainstalowanych bibliotek
  * `Callback`
  * `Rotary Encoder` (autor: Matthias Hertel)
Obie biblioteki są dostępne przez Menedżera bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)

##### Menedżer bibliotek
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.