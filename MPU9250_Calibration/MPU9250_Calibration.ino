#include "MPU9250.h"

MPU9250 mpu; // You can also use MPU9255 as is

void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  // change to your own address

    delay(5000);

    // calibrate anytime you want to
    mpu.calibrateAccelGyro();
    Serial.println("Acc Calibration done");
    Serial.println("Mag Calibration started");
    mpu.calibrateMag();
    Serial.println("Mag Calibration done");
}

void loop() { }
