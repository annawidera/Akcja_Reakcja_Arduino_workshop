# Przyciski
![Przycisk-zdjęcie](https://http2.mlstatic.com/boton-micro-switch-pulsador-corto-6x6x45mm-arduino-elec-D_NQ_NP_675021-MLV20686750383_042016-F.jpg)
## Schemat podłączenia
Na co zwrócić uwagę?
- rezystor: ok. 10kΩ, 
- zwarte nóżki przycisku powinny być po przeciwnych stronach szczeliny płytki stykowej, 
- sygnał przycisku wchodzi na pin **digital** (cyfrowy), 
- piny **0** i **1** są wykorzystywane do komunikacji Arduino z komputerem (`Serial.print("Hello");`) i podpięcie do nich przycisku uniemożliwia komunikację.
[![Schemat-podlaczenia](https://www.arduino.cc/en/uploads/Tutorial/101_ButtonLed_bb.png)](https://www.arduino.cc/en/Tutorial/Button)

## Obsłużone zdarzenia
Przycisk może być w jednym z 4 stanów: 
- `pressed` w chwili naciśnięcia (pojawia się raz), 
- `holdDown` w czasie, gdy jest trzymany wciśnięty (ciągły, można odcyztać długoś trwania tego stanu), 
- `released` kiedy właśnie został puszczony (pojawia się raz), 
- `holdUp` kiedy pozostaje nietknięty (ciągły, można odcyztać długoś trwania tego stanu).

Czyli sekwencja stanów może być np. taka: 
`holdUp` → `holdUp` → `holdUp` → `pressed` → `holdDown` → `holdDown` → `holdDown` → `holdDown` → `released` → `holdUp` → `holdUp`. 

#### Funkcja do obsługi stanów przycisków
Kod funkcji jest przykładowy, pokazuje co można odczytać ze zmiennej `button` (typu `Button`). 
``` C++ 
void buttonPressedHandler(Button button) {
  if (button.state == holdUp) {// Najbardziej powszechny stan, zaciemnia komunikaty w Serial Monitorze
    return;
  }

  if (button.state == pressed) {
    Serial.print("Button" ); 
    Serial.print(button.index); 
    Serial.println(" pressed");
  }
  
  Serial.print("button "); Serial.print(button.index); 
  Serial.print("     state: ");  writeState(button.state);  Serial.print(button.state);
  Serial.print("     startTime: "); Serial.print(button.startTime);
  Serial.print("     duration: "); Serial.println(button.duration);
}
```
#### Szkic do działania potrzebuje
Cały szkic do obsługi przycisków wymaga: 
- pliku `ButtonState.h` (w tym samym katalogu co szkic `Button.ino`), 
- zainstalowanych bibliotek
  * `Callback`
  * `Bounce2`
Obie biblioteki są dostępne przez Menedżera bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)

## Schemat elektryczny
Być może taki schemat okaże się wygodniejszy. 
[![Schemat-elektryczny](https://www.arduino.cc/en/uploads/Tutorial/button_schem.png)](https://www.arduino.cc/en/Tutorial/Button)

## Menedżer bibliotek
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.