/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(107);
  delay(2000);
}

void loop() {
<<<<<<< HEAD
  
=======

  myservo.write(0);
  delay(2000);
  myservo.write(180);
  delay(2000);
  //int sensorValue = analogRead(A0);

  //int posVal = map(sensorValue, 0, 1023, 0, 180);
  
  //myservo.write(posVal);
  //delay(15);
>>>>>>> 65eddf34f33b7568ce76619148540e4488a81381
 
}

