#include "MPU9250.h"//bolderflight/MPU9250

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;
#define xao 0//value offsets
#define yao -0.33
#define zao -2.05
#define xmo -168
#define ymo 6
#define zmo 14

float roll;
float pitch;
float yaw;
float cfac = 0.1;//calibration factor

float prevTime;//previous time
void setup() {
  // serial to display data
  Serial.begin(9600);
  //while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}

void loop() {
  // read the sensor
  IMU.readSensor();
  // display the data
  float accx = IMU.getAccelX_mss()-xao;
  float accy = IMU.getAccelY_mss()-yao;
  float accz = IMU.getAccelZ_mss()-zao;
  float rotx = IMU.getGyroX_rads();
  float roty = IMU.getGyroY_rads();
  float rotz = IMU.getGyroZ_rads();
  float magx = IMU.getMagX_uT()-xmo;
  float magy = IMU.getMagY_uT()-ymo;
  float magz = IMU.getMagZ_uT()-zmo;
  float currentTime = millis();
  float dt = (prevTime - currentTime)/1000;
  prevTime = currentTime;
  //rotate with gyro
  roll -= rotx*dt;
  pitch -= roty*dt;
  yaw += rotz*dt;
  //calibrate with rotation that get with acceleration and linear blend it.
  float temp1 = atan2(accy, accz)-PI;
  calib(&roll, &temp1);
  float temp2 = sqrt(accz*accz+accy*accy);
  temp2 = atan2(accx, temp2);
  calib(&pitch, &temp2);
  float temp3 = atan2(magy, magx);
  calib(&yaw, &temp3);
  //Serial.print("\t");
  Serial.print(roll,6);
  Serial.print("\t");
  Serial.print(pitch,6);
  Serial.print("\t");
  Serial.println(yaw,6);
  
  delay(50);
}

void calib(float *base, float *target){//calibration
  if(*target-*base>1)*base+=TWO_PI;
  if(*base-*target>1)*base-=TWO_PI;
  *base = (1-cfac)**base+cfac**target;
}
