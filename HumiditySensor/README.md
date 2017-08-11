# Czujnik wilgotności i temperatury
[![DHT22-czujnik wilgotnosci i tempratury](http://www.jarzebski.pl/media/medium/publish/2014/04/dht22.png)](http://www.jarzebski.pl/arduino/czujniki-i-sensory/czujnik-wilgotnosci-i-temperatury-dht11-dht22.html)

## Schemat podłączenia
Na co zwrócić uwagę?
- sygnał przycisku wchodzi na pin **digital** (cyfrowy), 
- nóżka z danymi (2 od lewej) jest "podciągnięta" przez rezystor (10kΩ) do VCC,
- 3 nóżka od lewej pozostaje niepodłączona, 
- piny **0** i **1** są wykorzystywane do komunikacji Arduino z komputerem (`Serial.print("Hello");`) i podpięcie do nich czujnika uniemożliwia komunikację.
![Schemat-podlaczenia](https://plot.ly/static/img/workshop/arduino-dht22-temperature-hookup.svg)

## Mierzone parametry
Czujnik mierzy temperaturę i wilgotność otoczenia. Ma całkiem niezłą dokładność i responsywność. *Polecam spróbować dmuchnąć czujnikowi w... kratkę* 
Zapożyczone z opisu na stronie sklepu i z dokumentacji: 
- Temperatura
  - Zakres pomiarowy: -40 do 80 °C
  - Rozdzielczość: 8-bitów (0,1 °C)
  - Dokładność: ± 0,5 °C
  - Czas odpowiedzi: średnio 2 s
- Wilgotność:
  - Zakres pomiarowy: 0 - 100 % RH
  - Rozdzielczość: 8-bitów (±0,1 % RH)
  - Dokładność ±2 %RH*
  - Czas odpowiedzi: średnio 2 s
  *RH - Wilgotność względna wyrażana w procentach. Jest to stosunek rzeczywistej wilgoci w powietrzu do maksymalnej jej ilości, którą może utrzymać powietrze w danej temperaturze.

## Obsługa
Dostęp do aktualnych wartości obu mierzonych parametrów (wilgotność względna wyrażona w procentach, temperatura w stopniach Celsjusza) dają funkcje: 
``` C++ 
void humidityValueChangeHandler(float humidity) {
  Serial.print("humidity: "); Serial.println(humidity);
}

void temperatureValueChangedHandler(float temperature) {
  Serial.print("temperature: "); Serial.print(temperature); Serial.println("*C");
}
```

#### Szkic, aby działać potrzebuje
Przygotowany przeze mnie szkic do obsługi czujnika DHT wymaga zainstalowanej biblioteki
  * `DHT`
Wybrałam bibliotekę napisaną przez Marka Ruysa, ze względu na prostotę użycia. Tą bibliotekę trzeba samodzielnie pobrać z github'a, tutaj: https://github.com/markruys/arduino-DHT i zgodnie z instrukcją zamieszczoną w opisie:
> Place the DHT library folder in your <arduinosketchfolder>/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the Arduino IDE.


## Schemat elektryczny
Być może taki schemat okaże się wygodniejszy (DHT11 i DHT22 są komplementarne, DHT11 mierzy po prostu mniejszy zakres temperatur i wilgotności)
[![Schemat-elektryczny](http://www.jarzebski.pl/media/medium/publish/2013/11/dht11-conn.png)](https://www.arduino.cc/en/Tutorial/Button)


##### Linki
[Szczegółowy opis podpięcia i oprogramowania czujnika na blogu Jarzębskiego](http://www.jarzebski.pl/arduino/czujniki-i-sensory/czujnik-wilgotnosci-i-temperatury-dht11-dht22.html)
[botland - link do sklepu](https://botland.com.pl/czujniki-temperatury/1612-czujnik-temperatury-i-wilgotnosci-dht22-am2023.html)