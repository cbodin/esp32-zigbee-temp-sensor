# ESP32 ZigBee Temp Sensor

ZigBee Temperatur Sensor End Device using an ESP32-C6 microcontroller and a DS18B20 temperature sensor.

## Required software
- arduino-cli

## Required hardware
- ESP32-C6 (Tested with a Waveshare ESP32-C6-DEV-KIT-N8)
- DS18B20 Temperature sensor
- 4.7k Ohm resistor

## Assembly

WIP

## Building and uploading

```sh
# Find the port for uploading and monitoring
# The upload port should have the Board name set, and the monitoring port should have an "Unknown" Board name.
arduino-cli board list

# Compile
arduino-cli compile --board-options "PartitionScheme=zigbee,ZigbeeMode=ed,DebugLevel=debug"

# Upload
arduino-cli upload -p <upload-port>
# e.g. arduino-cli upload -p /dev/cu.usbmodem143401

# Monitor
arduino-cli monitor -p <monitor-port> --config 115200
# e.g. arduino-cli monitor -p /dev/cu.usbmodem574C0335481 --config 115200
```
