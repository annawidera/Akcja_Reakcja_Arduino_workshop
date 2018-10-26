# Serwomechanizm obrotowy 360*
[![SG5010](https://nettigo.pl/system/images/1979/original.jpg?1483454715)](https://nettigo.pl/products/serwomechanizm-obrotowy-360-stopni)

## 🔌 Schemat podłączenia
Na co zwrócić uwagę?
- Serwomechanizm podłączamy bezpośrednio do Arduino, ale ze względu na pobór mocy lepiej jest zasilić je korzystając z zewnętrznego zasilacza, 
- ważne: masy (GND) Arduino i zasilacza muszą być zwarte, najlepiej na płytce stykowej. 

![Schemat-podlaczenia](http://www.awidera.idl.pl/ArduinoDIYworkshopimages/servo_continuous_rotation.png)

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


##### Linki
[sklep - nettigo - DS04-NFC](https://nettigo.pl/products/serwomechanizm-obrotowy-360-stopni)