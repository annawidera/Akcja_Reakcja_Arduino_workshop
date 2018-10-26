# Serwomechanizm
[![Redox S90](http://mmhobby.pl/images/min/product_mid/326.JPG)](https://botland.com.pl/serwa-redox/1684-serwo-redox-s90-micro.html)
[![SG5010](http://www.robotistan.com/tower-pro-sg-5010-rc-servo-motor-3471-15-B.jpg)](https://botland.com.pl/serwa-typu-standard/485-serwo-tower-pro-sg-5010.html)
[![Sterownik](https://cdn-shop.adafruit.com/970x728/815-04.jpg)](https://www.adafruit.com/product/815)


## 🔌 Schemat podłączenia
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


## Poruszanie serwomechanizmu
Serwomechanizm może się poruszać w zakresie 0* - 180*. 

### Kalibracja
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


#### Funkcja do zadania pozycji
``` C++ 
setServoPosition(servoIndex, angle);
```
`servoIndex` to indeks serwomechanizmu w tablicy `servosIds` oraz `servosMin`, `servosMax`. Funkcja korzysta z tego indeksu, żeby pobrać wszystkie potrzebne w obliczeniach wartości. 
`angle` to kąt obrotu serwa, zakres: 0 - 180. 

#### Szkic, aby działać potrzebuje
Cały szkic do poruszana serwomechanizmem wymaga: 
- zainstalowanej biblioteki
  * `Adafruit PWM Servo Driver`
Biblioteka jest dostępna przez Menedżera bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)


##### Menedżer bibliotek 
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.

##### Linki
[sklep - botland - redox S90](https://botland.com.pl/serwa-redox/1684-serwo-redox-s90-micro.html)
[sklep - botland - SG5010](https://botland.com.pl/serwa-typu-standard/485-serwo-tower-pro-sg-5010.html)
[producent - adafruit - sterownik](https://www.adafruit.com/product/815)