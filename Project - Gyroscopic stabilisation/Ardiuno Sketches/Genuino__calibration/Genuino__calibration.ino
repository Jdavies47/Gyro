#include "CurieIMU.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);
 
  
  CurieIMU.begin();
  int gx = CurieIMU.getGyroOffset(X_AXIS);
  int gy = CurieIMU.getGyroOffset(Y_AXIS);
  int gz = CurieIMU.getGyroOffset(Z_AXIS);
  int ax = CurieIMU.getAccelerometerOffset(X_AXIS);
  int ay = CurieIMU.getAccelerometerOffset(Y_AXIS);
  int az = CurieIMU.getAccelerometerOffset(Z_AXIS);

  Serial.print("The x-gyro offset: ");
  Serial.println(gx);
  Serial.print("The y-gyro offset: ");
  Serial.println(gy);
  Serial.print("The z-gyro offset: ");
  Serial.println(gz);
  Serial.print("The x-accel offset: ");
  Serial.println(ax);
  Serial.print("The y-accel offset: ");
  Serial.println(ay);
  Serial.print("The z-accel offset: ");
  Serial.println(az);

  
  delay(3000);
  while (true){
  Serial.println("Starting Calibration");
  CurieIMU.autoCalibrateGyroOffset();
  delay(1000);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 2);
  delay(1000);

  Serial.println("Completed");

  gx = CurieIMU.getGyroOffset(X_AXIS);
  gy = CurieIMU.getGyroOffset(Y_AXIS);
  gz = CurieIMU.getGyroOffset(Z_AXIS);
  ax = CurieIMU.getAccelerometerOffset(X_AXIS);
  ay = CurieIMU.getAccelerometerOffset(Y_AXIS);
  az = CurieIMU.getAccelerometerOffset(Z_AXIS);

  Serial.print("The x-gyro offset: ");
  Serial.println(gx);
  Serial.print("The y-gyro offset: ");
  Serial.println(gy);
  Serial.print("The z-gyro offset: ");
  Serial.println(gz);
  Serial.print("The x-accel offset: ");
  Serial.println(ax);
  Serial.print("The y-accel offset: ");
  Serial.println(ay);
  Serial.print("The z-accel offset: ");
  Serial.println(az);
  }
 

}

void loop() {
  // put your main code here, to run repeatedly:

}
