# Ultradźwiękowy czujnik odlegości
[![HC-SR04 zdjęcie](https://www.robotshop.com/media/catalog/product/cache/image/380x380/9df78eab33525d08d6e5fb8d27136e95/h/c/hc-sr04-ultrasonic-range-finder-2.png)](https://botland.com.pl/ultradzwiekowe-czujniki-odleglosci/1420-ultradzwiekowy-czujnik-odleglosci-hc-sr04-2-200cm.html)

Sposób działania czujników ultradźwiękowych dobrze obrazuje poniższy schemat: 
[![Zasada działania](https://www.maxbotix.com/wp-content/uploads/2018/02/Basic-Sonar-Illustration-1024x576.png)](https://www.maxbotix.com/articles/how-ultrasonic-sensors-work.htm)


## Schemat podłączenia
Na co zwrócić uwagę?
- podpisy wyprowadzeń znajdują się z obu stron płytki, 
- `Trig` i `Echo` podłączamy do pinów cyfrwych (**digital**), pamiętając o tym, że piny **0** i **1** są wykorzystywane do komunikacji Arduino ⇆ Serial Monitor. 

HC-SR04 | Arduino
---: | :---
`VCC` | `VCC (5V)`
`GND` | `GND`
`TRIG` | pin cyfrowy (w przykładowym kodzie: 2)
`ECHO` | pin cyfrowy (w przykładowym kodzie: 3)

## Biblioteka do obsługi czujnika
Do obsługi czujnika wykorzystamy bibliotekę `HCSR04 ultrasonic sensor`, dostępną w menadżerze bibliotek. Na Githubie znajdziecie jej [dokumentację](https://github.com/gamgine/HCSR04-ultrasonic-sensor-lib). 

## Pomiar odległości
Czujnik w kodzie będzie reprezentowany przez zmienną typu `HCSR04` o nazwie `distanceSensor`. Poniższy fragment inicjalizuje czujnik podłączony do Arduino na pinach `2` i `3`. 
``` C++
#include <HCSR04.h>

#define TRIG_PIN 2
#define ECHO_PIN 3

HCSR04 distanceSensor(TRIG_PIN, ECHO_PIN);
```
Odczyt odległości od przeszkody (wyrażonej w centrymetrach, za pomocą liczby z częścią ułamkową) realizuje ten fragment: 
``` C++
float currentDistance = distanceSensor.dist();
```


## Zakresy odległości
Dla Waszej wygody dodałam mechanizm do grupowania zakresów odległości w większe klastry, pozwalając ocenić czy przeszkoda jest tuż-tuż, w pobliżu lub daleko. 
Do tego celu powstał nowy typ zmiennej: `Position`, który może przyjąć jedną z 3 wartości: `immediate`, `nearby` lub `far`. Jej deklarację znajdziecie w pliku `Position.h`. 

Zdefiniowałam też przedziały odległości kwalifikujące się jako `immediate`, `nearby` i `far`, możecie je dowolnie modyfikować, aby dostosować kod do Waszego pomysłu: 
``` C++
#define IMMEDIATE 10.0
#define NEARBY 50.0
```
Odległość (cm) | `Position`
---: | :---
0 - 10.0| `immediate`
10.0 - 50.0 | `nearby`
> 50.0 | `far`

Przeliczenia aktualnej odległości w cm na `Position` dokonuje funkcja `Position positionBasedOn(float currentDistance)`. Jeśli chcecie wypisać w czytelny sposób wynik tej konwersji w `Serial Monitorze` możecie użyć fukcji: `writePosition(Position pos)`. Wykorzystanie obu tych fukcji znajdziecie w przykładowym kodzie, w zakomentowanych liniach.

#### Szkic, aby działać potrzebuje
Cały szkic do obsługi ultradźwiękowego czujnika odległości wymaga: 
- pliku `Position.h` (w tym samym katalogu co szkic `DistanceUltrasonicSensor.ino`), 
- biblioteki: `HCSR04 ultrasonic sensor` (dostępnej w menadżerze bibliotek)

##### Menedżer bibliotek
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.