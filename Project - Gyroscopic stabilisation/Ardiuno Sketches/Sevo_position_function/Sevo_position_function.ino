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
