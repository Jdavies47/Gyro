#include "I2Cdev.h"
#include "MPU6050.h"
#include <Servo.h>
#include <PID_v1.h>

Servo Jim;

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  #include "Wire.h"
#endif

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

#define LED_PIN 13
bool blinkstate = false;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=5, Ki=2, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  // put your setup code here, to run once:

  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  Serial.begin(9600);
  Serial.println("Intializing I2C devices");
  accelgyro.initialize();

  Jim.attach(9);
  Serial.println("Centering Servo.... Please wait");
  Jim.write(90);
  delay(2000);
  Serial.println("....done.");

  //My MPU6050 offsets

  accelgyro.setXAccelOffset(-2535);
  accelgyro.setYAccelOffset(180);
  accelgyro.setZAccelOffset(1850);    
  accelgyro.setXGyroOffset(26);
  accelgyro.setYGyroOffset(-49);
  accelgyro.setZGyroOffset(-2);
  
  Serial.println("Finding current angle");
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  int angle = map(ax, -16384, 16384, 0, 180);
  Serial.println(angle);
  Input = ax;
  Setpoint = 0;

  myPID.SetMode(AUTOMATIC);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Input = ax;
  Serial.println("ax value:");
  Serial.println(ax);
  Serial.println("Input value:");
  Serial.println(Input);
  
  myPID.Compute();
  Serial.println("Output value:");
  Serial.println(Output);
  int Sangle = map(Output, -16384, 16384, 0, 180);
  Serial.println("Angle value:");
  Serial.println(Sangle);

  Jim.write(Sangle);
  delay(15);

}
