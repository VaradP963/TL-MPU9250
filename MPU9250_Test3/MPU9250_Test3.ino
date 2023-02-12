#include "MPU9250.h"

MPU9250 mpu;

void setup() {
  Serial.begin(115200);

  Wire.begin();

  delay(2000);
  mpu.setup(0x68); 

  delay(5000);

  // calibrate anytime you want to
  mpu.calibrateAccelGyro();
  mpu.calibrateMag();

  //mpu.printCalibration();
}

void loop() {
  static uint32_t prev_ms = millis();
  if ((millis() - prev_ms) > 100) {
    mpu.update();
    // mpu.print();
    Serial.print("$");
    //Serial.print("roll  (x-forward (north)) : ");
    Serial.print(mpu.getRoll());
    Serial.print("\t");
    //Serial.print("pitch (y-right (east))    : ");
    Serial.print(mpu.getPitch());
    Serial.print("\t");
    //Serial.print("yaw   (z-down (down))     : ");
    Serial.print(mpu.getYaw());
    Serial.println("\n");
    Serial.print("The Temp is:");
    Serial.println(mpu.getTemperature());
    
    prev_ms = millis();
  }
}
