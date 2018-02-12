# CoupleCounter
A valentines gift to display time since memorable events

Every hour the display shows a random alias and time since a random event.
A DS3231 or DS1307 RTC is used to accurately keep time and communicates with the ESP8266 via I2C along with the 0.96" OLED Display.
The Unix Timestamp of each event is stored and then compaired to the current Unix time from the RTC and converted to days and displayed.

Prototype 1:
![Prototype1](../assets/prototype1.jpg?raw=true)
