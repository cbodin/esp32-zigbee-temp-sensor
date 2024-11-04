#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/**
 * @class TempSensor
 * @brief Handles the Dallas temperature sensor integration.
 */
class TempSensor
{
    OneWire oneWire;
    DallasTemperature sensors;
    DeviceAddress tempSensor;

public:
    /** Returned if the device was disconnected when reading the temperature. */
    static constexpr float ERR_DEVICE_DISCONNECTED = DEVICE_DISCONNECTED_C;

    /**
     * @brief Constructs a TempSensor object with the specified pin.
     * @param tempSensorPin The pin number where the temperature sensor is connected.
     */
    TempSensor(uint8_t tempSensorPin)
        : oneWire(tempSensorPin), sensors(&oneWire)
    {
    }

    TempSensor(const TempSensor &) = delete;
    TempSensor &operator=(const TempSensor &) = delete;

    /**
     * @brief Initializes the temperature sensor and finds the address.
     * @return True if the sensor was found; false otherwise.
     */
    bool setup()
    {
        sensors.begin();
        sensors.setResolution(12);

        return sensors.getAddress(tempSensor, 0);
    }

    /**
     * @brief Retrieves the temperature in degrees Celsius.
     * @return The temperature, or ERR_DEVICE_DISCONNECTED if the sensor is disconnected.
     */
    float getTemp()
    {
        sensors.requestTemperaturesByAddress(tempSensor);
        return sensors.getTempC(tempSensor);
    }
};
