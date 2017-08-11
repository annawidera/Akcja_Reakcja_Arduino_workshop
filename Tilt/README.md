# Tilt
![Obrazek](https://cdn-shop.adafruit.com/1200x900/173-00.jpg)

## Schemat podłączenia
Na co zwrócić uwagę?
- podłącza się go tak samo, jak przycisk,
- sygnał przycisku wchodzi na pin **digital** (cyfrowy), 
- piny **0** i **1** są wykorzystywane do komunikacji Arduino z komputerem (`Serial.print("Hello");`) i podpięcie do nich przycisku uniemożliwia komunikację.
[![Schemat-podlaczenia](https://cdn-learn.adafruit.com/assets/assets/000/000/500/medium800/force___flex_tiltarduinolay.gif?1447975913)](https://learn.adafruit.com/tilt-sensor/using-a-tilt-sensor)

## Reszta tak, jak w przyciskach

## Przykładowy kod
W przykładowym kodzie `Tilt.ino` połączyłam działanie Tilta ze świeceniem diody LED wbudowanej na płytce Arduino (pin 13). 
Czas zwarcia (~= naciśnięcia przycisku) mógłby określać np. jasność świecenia diody. 