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
     * @brief Constructs a ZigbeeTempSensorDevice object.
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
     * @brief Initializes and configures the Zigbee library.
     * @return True if the zigbee service was started successfully; false otherwise.
     */
    bool setup()
    {
        zbTempSensor->setManufacturerAndModel("Espressif", "ZigbeeTempSensor");
        zbTempSensor->setMinMaxValue(-55, 125);
        zbTempSensor->setTolerance(0.01f);

        Zigbee.addEndpoint(zbTempSensor);
        bool status = Zigbee.begin(ZIGBEE_END_DEVICE);

        if (status)
        {
            // Set reporting interval for temperature measurement in seconds, must be called after Zigbee.begin()
            // min_interval and max_interval in seconds, delta (temp change in °C)
            // if min = 1 and max = 0, reporting is sent only when temperature changes by delta
            // if min = 0 and max = 10, reporting is sent every 10 seconds or temperature changes by delta
            // if min = 0, max = 10 and delta = 0, reporting is sent every 10 seconds regardless of temperature change
            zbTempSensor->setReporting(0, 10, 0.1f);
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
