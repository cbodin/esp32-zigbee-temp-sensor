#include <Arduino.h>
#include "temp_sensor.cpp"
#include "zigbee_temp_sensor_device.cpp"

// Setup temp sensor and zigbee device
TempSensor tempSensor(GPIO_NUM_10);
ZigbeeTempSensorDevice zbTempSensorDevice;

void setup()
{
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
  float temp = tempSensor.getTemp();
  if (temp != TempSensor::ERR_DEVICE_DISCONNECTED)
  {
    zbTempSensorDevice.setTemperature(temp);
    log_d("Setting temperature %.2f°C", temp);
  }

  // TODO: Configure direct reporting and zigbee reset on button press

  delay(2000);
}
