
////////////////////////////////////// Libary Imports ///////////////////////////////////
#include <PID_v1.h>
#include "CurieIMU.h"
#include <MadgwickAHRS.h>
#include <Servo.h>
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// Function Imports //////////////////////////////////
Servo servo1;
Madgwick filter;
/////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////// Global Constants /////////////////////////////////
float bikeConstant = 4; 
float bikeMass = 4;
float bikeHieght = 0.085; // For the moment of rotation about the base of the wheels.
float wheelMOI = 0.000126; // The flywheels moment of inertia
float g = 9.81;

/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// Global Variables //////////////////////////////////
double bikeSetPoint=0, bikeRollInput, errorFactor;
double Kp=10, Ki=0, Kd=0;
double wheelRPM = 733;
double servoAngle = 0;
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// Gloabal Buffers ///////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////// PID /////////////////////////////////////////


PID servoPID(&bikeRollInput, &errorFactor, &bikeSetPoint, Kp, Ki, Kd, DIRECT);

/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////// Setup Code //////////////////////////////////////
void setup() {

  Serial.begin(9600); // This is temporary for debugging purposes only.
  while (!Serial); // Forces a wait for the serial port to open. Needed on the genuino.

  CurieIMU.begin(); // Start the IMU services on the Genuino

  ////////////////// IMU Offsets ////////////////////////
  CurieIMU.setAccelerometerOffset(X_AXIS, 0.04);
  CurieIMU.setAccelerometerOffset(Y_AXIS, 0.01);
  CurieIMU.setAccelerometerOffset(Z_AXIS, -0.98);
  CurieIMU.setGyroOffset(X_AXIS, 1.72);
  CurieIMU.setGyroOffset(Y_AXIS, 1.49);
  CurieIMU.setGyroOffset(Z_AXIS, -0.44);
  ///////////////////////////////////////////////////////

  CurieIMU.setGyroRate(25);
  CurieIMU.setAccelerometerRate(25);
  CurieIMU.setGyroRange(10); // Set the gyroscope range to 10 degrees/second (high precision)
  CurieIMU.setAccelerometerRange(2); // Set the accelerometer range to 2G
  filter.begin(25);
  servoPID.SetMode(AUTOMATIC);
  servoPID.SetOutputLimits(-200,200);
  servo1.attach(9);
}
/////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////// Main /////////////////////////////////////////
void loop() {
  int rawax, raway, rawaz;
  int rawgx, rawgy, rawgz;
  float roll;
  int angle;

  angle = getAngle();

  //Serial.print("This is the angle: ");
  Serial.println(angle);
  

  // read accelerometer measurements from device
  CurieIMU.readMotionSensor(rawax, raway, rawaz, rawgx, rawgy, rawgz);

  float ax = convertRawAcceleration(rawax);
  float ay = convertRawAcceleration(raway);
  float az = convertRawAcceleration(rawaz);
  float gx = convertRawGyro(rawgx);
  float gy = convertRawGyro(rawgy);
  float gz = convertRawGyro(rawgz);

  filter.updateIMU(gx, gy, gz, ax, ay, az);

  roll = filter.getRoll(); // This produces the angle in degrees for the bikes current postion

  //////////////////////////////// This section is for counter roll motion ///////////////////////////////////////
  float servoRollReactionAngV = servoRollAngVel(wheelRPM, abs(gx), servoAngle); //This is the reaction torque from the bike roll only
  float rollPWMTimeDifference = pwmPeriodDiff(servoRollReactionAngV);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  /////////////////////////////// This section is angle correction roll //////////////////////////////////////////
  float servoAngleReactionAngV = servoAngleAngV(abs(roll), wheelRPM, servoAngle);
  float anglePWMTimeDifference = pwmPeriodDiff(servoAngleReactionAngV);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////// PID for the two Contributions ///////////////////////////////////////////
  bikeRollInput = roll; // This is the current angle of the bike.
  servoPID.Compute();
  float totalPWMChange = (rollPWMTimeDifference+anglePWMTimeDifference);//*errorFactor;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  delay(15);
  //Serial.println(errorFactor);

  if (roll>0){
    if (gx>0){
      servo1.write(1530+totalPWMChange);
    }
    else{
      //servo1.write(1530+(abs(errorFactor)));//*anglePWMTimeDifference));
      servo1.write(1530+anglePWMTimeDifference);
    }
  }
  else{
    if (gx>0){
      //servo1.write(1530-(abs(errorFactor)));//*anglePWMTimeDifference));
      servo1.write(1530-anglePWMTimeDifference);
    }
    else{
      servo1.write(1530-totalPWMChange);
    }
  }
  //servo1.write(1600);
}
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////// Functions /////////////////////////////////////

// This function returns the servo angular velocity required to provide a corrective torque
float servoRollAngVel(float wangvel, float rollg, float servoAngle){
  float sangvel = ((bikeConstant*rollg)/(wangvel*wheelMOI*cos(radians(servoAngle))));
  return sangvel;
}

// This function returns the pulse width value needed for a specified servo angular velocity.
long pwmPeriodDiff (float servoAngVelDeg){
  float sangvel = servoAngVelDeg*0.017453;
  long t = (1.0907*sangvel*sangvel*sangvel*sangvel*sangvel) - (11.927*sangvel*sangvel*sangvel*sangvel) + (46.999*sangvel*sangvel*sangvel) - (78.133*sangvel*sangvel) + (63.148*sangvel) - 0.5;
  return t;
}

float massTorque(float angle){
  float torque = bikeMass*g*(bikeHieght*sin(radians(angle)));
  return torque;
}

float servoAngleAngV(float angle, float wheelAngV, float servoAngle){
  float torque = massTorque(angle);
  float bottom = (wheelMOI*wheelAngV*cos(radians(servoAngle)));
  float servoAngV = (torque/(wheelMOI*wheelAngV*cos(radians(servoAngle))));
  return servoAngV;
}

float currentServoAngle(float previousAngle){
  
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float convertRawGyro(int gRaw) {
  // since we are using 10 degrees/seconds range
  // -10 maps to a raw value of -32768
  // +10 maps to a raw value of 32767
  float g = (gRaw * 10.0) / 32768.0;
  return g;
}
float getAngle(){
  int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);
  float angle = (sensorValue+1) * (27220/1024);
  return ((int)(angle/100)-139);
}
/////////////////////////////////////////////////////////////////////////////////////////
