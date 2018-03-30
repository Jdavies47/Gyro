// Basic Functionality Test Script

#include <Servo.h>

Servo servoControlSignal;

int pos = 90;
int gateSignal = 3;
int speed = 255;

// the setup routine runs once when you press reset:
void setup(){
  servoControlSignal.attach(9);

  // MOSFET gate pin on pin ~3
  analogWrite(gateSignal, speed);
  //Wait for the flywheel to gain some speed
  delay(30000);

  //Set the servo back to horizontal
  servoControlSignal.write(110);
  delay(2000);
  servoControlSignal.write(70);
  delay(2000);
  servoControlSignal.write(pos);
  delay(2000);
  
  pinMode(gateSignal, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  

}

// the loop routine runs over and over again forever:
void loop() {
  for(pos = 70; pos <= 110; pos += 1) // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    servoControlSignal.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                     // waits 15ms for the servo to reach the position
  }
  for(pos = 110; pos>=70; pos-=1)     // goes from 180 degrees to 0 degrees
  {
    servoControlSignal.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  // print out the value you read:
  //analogWrite(gateSignal, speed);

}
