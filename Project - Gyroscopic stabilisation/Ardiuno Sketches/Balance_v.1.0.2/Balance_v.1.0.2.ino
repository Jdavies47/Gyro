
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
const float bikeConstant = 4; 
const float bikeMass = 5;
const float bikeHieght = 0.085; // For the moment of rotation about the base of the wheels.
const float wheelMOI = 0.000126; // The flywheels moment of inertia
const float g = 9.81;
const int bufferSize = 10;
const int maxPwmChange = 200;
const int maxAcel = 3; // This is the safety acceleration cap

/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// Global Variables //////////////////////////////////
double bikeSetPoint=0, bikeRollInput, errorFactor;
double Kp=10, Ki=0, Kd=0;
double wheelRPM = 200;
double servoAngle = 0;
int nextRollingAverage;
int servoPwmPulse = 1530;
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// Gloabal Buffers ///////////////////////////////////
int pwmDifferBuff[bufferSize];
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

  for (int i=0; i<bufferSize; ++i){ //FIlls the buffer full of stationary value (i.e starts in equib)
    pwmDifferBuff[i] = 1530;
  }

  CurieIMU.setGyroRate(25);
  CurieIMU.setAccelerometerRate(25);
  CurieIMU.setGyroRange(10); // Set the gyroscope range to 10 degrees/second (high precision)
  CurieIMU.setAccelerometerRange(2); // Set the accelerometer range to 2G
  filter.begin(25);
  servoPID.SetMode(AUTOMATIC);
  servoPID.SetOutputLimits(-200,200);
  servo1.attach(9);
  servo1.write(1530);
  delay(3000);
}
/////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////// Main /////////////////////////////////////////

void loop() {
  if(nextRollingAverage >= bufferSize){
    nextRollingAverage = 0; //Reset back to the start of the buffer
  }

  //if(FAILED()){
    //break
  //}
  
  int rawax, raway, rawaz;
  int rawgx, rawgy, rawgz;
  float roll;
  int angle1, angle2, angle;
  float frameAngle;

  angle = getAngle2();
  angle1 = getAngle1();
  angle2 = getAngle2(); // This is the angle of the flywheel

  Serial.print("Angle 2: ");
  Serial.println(angle2);

  Serial.print("Angle 1: ");
  Serial.println(angle1);
  
  //Serial.print("Current Pulse width: ");
  //Serial.println(servoPwmPulse);

  // read accelerometer measurements from device
  CurieIMU.readMotionSensor(rawax, raway, rawaz, rawgx, rawgy, rawgz);

  float ax = convertRawAcceleration(rawax);
  float ay = convertRawAcceleration(raway);
  float az = convertRawAcceleration(rawaz);
  float gx = convertRawGyro(rawgx);
  float gy = convertRawGyro(rawgy);
  float gz = convertRawGyro(rawgz);

  frameAngle = pitch(ax,ay,az);
  //Serial.print("************************** ");
  //Serial.println(frameAngle);

  int pulseDir = frameAngle/abs(frameAngle); //+1/-1

  //////////////////////////////// This section is for counter roll motion ///////////////////////////////////////
  float servoRollReactionAngV = servoRollAngVel(wheelRPM, gx, angle); //This is the reaction torque from the bike roll only
  float rollPWMTimeDifference = pwmPeriodDiff(servoRollReactionAngV);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  /////////////////////////////// This section is angle correction roll //////////////////////////////////////////
  float servoAngleReactionAngV = servoAngleAngV(abs(frameAngle), wheelRPM, angle);
  float anglePWMTimeDifference = pwmPeriodDiff(servoAngleReactionAngV);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////// PID for the two Contributions ///////////////////////////////////////////
  bikeRollInput = roll; // This is the current angle of the bike.
  servoPID.Compute();
  float totalPWMChange = (rollPWMTimeDifference+anglePWMTimeDifference);//*errorFactor;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //Add to the smoothing buffer
  pwmDifferBuff[nextRollingAverage] = 1530+(anglePWMTimeDifference*pulseDir);
  int angleRollAverage = 0;


  for (int i=0; i<bufferSize; ++i){
    angleRollAverage += pwmDifferBuff[i];
  }

  // This is the rolling average value for PWM. CHanging the buffersize will change the amount of smoothing
  angleRollAverage /= bufferSize;
  //Serial.print("The smoothed value is: ");
  //Serial.println(angleRollAverage);
  // This angleRollAverage is the delta pulse to be passed to the servoMove function
  //servoMove(angleRollAverage);
  servo1.write(1550);
  delay(15);// This will also be a important fact to how quick the system will accelerate

  nextRollingAverage++;
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

float servoAngleAngV(float pitch, float wheelAngV, float servoAngle){
  float torque = massTorque(pitch);
  float bottom = (wheelMOI*wheelAngV*cos(radians(servoAngle)));
  float servoAngV = (torque/(wheelMOI*wheelAngV*cos(radians(servoAngle))));
  return servoAngV;
}

void servoMove (int pulseSize){ //dir should be 1/-1 to point a direction.
   /*if (abs(servoPwmPulse-pulseSize)<3){ // If the pulse change is small, i.e noise do nothing
    return;
   }*/
   
   // if statement for direction
   if(servoPwmPulse-pulseSize>0){
    servoPwmPulse -= maxAcel;
   }
   else{
    servoPwmPulse += maxAcel;
   }
   servo1.write(servoPwmPulse); 
}

boolean FAILED(){
  // Write code to check for a failed system
}


float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float pitch(float ax, float ay, float az){
  float angle = atan((-ay)/sqrt(ax*ax+az*az));
  return angle*57.2958;
  
}

float convertRawGyro(int gRaw) {
  // since we are using 10 degrees/seconds range
  // -10 maps to a raw value of -32768
  // +10 maps to a raw value of 32767
  float g = (gRaw * 10.0) / 32768.0;
  return g;
}
float getAngle1(){
  int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);
  float angle = (sensorValue+1) * (27220/1024);
  return ((int)(angle/100)-130);
}
float getAngle2(){
  int sensorValue = analogRead(A1);
  //Serial.println(sensorValue);
  float angle = (sensorValue+1) * (21730/1024);
  return ((int)(angle/100)-170);
}
/////////////////////////////////////////////////////////////////////////////////////////
