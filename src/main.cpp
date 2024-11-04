#include <Arduino.h>
#include "temp_sensor.cpp"
#include "zigbee_temp_sensor_device.cpp"

// Boot button pin for ESP32-C6
#define BOOT_BUTTON_PIN 9

// Last report time
unsigned long lastReportTime = millis();

// Setup temp sensor and zigbee device
TempSensor tempSensor(GPIO_NUM_10);
ZigbeeTempSensorDevice zbTempSensorDevice;

/**
 * @brief Requests the temperature from the sensor and sets in on the zigbee device.
 */
void requestAndSetTemperature()
{
  float temp = tempSensor.getTemp();
  if (temp != TempSensor::ERR_DEVICE_DISCONNECTED)
  {
    log_d("Setting temperature %.2f°C", temp);
    zbTempSensorDevice.setTemperature(temp);
  }
  else
  {
    log_e("Temp sensor disconnected");
  }
}

void setup()
{
  pinMode(BOOT_BUTTON_PIN, INPUT);

  if (!tempSensor.setup())
  {
    log_e("Unable to setup temp sensor, couldn't find address of sensor.");
    return;
  }

  if (!zbTempSensorDevice.setup())
  {
    log_e("Unable to setup zigbee temperature sensor device.");
  }
}

void loop()
{
  if (digitalRead(BOOT_BUTTON_PIN) == LOW)
  {
    delay(100);
    unsigned long startTime = millis();

    // Checking button for factory reset
    while (digitalRead(BOOT_BUTTON_PIN) == LOW)
    {
      delay(50);

      if ((millis() - startTime) > 3000)
      {
        log_d("Resetting Zigbee to factory settings");
        zbTempSensorDevice.factoryReset();
      }
    }

    // Report temperature directly
    requestAndSetTemperature();
  }

  // Read and set temperature every 5 seconds
  if ((millis() - lastReportTime) > 5000)
  {
    requestAndSetTemperature();
    lastReportTime = millis();
  }

  delay(100);
}
