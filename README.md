# przechowalnia
Sterowanie temperaturą w przechowalni warzyw oraz jej wizualizacja
##
Celem działania jest użycie powietrza zewnętrznego do schłodzenia przechowywanych warzyw. 
###
Poniżej widok przechowalni; pod okapem dachu poziome klapy poruszne elektrycznymi siłownikami liniowymi pełniące rolę wyrzutni ciepłego powietrza; na ścianie pionowy kanał rozpoczynjący się czerpnią zimnego powietrza zewnętrznego, wewnątrz kanału wentylator wyrzucający chłodne powietrze.
![przechowalnia](./img/IMG_20190705_132048.jpg)
![wentylator](./img/IMG_20190705_132010_HHT.jpg)
Układ sterujący okresowo przyjmuje wiadomości od bezprzewodowych czujników zawierające zmierzoną temperaturę oraz napięcie baterii zasilających. Zakładając, że  wiadomości są wysyłane co 10 minut, baterie pozwalają na 2 lata pracy czujnika. Poniżej układ czujnika z sondą temperatury.
![czujnik](./img/IMG_20190705_132203.jpg)

Układ sterujący na podstawie danych steruje stanem przepustnic wentylacyjnych oraz wentylatorów, a także przesyła zebrane wartości poprzez formularz php do bazy sql. Wizualizacja  możliwa poprzez google charts lub serwis Grafana.

![gcharts](./img/gcharts.png)

![grafana](./img/grafana.png)
