#include "ZigbeeCore.h"
#include "ep/ZigbeeTempSensor.h"

/**
 * @class ZigbeeTempSensorDevice
 * @brief Handles the Zigbee end device integration for reporting temperature.
 */
class ZigbeeTempSensorDevice
{
    ZigbeeTempSensor *zbTempSensor;

public:
    /**
     * @brief Constructs a TempSensor object with the specified pin.
     * @param tempSensorPin The pin number where the temperature sensor is connected.
     */
    ZigbeeTempSensorDevice()
    {
        zbTempSensor = new ZigbeeTempSensor(10);
    }

    ~ZigbeeTempSensorDevice()
    {
        // The desctructure function of ZigbeeTempSensor is currently undefined-
        // We work around this by using a pointer and skipping destructure completely.
        // delete zbTempSensor;
    }

    ZigbeeTempSensorDevice(const ZigbeeTempSensorDevice &) = delete;
    ZigbeeTempSensorDevice &operator=(const ZigbeeTempSensorDevice &) = delete;

    /**
     * @brief Initializes the temperature sensor and finds the address.
     * @return True if the sensor was found; false otherwise.
     */
    bool setup()
    {
        zbTempSensor->setManufacturerAndModel("Espressif", "ZigbeeTempSensor");
        zbTempSensor->setMinMaxValue(-55, 125);
        zbTempSensor->setTolerance(0.01);

        Zigbee.addEndpoint(zbTempSensor);
        bool status = Zigbee.begin(ZIGBEE_END_DEVICE);

        if (status)
        {
            zbTempSensor->setReporting(0, 10, 0);
        }

        return status;
    }

    /**
     * @brief Sets the current temperature to be reported. In degrees celcius.
     */
    void setTemperature(float value)
    {
        zbTempSensor->setTemperature(value);
    }

    /**
     * @brief Trigger a temperature report.
     */
    void reportTemperature()
    {
        zbTempSensor->reportTemperature();
    }

    /**
     * @brief Factory reset the zigbee controller.
     */
    void factoryReset()
    {
        Zigbee.factoryReset();
    }
};
