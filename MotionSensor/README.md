# Detektor ruchu PIR
(ang. *Passive Infra Red* - pasywny czujnik podczerwieni) - czujnik elektroniczny służący do wykrywania ruchu. Jego działanie opiera się na bardzo precyzyjnym pomiarze temperatury. Jest powszechnie stosowany w systemach alarmowych. 
[Lear Adafruit: Dokładny opis działania czujników PIR](https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/how-pirs-work)
![PIR motion sensor-zdjęcie](http://www.meccanismocomplesso.org/wp-content/uploads/2016/02/Meccanismo-Complesso-PIR-motion-sensor-SR501.jpg)

## Schemat podłączenia
Na co zwrócić uwagę?
- czujnik korzysta z pinu **cyfrowego** (w przykładowym kodzie: 2)
- wyjścia z płytki z czujnikiem powinny być podpisane (kolejność wyprowadzeń może się różnić między czujnikami różnych producentów)

PIR | Arduino
---: | :---
`VCC` | `VCC`
`OUT` | **2** (lub inny pin **cyfrowy**)
`GND` | `GND`


## Obsłużone zdarzenia
Czujnik sygnalizuje dwa zdarzenia: 
- pojawienie się ruchu w zasięgu jego badania, 
- zanik ruchu

Wykrycie ruchu sygnalizowane jest natychmiast. Informacja o zaniku ruchu pojawia się z pewnym opóźnieniem (które można regulować potencjometrem na płytce sensora). 
Drugi potencjometr (Sx) służy do regulacji czułości. 

Przy każdej zmianie stanu (wykryto ruch / brak ruchu) wywoływana jest funkcja z parametrem `isMotion`, który przyjmuje wartości odpowiednio `true` i `false`:
``` C++ 
void motionStatusChanged(bool isMotion) {
  switch (isMotion) {
    case true: Serial.println("Motion detected"); break; 
    case false: Serial.println("Motion disappeared"); break;
  }
}
```
Można też przechwytywać i obsługiwać na bieżąco aktualny stan ruchu, wtedy trzeba usunąć filtrowanie:
`if (currentMotionStatus != isMotion)`. 