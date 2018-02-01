// Test Script to find the servo position of a continous Servo
#include<Servo.h>

Servo TestServo;

float servoPos = 90; //Asssume starts at flat position
int times[2];
int order = 0;
void setup() {

  Serial.begin(9600);

  TestServo.attach(9);


}

void loop() {

  if (order > 1){
    order = 0;
  }
  times[order] = micros;
  TestServo.write(1560);
  Serial.println(times[order]);

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
