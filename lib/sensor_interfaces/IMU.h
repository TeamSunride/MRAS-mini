//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_IMU_H
#define MRASV2_IMU_H

#include "Sensor.h"
#include "Vector3D.h"

class IMU : public Sensor {
public:
    /**
     * @return Current acceleration vector in ms^-2
     */
    Vector3D getAcceleration() {
        return _acceleration;
    }

    /**
     * @return Current gyroscope vector in deg/s
     */
    Vector3D getGyroVector() {
        return _gyro_vector;
    }

    Vector3D getMagnetometerVector() {
        return _magnetometer_vector;
    }

protected:
    Vector3D _acceleration{};
    Vector3D _gyro_vector{};
    Vector3D _magnetometer_vector{};
};

#endif //MRASV2_IMU_H
