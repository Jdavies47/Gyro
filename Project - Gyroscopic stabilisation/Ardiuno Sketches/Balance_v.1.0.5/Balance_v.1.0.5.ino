
////////////////////////////////////// Libary Imports ///////////////////////////////////
#include <PID_v1.h>
#include "CurieIMU.h"
#include <Servo.h>
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// Function Imports //////////////////////////////////
Servo servo1, servo2;
/////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////// Global Constants /////////////////////////////////
const float bikeConstant = 2; 
const float bikeMass = 6;
const float bikeHieght = 0.03; // 0.085For the moment of rotation about the base of the wheels.
const float wheelMOI = 0.000126; // The flywheels moment of inertia
const float g = 9.81;
const int bufferSize = 5;
const int maxPwmChange = 200;
const int maxAcel = 3; // This is the safety acceleration cap
const int motorRig1Pin = 3;
const int motorRig2Pin = 5;
const int startMotorSpeed1 = 220;
const int startMotorSpeed2 = 0;
const int STOP = 1530;
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// Global Variables //////////////////////////////////
double bikeSetPoint=0, bikeRollInput, servoPWM;
double Kp=2.1, Ki=0, Kd=0.0;
double wheelRPM = 200;
double servoAngle = 0;
int nextRollingAverage;
int servoPwmPulse = STOP;
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// Gloabal Buffers ///////////////////////////////////
int pwmDifferBuff1[bufferSize];
int pwmDifferBuff2[bufferSize];
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////// PID /////////////////////////////////////////

PID servoPID(&bikeRollInput, &servoPWM, &bikeSetPoint, Kp, Ki, Kd, DIRECT);

/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////// Setup Code //////////////////////////////////////
void setup() {

  delay(3000);
    
  CurieIMU.begin(); // Start the IMU services on the Genuino

  ////////////////// IMU Offsets ////////////////////////
  CurieIMU.setAccelerometerOffset(X_AXIS, 0.04);
  CurieIMU.setAccelerometerOffset(Y_AXIS, 0.01);
  CurieIMU.setAccelerometerOffset(Z_AXIS, -0.98);
  CurieIMU.setGyroOffset(X_AXIS, 1.72);
  CurieIMU.setGyroOffset(Y_AXIS, 1.49);
  CurieIMU.setGyroOffset(Z_AXIS, -0.44);
  ///////////////////////////////////////////////////////

  for (int i=0; i<bufferSize; ++i){ //Fills the buffer full of stationary value (i.e starts in equib)
    pwmDifferBuff1[i] = 1530;
    pwmDifferBuff2[i] = 1530;
  }

  CurieIMU.setGyroRate(25);
  CurieIMU.setAccelerometerRate(25);
  CurieIMU.setGyroRange(10); // Set the gyroscope range to 10 degrees/second (high precision)
  CurieIMU.setAccelerometerRange(2); // Set the accelerometer range to 2G
  servoPID.SetMode(AUTOMATIC);
  servoPID.SetOutputLimits(-105,105);
  servo1.attach(6);
  servo2.attach(9);
  servo1.write(STOP);
  servo2.write(STOP);

  systemReset();

  motorStart();

  //systemReset();
  
  delay(3000);
}
/////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////// Main /////////////////////////////////////////

void loop() {
  if(nextRollingAverage >= bufferSize){
    nextRollingAverage = 0; //Reset back to the start of the buffer
  }
  
  int rawax, raway, rawaz;
  int rawgx, rawgy, rawgz;
  float roll;
  int angle1, angle2, angle;
  float frameAngle;

  angle = getAngle2();
  angle1 = getAngle1();
  angle2 = getAngle2(); // This is the angle of the flywheel

  // read accelerometer measurements from device
  CurieIMU.readMotionSensor(rawax, raway, rawaz, rawgx, rawgy, rawgz);

  float ax = convertRawAcceleration(rawax);
  float ay = convertRawAcceleration(raway);
  float az = convertRawAcceleration(rawaz);
  float gx = convertRawGyro(rawgx);
  float gy = convertRawGyro(rawgy);
  float gz = convertRawGyro(rawgz);

  frameAngle = pitch(ax,ay,az);

  if(frameAngle>50){// To kill the system if fallen over.
    while(true){
      //servo1.detach(6);
      //servo2.detach(9);
      servo1.write(STOP);
      servo2.write(STOP);
    }
  }

  int pulseDir = frameAngle/abs(frameAngle); //+1/-1

  //////////////////////////////// This section is for counter roll motion ///////////////////////////////////////
  float servoRollReactionAngV = servoRollAngVel(wheelRPM, gx, angle); //This is the reaction torque from the bike roll only
  float rollPWMTimeDifference = pwmPeriodDiff(servoRollReactionAngV);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  /////////////////////////////// This section is angle correction roll //////////////////////////////////////////
  float servo1AngleReactionAngV = servoAngleAngV(abs(frameAngle), wheelRPM, angle1);
  float angle1PWMTimeDifference = pwmPeriodDiff(servo1AngleReactionAngV);

  float servo2AngleReactionAngV = servoAngleAngV(abs(frameAngle), wheelRPM, angle2);
  float angle2PWMTimeDifference = pwmPeriodDiff(servo2AngleReactionAngV);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////// PID for the two Contributions ///////////////////////////////////////////
  bikeRollInput = frameAngle; // This is the current angle of the bike.
  servoPID.Compute();
  float totalPWMChange = (rollPWMTimeDifference+angle1PWMTimeDifference);//*errorFactor;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //Add to the smoothing buffer
  pwmDifferBuff1[nextRollingAverage] = 1530-(angle1PWMTimeDifference*pulseDir);
  pwmDifferBuff2[nextRollingAverage] = 1530-(angle2PWMTimeDifference*2*pulseDir);
  int angleRollAverage1 = 0;
  int angleRollAverage2 = 0;

  for (int i=0; i<bufferSize; ++i){
    angleRollAverage1 += pwmDifferBuff1[i];
  }
  for (int i=0; i<bufferSize; ++i){
    angleRollAverage2 += pwmDifferBuff2[i];
  }

  // This is the rolling average value for PWM. CHanging the buffersize will change the amount of smoothing
  angleRollAverage1 /= bufferSize;
  angleRollAverage2 /= bufferSize;
  float pwm = (servoPWM+1530);
  float factor = 1+(sin(angle1));
  // This angleRollAverage is the delta pulse to be passed to the servoMove function
  //servoMove(angleRollAverage1,1);
  servoMove(pwm,1);
  //servoMove(pwm,2);
  //servo1.write(1530);
  //servo2.write(1530);
  delay(15);// This will also be a important fact to how quick the system will accelerate

  nextRollingAverage++;
}
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////// Functions /////////////////////////////////////

void systemReset(){ // This is to return each servo back to the servo position for the flywheels
  while(getAngle1() != 0){
    servo1.write(1543);
  }
  servo1.write(STOP);

  while(getAngle2() != 0){
    servo2.write(1543);
  }
  servo2.write(STOP);
  
}

void motorStart(){ //Until RPM measurement system implimented, this is going to spin the wheel up to a constant arbituary value
  for (int i=0; i<startMotorSpeed1;++i){
    analogWrite(motorRig1Pin,i);
    delay(50);
  }
  for (int i=0; i<startMotorSpeed2;++i){
    analogWrite(motorRig2Pin,i);
    delay(50);
  }
  delay(15000); // This is to replaced once RPM can be measured
}

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

void servoMove (int pulseSize, int servo){ // Function to move a sevro without exceeding a safe acceleration
   
   // if statement for direction
   if(servoPwmPulse-pulseSize>0){
    servoPwmPulse -= maxAcel;
   }
   else{
    servoPwmPulse += maxAcel;
   }
   if (servo == 1){
    servo1.write(servoPwmPulse);
   }
   else {
    servo2.write(servoPwmPulse);
   }
}

boolean FAILED(){
  
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
  float angle = (sensorValue+1) * (27220/1024);
  return ((int)(angle/100)-134);
}
float getAngle2(){
  int sensorValue = analogRead(A1);
  float angle = (sensorValue+1) * (21730/1024);
  return ((int)(angle/100)-170);
}
/////////////////////////////////////////////////////////////////////////////////////////
