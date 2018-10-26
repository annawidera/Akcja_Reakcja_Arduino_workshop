# Serwomechanizm
[![Redox S90](http://mmhobby.pl/images/min/product_mid/326.JPG)](https://botland.com.pl/serwa-redox/1684-serwo-redox-s90-micro.html)
[![SG5010](http://www.robotistan.com/tower-pro-sg-5010-rc-servo-motor-3471-15-B.jpg)](https://botland.com.pl/serwa-typu-standard/485-serwo-tower-pro-sg-5010.html)
[![Sterownik](https://cdn-shop.adafruit.com/970x728/815-04.jpg)](https://www.adafruit.com/product/815)

# Serwomechanizm obrotowy 360*
[![SG5010](https://nettigo.pl/system/images/1979/original.jpg?1483454715)](https://nettigo.pl/products/serwomechanizm-obrotowy-360-stopni)



## Schemat podłączenia serwomechanizmów 0-180*
Na co zwrócić uwagę?
- Arduino komunikuje się ze sterownikiem serwomechanizmów po protokole **I²C**, którego linie są wyprowadzone na pinach **A4 (SDA)** i **A5 (SCL)** Arduino. 
- serwomechanizmy zużywają znacząco więcej prądu niż oferują piny Arduino, dlatego do ich działania potrzebne jest zewnętrzne źródło zasilania podpinane bezpośrednio do sterownika (na płytce sterownika jest to niebieskie gniazdo do zakręcania śrubkami), 
- **Ważne**: koniecznie trzeba zewrzeć masy (GND) Arduino i zasilacza serwomechanizmów (czarny kabel czarnej wtyczki) 

![Schemat-podlaczenia](http://www.awidera.idl.pl/ArduinoDIYworkshopimages/servo_PCA9685.png)

### Serwo do sterownika
#### SG-5010
Serwo | Sterownik 
---: | :---
brązowy | GND
czerwony | V+
pomarańczowy | PWM

## Schemat podłączenia serwomechanizmów obrotowych
Na co zwrócić uwagę?
- Serwomechanizm podłączamy bezpośrednio do Arduino, ale ze względu na pobór mocy lepiej jest zasilić je korzystając z zewnętrznego zasilacza, 
- ważne: masy (GND) Arduino i zasilacza muszą być zwarte, najlepiej na płytce stykowej. 

![Schemat-podlaczenia](http://www.awidera.idl.pl/ArduinoDIYworkshopimages/servo_continuous_rotation.png)


## Poruszanie serwomechanizmu (0-180*)
Serwomechanizm może się poruszać w zakresie 0* - 180*. 

### Kalibracja (0-180*)
Najpierw należy znaleźć skrajne wartości długości pulsu dla pozycji 0* i 180* (maksymalne wychylenia w obu kierunkach). Możecie do tego wykorzystać skrypt `FindMinMax`, zmieniając w nim **stopniowo** wartości 
``` C++
#define SERVOMIN  150
#define SERVOMAX  600
```
W czasie pracy serwa przysłuchujcie się czy mechanizm działa swobodnie, czy napotyka opór. Jeśli słychać skrzypienie albo serwo mocno się grzeje, to oznacza, że maksymalna wartość w danej pozycji została przekroczona i najlepiej jak najszybciej wrócić do poprzedniego ustawienia, kiedy jeszcze nie skrzypiało. 

Znalezione wartości MIN i MAX obowiązują dla tego konkretnego serwa. Wykorzystajcie je w drugim skrypcie: `Servo`, na początku programu: 
``` C++ 
const int servosMin[servosCount] = { 150 };
const int servosMax[servosCount] = { 600 };
```
Skrypt jest przygotowany do obsługi kilku serwomechanizmów jednocześnie dlatego wartości przechowywane są w tablicy. 
Ważne jest także wskazanie na którym slocie sterownika został podłączony serwomechanizm: 
``` C++
#define servosCount 1
const int servosIds[servosCount] = { 0 };
```
Numer kanału (slot) znajdziecie nad wtyczką serwa podłączoną do sterownika (jeśli podłączyliście zgodnie ze schematem powyżej będzie to `0`). 

Podłączając większą liczbę serw pamiętajcie o zwiększeniu `#define servosCount 1`. 


#### Funkcja do zadania pozycji (0-180*)
``` C++ 
setServoPosition(servoIndex, angle);
```
`servoIndex` to indeks serwomechanizmu w tablicy `servosIds` oraz `servosMin`, `servosMax`. Funkcja korzysta z tego indeksu, żeby pobrać wszystkie potrzebne w obliczeniach wartości. 
`angle` to kąt obrotu serwa, zakres: 0 - 180. 

#### Szkic, aby działać potrzebuje (0-180*)
Cały szkic do poruszana serwomechanizmem wymaga: 
- zainstalowanej biblioteki
  * `Adafruit PWM Servo Driver`
Biblioteka jest dostępna przez Menedżera bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)


## Poruszanie serwomechanizmu obrotowego

Przykładowy program to: `ContinuousRotation`, w folderze `Servo`. 

Pin, do którego podłączony jest serwomechanizm zdefiniowany jest na początku programu: `#define SERVO_PIN 9`.

Serwomechanizm obrotowy może się kręcić zgodnie lub przeciwnie do ruchu wskazówek zegara ze zmienną prędkością. Zadeklarowałam dwa pomocnicze typy zmiennych, określający kierunek: 
``` C++
enum Direction { 
  forward, 
  backward
};
```
oraz określający prędkość:
``` C++
enum Speed { 
  slowly, 
  mediumSpeed, 
  fast
};
```

Aby poeksperymentować z prędkościami trzeba zmienić wartości zadeklarowane na górze programu: 
``` C++
#define SLOWLY 15
#define MEDIUM_SPEED 30
#define FAST 90
```
 Do wprawienia serwomechanizmu w ruch służy funkcja: `move(Direction direction, Speed speed)`. W głównej pętli programu znajdują się instrukcje poruszające serwomechanizm z każdą dostępną prędkością w każdym kierunku przez 2 sekundy. 


##### Menedżer bibliotek 
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.

##### Linki
[sklep - botland - redox S90](https://botland.com.pl/serwa-redox/1684-serwo-redox-s90-micro.html)
[sklep - botland - SG5010](https://botland.com.pl/serwa-typu-standard/485-serwo-tower-pro-sg-5010.html)
[producent - adafruit - sterownik](https://www.adafruit.com/product/815)