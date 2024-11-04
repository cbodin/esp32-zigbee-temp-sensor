# ESP32 ZigBee Temp Sensor

ZigBee Temperatur Sensor End Device using an ESP32-C6 microcontroller and a DS18B20 temperature sensor.

## Credits
The code is based on the examples provided with the Arduino ESP32 and Dallas Temperature libraries:
- [Zigbee Temperature Sensor](https://github.com/espressif/arduino-esp32/blob/idf-release/v5.1/libraries/Zigbee/examples/Zigbee_Temperature_Sensor/Zigbee_Temperature_Sensor.ino)
- [Arduino Temperature Library](https://github.com/milesburton/Arduino-Temperature-Control-Library)

This project is using a [forked version](https://github.com/pstolarz/Arduino-Temperature-Control-Library/tree/OneWireNg) of the Dallas Temperature library, which in turn is using the OneWireNg library with support for ESP32 C6.

## Required software
- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO](https://platformio.org/)

## Required hardware
- ESP32-C6 (Tested with a Waveshare ESP32-C6-DEV-KIT-N8)
- DS18B20 Temperature sensor
- 4.7k Ohm resistor

A Google search for "ds18b20 esp32" will find the necessary wiring diagrams.
The default GPIO pin is set to 10.
