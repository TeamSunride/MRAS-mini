//
// Created by Tom Danvers on 05/12/2022.
//

#include <cstdio>
#include "timestamp.h"
#include "MRAS_System.h"
#include "MRAS_Config.h"
#include "ArduinoTextLogger.h"
#include "NativeDataLogger.h"
#include "Sensor_LSM6DSO32.h"
#include "Arduino.h"
#include "Sensor_LIS3MDL.h"
#include "Sensor_MS5607.h"
#include "Sensor_ADXL375.h"
#include "Sensor_ZOEM8Q.h"
#include "RocketTelemetrySystem.h"
#include "RocketSDLogger.h"
#include "ArduinoBuzzer.h"
#include "StateEstimator.h"

auto logger = ArduinoTextLogger(0, 0);
MRAS_System *mras = MRAS_System::get_instance();

NativeDataLogger data_logger = NativeDataLogger(1);

Sensor_LSM6DSO32 imu = Sensor_LSM6DSO32(2, MRAS_LSM6DSO32_CHIP_SELECT, MRAS_LSM6DSO32_SPI_BUS,
                                        MRAS_LSM6DSO32_SPI_FREQUENCY);
Sensor_LIS3MDL magnetometer = Sensor_LIS3MDL(3, MRAS_LIS3MDL_CHIP_SELECT, MRAS_LIS3MDL_SPI_BUS,
                                             MRAS_LIS3MDL_SPI_FREQUENCY);
Sensor_MS5607 barometer = Sensor_MS5607(4, MRAS_MS5607_I2C_ADDRESS, MRAS_MS5607_I2C_BUS,
                                        MRAS_MS5607_I2C_FREQUENCY);
Sensor_ADXL375 accelerometer = Sensor_ADXL375(5, MRAS_ADXL375_CHIP_SELECT, MRAS_ADXL375_SPI_BUS,
                                              MRAS_ADXL375_SPI_FREQUENCY);
Sensor_ZOEM8Q gnss = Sensor_ZOEM8Q(6, MRAS_GNSS_I2C_BUS, MRAS_GNSS_I2C_FREQUENCY);

RocketTelemetrySystem telemetry_system = RocketTelemetrySystem(7);

RocketSDLogger sd_logger = RocketSDLogger(8, BUILTIN_SDCARD);

StateEstimator altitudeEstimator = StateEstimator(9, 0.001);

ArduinoBuzzer buzzer = ArduinoBuzzer(10, 10);

void setup() {
    setSyncProvider(getTeensy3Time);

    mras->set_logger(&logger);
    mras->set_buzzer(&buzzer);
    mras->add_subsystem(&sd_logger);
    mras->add_subsystem(&data_logger);
    mras->add_subsystem(&magnetometer);
    mras->add_subsystem(&imu);
    mras->add_subsystem(&gnss);
    mras->add_subsystem(&barometer);
    mras->add_subsystem(&accelerometer);
    mras->add_subsystem(&telemetry_system);
    mras->add_subsystem(&altitudeEstimator);


    // imu.add_subscriber(&data_logger);
    // magnetometer.add_subscriber(&data_logger);
    barometer.add_subscriber(&data_logger);
    // accelerometer.add_subscriber(&data_logger);
    gnss.add_subscriber(&data_logger);
    // altitudeEstimator.add_subscriber(&data_logger);
    imu.add_subscriber(&altitudeEstimator);
    barometer.add_subscriber(&altitudeEstimator);

//     setup SD logger subscriptions
    logger.add_subscriber(&sd_logger);
    imu.add_subscriber(&sd_logger);
    magnetometer.add_subscriber(&sd_logger);
    barometer.add_subscriber(&sd_logger);
    accelerometer.add_subscriber(&sd_logger);
    gnss.add_subscriber(&sd_logger);
    altitudeEstimator.add_subscriber(&sd_logger);

    gnss.add_subscriber(&telemetry_system);
    imu.add_subscriber(&telemetry_system);
    barometer.add_subscriber(&telemetry_system);
    altitudeEstimator.add_subscriber(&telemetry_system);


    mras->setup();
}

void loop() {
    mras->loop();
    //Serial.println(millis());
}