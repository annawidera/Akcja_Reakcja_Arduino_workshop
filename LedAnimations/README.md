# Adresowalne LEDy WS2811
![Obrazek](https://botland.com.pl/27241-thickbox_default/dioda-led-8mm-rgb-ws2811-adresowana-10szt.jpg)


## Na co zwrócić uwagę?
- jedna z nóg diody jest najdłuzsza - to pin zasilania (5V), 
- potrzebne będą: rezystor 100Ω i kondensator elektrolityczny o pojemności między 10uF a 1000uF. 
- do wysyłania informacji o kolorach uzyjemy pinu cyfrowego, np. 6. 
- piny **0** i **1** są wykorzystywane do komunikacji Arduino z komputerem (`Serial.print("Hello");`) i wykorzystanie ich do świecenia diodami uniemożliwia komunikację.

- opis wyprowadzeń: 

![Wyprowadzenia](http://awidera.idl.pl/ArduinoDIYworkshopimages/led_ws2811.png)


## Schemat podłączenia
![Schemat-podlaczenia](http://awidera.idl.pl/ArduinoDIYworkshopimages/led_ws2811_bb.png)

## Obsługa

### Inicjalizacja

Na początku programu tworzymy globalną zmienną, która reprezentuje łańcuszek LEDów w programie: 
``` C++
#define LED_STRIP_PIN 6
#define NUM_LEDS 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_STRIP_PIN, NEO_RGB + NEO_KHZ400);
```
`NUM_LEDS` to liczba diod w łańcuchu, 

`LED_STRIP_PIN` to numer pinu Arduino, do którego podłączona jest nózka DATA_IN pierwszej diody z szeregu (na schemacie połączeń zielony kabel).

Od teraz `strip` reprezentuje fizyczne diody i to na tym obiekcie będziemy wywoływać różne funkcje, aby zmienić kolor świecenia diod. 

Na początku (najlepiej w funkcji `setup()`) musimy wywołać metodę `begin()`.: 
``` C++ 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
```

### Ustawianie koloru

Do ustawiania koloru konkretnej diody służy funkcja `setPixelColor`, która występuje w kilku wersjach. 
W obu wersjach pierwszym argumentem funkcji jest indeks diody w szeregu (oczywiście numerujemy od *0*). 

W wersji dłuższej `setPixelColor(index, red, green, blue)` podajemy wszystkie składowe koloru (czerwony, zielony, niebieski) oddzielnie (💡 są to zmienne 8bitowe, typu: `uint8_t`).

W wersji krótszej `setPixelColor(index, color)` podajemy wartość koloru w całości (💡 zmienna 32bitowa, typu `uint32_t` zawierająca w sobie wszystkie składowe). 

Aby zdobyć kolor upakowany w jednej zmiennej można użyć funkcji `strip.Color(red, green, blue)`. _W przykładowym szkicu korzystam z niej przy tworzeniu tablicy `colors`_. 

## Wyświetlenie koloru na diodach

Po ustawieniu koloru funkcją `setPixelColor(...)` trzeba wysłać aktualizację kolorów do diod za pomocą funkcji `strip.show()`.

#### Szkic, aby działać potrzebuje
Cały szkic do animacji na diodach LED WS2811: 
- zainstalowanej biblioteki
  * `Adafruit_NeoPixel`
Biblioteka jest dostępna przez Menedżera bibliotek środowiska Arduino IDE (patrz na końcu dokumentu)


##### Menedżer bibliotek
Menedżer bibliotek dostępny w środowisku Arduino IDE przez menu `Szkic` → `Dołącz bibliotekę` → `Zarządzaj bibliotekami...`.

##### Linki
[link do strony produktu w sklepie botland.com.pl](https://botland.com.pl/diody-led-rgb/7294-dioda-led-8mm-rgb-ws2811-adresowana-10szt.html?search_query=ws2811&results=12)

#### Przydatne

Wpisując w Google `color picker` w wynikach wyszukiwania pierwszy powinien być widget umożliwiający przeglądanie kolorów i pobranie dla nich wartości ich składowych (r, g, b).
