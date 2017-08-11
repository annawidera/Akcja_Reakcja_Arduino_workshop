# Silnik krokowy ze sterownikiem (ULN2003)
Silnik krokowy może poruszać się w kółko (360*, w przeciwieństwie do serwomechanizmów, które poruszają się w zakresie 180*), o zadaną precyzyjnie liczbę kroków. Ruch nie jest szybki, ale dość precyzyjny. 
![28BYJ-48-Stepper motor](http://www.prometec.net/wp-content/uploads/2015/06/FT68TVVHMMF4Z5P.LARGE_.jpg)

## Schemat podłączenia
Na co zwrócić uwagę?
- silnik wymaga zewnętrznego źródła zasilania (np. z ładowarki telefonu USB przez przecięty kabel USB, z którego wyprowadzone są linie zasilania GND i VCC), 
- ważne jest aby zewrzeć masy (`GND`) Arduino i zasilania samego silnika, 
- sygnały sterujące to piny **digital** (cyfrowe), 
- piny **0** i **1** są wykorzystywane do komunikacji Arduino z komputerem (`Serial.print("Hello");`) - wykorzystanie ich do sterowania silnikiem uniemożliwia komunikację.

![Schemat-podlaczenia](http://www.awidera.idl.pl/ArduinoDIYworkshopimages/StepperConnectionDiagram.png)

## Działanie silnika
Do obsługi silnika wykorzystamy bibliotekę opublikowaną przez [Engy Fun'a](http://engyfun.blogspot.com/2015/02/here-is-source-code-for-our-28byj48.html) z moimi modyfikacjami (dołączam ją do przygotowanego szkicu `StepperMotor.ino` w tym samym katalogu). 

Trzeba stworzyć obiekt reprezentujący silnik w kodzie programu, podając piny Arduino, do których zostały podpięte wyprowadzenia sterownika (od IN1 do IN4). 
``` C++ 
StepperMotor motor(8,9,10,11);
```
Następnie ustawić czas trwania jednego kroku (w milisekundach) oraz liczbę kroków składających się na pełen obrót (360*): 
``` C++
motor.setStepDuration(1);
motor.setStepsPerRevolution(4096);
  ```
i silnik nadaje się do użytku :)

#### Pełne obroty
Jedną z opcji poruszania silnikiem jest obrót o zadaną liczbę pełnych obrotów zgodnie z ruchem wskazówek zegara lub przeciwnie: 
``` C++ 
motor.stepRevolutions(5, cw);
motor.stepRevolutions(2, ccw);
```
Pierwszy argument to liczba obrotów, drugi określa kierunek obrotów. 

#### Zadana liczba kroków
``` C++ 
motor.step(-800);
```
Jedyny argument określa liczbę kroków. Jeśli jest liczbą dodatnią, ruch odbywa się zgodnie z kierunkiem ruchu wskazówek zegara, dla liczb ujemnych: przeciwnie. 

### I ot, cała filozofia! :)
Do silnika można przytroczyć np. nietypowe wskazówki 
![Fortune wheel](https://s-media-cache-ak0.pinimg.com/236x/d0/4c/04/d04c04b0bb709634284e3d2068968892--cool-room-decor-cool-rooms.jpg)
i realizować ważne, życiowe wybory: 
![Garfield](https://i1.kwejk.pl/k/obrazki/126086-kolo-fortuny.gif)
#### Szkic, aby działać potrzebuje
Cały szkic do sterowania silnikiem wymaga plików biblioteki `StepperMotor.h` i `StepperMotor.cpp` (w tym samym katalogu co szkic `StepperMotor.ino`).Są załączone w szkicu, który dla Was udostępniam.