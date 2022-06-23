//
// Created by tomto on 14/06/2022.
//

#include "IMU_MPU6050.h"

// class reference:
// https://www.i2cdevlib.com/docs/html/class_m_p_u6050.html#a8fc7eab1302281f6e4bc953379f3237b

#define MPU6050_FS_RANGE 3
#define MPU6050_ACCEL_SCALE_FACTOR (2048 / 9.81)
#define MPU6050_GYRO_SCALE_FACTOR 16.4

int8_t IMU_MPU6050::begin() {
    // assume that WIre.begin() was already called somewhere.

    mpu.initialize();
    mpu.setFullScaleAccelRange(MPU6050_FS_RANGE); // +- 16G
    mpu.setFullScaleGyroRange(MPU6050_FS_RANGE); // +- 2000 deg/s

    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    return 0;
}

int8_t IMU_MPU6050::readData() {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    _acceleration.setX((float) (ax / MPU6050_ACCEL_SCALE_FACTOR));
    _acceleration.setY((float) (ay / MPU6050_ACCEL_SCALE_FACTOR));
    _acceleration.setZ((float) (az / MPU6050_ACCEL_SCALE_FACTOR));
    _gyro_vector.setX((float) (gx / MPU6050_GYRO_SCALE_FACTOR));
    _gyro_vector.setY((float) (gy / MPU6050_GYRO_SCALE_FACTOR));
    _gyro_vector.setZ((float) (gz / MPU6050_GYRO_SCALE_FACTOR));
    return 0;
}
