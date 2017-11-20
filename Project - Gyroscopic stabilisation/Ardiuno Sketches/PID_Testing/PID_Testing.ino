
#include <PID_v1.h>
#include "CurieIMU.h"
#include <MadgwickAHRS.h>
#include <Servo.h>

Servo myservo;
Madgwick filter;
unsigned long microsPerReading, microsPrevious;
float accelScale, gyroScale;

// Constants
float wmoi = 0.000126; // The flywheels moment of inertia
float bikeConst = 1.5 ; // This is a factor that need to be chnaged per system for the bike MOI
const int buffersize = 200;
int NRA;
/////////

// Buffer arrays
float gxb[buffersize];
float gyb[buffersize];
float gzb[buffersize];
float rb[buffersize];
////////////////////

int Servomid = 96;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=0, consKi=0, consKd=0;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

void setup()
{
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  Serial.println("Starting Setup");
  delay(3000);

  // initialize device
  Serial.println("Initializing IMU device...");

  CurieIMU.begin();

  CurieIMU.setAccelerometerOffset(X_AXIS, -0.04);
  CurieIMU.setAccelerometerOffset(Y_AXIS, -0.01);
  CurieIMU.setAccelerometerOffset(Z_AXIS, 0.98);
  CurieIMU.setGyroOffset(X_AXIS, -1.72);
  CurieIMU.setGyroOffset(Y_AXIS, -1.49);
  CurieIMU.setGyroOffset(Z_AXIS, 0.44);
  
  //CurieIMU.autoCalibrateGyroOffset();
  //CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 2);
  CurieIMU.setGyroRate(25);
  CurieIMU.setAccelerometerRate(25);
  filter.begin(25);

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  // Set the gyroscope range to 250 degrees/second
  CurieIMU.setGyroRange(10);
  
  //initialize the variables we're linked to
  Input = 1;
  Setpoint = 0; // Need to check this value with the filter scale-ings
  int tax, tay, taz;
  int tgx, tgy, tgz;
  CurieIMU.readMotionSensor(tax, tay, taz, tgx, tgy, tgz);

  Serial.print("X is: ");
  Serial.print(convertRawAcceleration(tax));
  Serial.print(" Y is: ");
  Serial.print(convertRawAcceleration(tay));
  Serial.print(" Z is: ");
  Serial.print(convertRawAcceleration(taz));
  Serial.print(" GX is: ");
  Serial.print(convertRawGyro(tgx));
  Serial.print(" GY is: ");
  Serial.print(convertRawGyro(tgy));
  Serial.print(" GZ is: ");
  Serial.print(convertRawGyro(tgz));

  Serial.println(" At mid point");

  delay(3000);

  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-100, 100);

  myservo.attach(9);

}

void loop()
{
  int rawax, raway, rawaz;
  int rawgx, rawgy, rawgz;
  float ax, ay, az;
  float gx, gy, gz;
  float roll, pitch, heading;
  float xRA = 0;
  float yRA = 0;
  float zRA = 0;
  float smoothRoll;
  unsigned long microsNow;
  int sensorValue = analogRead(A1);
  double p = sensorValue * (0.5/ 1023.0);

  myPID.SetTunings(p,consKi,consKd);

  if (NRA >= buffersize){ //To reset the array number to cycle through
    NRA = 0;
  }

  // check if it's time to read data and update the filter
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {

    // read raw data from CurieIMU
    CurieIMU.readMotionSensor(rawax, raway, rawaz, rawgx, rawgy, rawgz);

    // convert from raw data to gravity and degrees/second units
    ax = convertRawAcceleration(rawax);
    ay = convertRawAcceleration(raway);
    az = convertRawAcceleration(rawaz);
    gx = convertRawGyro(rawgx);
    gy = convertRawGyro(rawgy);
    gz = convertRawGyro(rawgz);

    
    gxb[NRA] = gx;
    gyb[NRA] = gy;
    gzb[NRA] = gz;

    for (int i=0; i< buffersize; ++i){
      xRA += gxb[i];
      yRA += gyb[i];
      zRA += gzb[i];
    }
    xRA /= buffersize;
    yRA /= buffersize;
    zRA /= buffersize;

    /*Serial.println("Averages:");
    Serial.println(xRA);
    Serial.println(yRA);
    Serial.println(zRA);*/

    // update the filter, which computes orientation
    filter.updateIMU(xRA, yRA, zRA, ax, ay, az);

    // print the heading, pitch and roll
    roll = filter.getRoll();

    rb[NRA++] = roll;
    for (int i=0; i< buffersize; ++i){
      smoothRoll += rb[i];
    }
    smoothRoll /= buffersize;

    // increment previous time, so we keep proper pace
    microsPrevious = microsPrevious + microsPerReading;
  }
  
  Input = smoothRoll;

  //Serial.println(Input);

  /*double gap = abs(Setpoint-Input); //distance away from setpoint
  if (gap < 1)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
  }*/

  myPID.Compute();

  float servoSpeed = servoAngVel(261.8, abs(Output), 10);
  float midPointDiff = pwmPeriodDiff(servoSpeed);

  if (roll>0){
    myservo.write(1530 + midPointDiff);
  }
  else{
    myservo.write(1530 - midPointDiff);
  }
   
  //Serial.print("The counter roll is: ");
  //Serial.println(i);
  //myservo.write(i);
  //Serial.print("The output value is: ");
  //Serial.println(Output);
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  
  float g = (gRaw * 10.0) / 32768.0;
  return g;
}

float servoAngVel(float wangvel, float roll, float angle){
  float sangvel = ((bikeConst*roll)/(wangvel*wmoi*angle));
  //Serial.print("The sangvel is: ");
  //Serial.println(sangvel);
  return sangvel;
}

long pwmPeriodDiff (float sangvel){
  long t = (1.0907*sangvel*sangvel*sangvel*sangvel*sangvel) - (11.927*sangvel*sangvel*sangvel*sangvel) + (46.999*sangvel*sangvel*sangvel) - (78.133*sangvel*sangvel) + (63.148*sangvel) - 0.5;
  //Serial.print("The diff is: ");
  //Serial.println(t);
  return t;
}

