# Serwomechanizm
[![Redox S90](http://mmhobby.pl/images/min/product_mid/326.JPG)](https://botland.com.pl/serwa-redox/1684-serwo-redox-s90-micro.html)
[![SG5010](http://www.robotistan.com/tower-pro-sg-5010-rc-servo-motor-3471-15-B.jpg)](https://botland.com.pl/serwa-typu-standard/485-serwo-tower-pro-sg-5010.html)
[![Sterownik](https://cdn-shop.adafruit.com/970x728/815-04.jpg)](https://www.adafruit.com/product/815)



## Schemat podłączenia
Na co zwrócić uwagę?
- Arduino komunikuje się ze sterownikiem serwomechanizmów po protokole **I²C**, którego linie są wyprowadzone na pinach **A4 (SDA)** i **A5 (SCL)** Arduino. 
- serwomechanizmy zużywają znacząco więcej prądu niż oferują piny Arduino, dlatego do ich działania potrzebne jest zewnętrzne źródło zasilania podpinane bezpośrednio do sterownika (na płytce sterownika jest to niebieskie gniazdo do zakręcania śrubkami), 
- **Ważne**: koniecznie trzeba zewrzeć masy (GND) Arduino i zasilacza serwomechanizmów (czarny kabel czarnej wtyczki) 

[![Schemat-podlaczenia](https://cdn-learn.adafruit.com/assets/assets/000/002/220/medium800/adafruit_products_Connections_bb-1024.jpg?1396780597)](https://learn.adafruit.com/16-channel-pwm-servo-driver/hooking-it-up)

### Serwo do sterownika
#### SG-5010
Serwo | Sterownik 
---: | :---
brązowy | GND
czerwony | V+
pomarańczowy | PWM

## Poruszanie serwomechanizmu
Serwomechanizm może się poruszać w zakresie 0* - 180*. 
#### Funkcja do zadania pozycji
``` C++ 
setServoPosition(servoId, position);
```
`servoId` to numer kanału na sterowniku, do którego podłączone są kabelki z serwa (z zakresu 0-15), 
`position` to kąt obrotu serwa, zakres: 0 - 180. 

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