# Cyfrowy czujnik zbliżeniowy, jasności, koloru i gestów

W jednym małym układzie (chipie) zaszyte są aż 4 czujniki. Możemy wykorzystywać je wszystkie na raz albo pojedynczo. 

![Obrazek](https://cdn-shop.adafruit.com/970x728/3595-00.jpg)

## Schemat podłączenia

![Schemat podłączenia](http://awidera.idl.pl/ArduinoDIYworkshopimages/apds9960_bb.png)

Wyprowadzenia SCL i SDA składają się na protokół komunikacyjny I2C (TWI *two wire interface*). Arduino potrafi komunikować się używając tego protokołu, ale koniecznie trzeba do tego wykorzystać wyprowadzenia **A4** i **A5**. 

## Inicjalizacja czujnika
Producent zapewnia bibliotekę dedykowaną temu czujnikowi, żeby praca z nim była łatwa i przyjemna. :) 

``` C++
#include <Adafruit_APDS9960.h>
Adafruit_APDS9960 gestureSensor;
```

Od teraz zmienna `gestureSensor` w kodzie reprezentuje fizyczny czujnik.

Potrzebujemy go zainicjalizować, jak większość czujników, `apds.begin()`. 
> Ta funkcja zwraca wartość typu `bool` (prawda / fałsz) sygnalizując czy inicjalizacja czujnika się powiodła (tzn. czy została ustanowiona komunikacja między Arduino, a czujnikiem). Warto sprawdzić tą zwracaną wartość i już na początku wypisać na Serial Monitorze komunikat o ewentualnych problemach (najpewniej trzeba ponownie przyjrzeć się kabelkom).

Następnie włączamy wymagane tryby pracy czujnika: 
``` C++ 
  // for gesture mode, proximity is required
  apds.enableProximity(true);
  apds.enableGesture(true);
```
i czujnik jest już gotowy do pracy. 

## Odczytywanie gestów

Do odczytania gestów służy funkcja: `apds.readGesture()`. Zwraca ona wartości typu `uint8_t` (liczba całkowita, 8bitowa). W dostarczonej przez Adafruit bibliotece są zdefiniowane stałe o obrazowych nazwach, które ukrywają wartości liczbowe typu 1, 2, 3 itd. i można je wykorzystać w operacjach porównania, jak na przykład: 
``` C++ 
if(gesture == APDS9960_DOWN) {
  Serial.println("v");
}
```
Pozostałe gesty to: `APDS9960_UP`, `APDS9960_LEFT` i `APDS9960_RIGHT`. 


#### Szkic, aby działać potrzebuje
Szkic do obsługi czujnika APDS9960 wymaga: 
- zainstalowanej biblioteki
  * `Adafruit_APDS9960`
Biblioteka jest dostępna przez Menedżera bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)


##### Menedżer bibliotek
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.


#### Linki
[Link do strony produktu na stronie producenta: Adafruit](https://www.adafruit.com/product/3595)

[Link do sekcji learn związanej z tym czujnikiem](https://learn.adafruit.com/adafruit-apds9960-breakout/overview)

