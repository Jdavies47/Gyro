
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards



void setup() {

  int pos = 1520; // variable to store the servo position
  int state = 1;
  
  Serial.begin(9600);
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  /*while (true){
    myservo.write(pos);
    Serial.println(pos);
    Serial.print("The state is ");
    Serial.println(state);
    
    if (state == 1){
      pos = pos + 1;
    }
    if (state == 2){
      pos = pos -1;
    }
    if (pos == 1533){
      state = 2;
    }
    if (pos == 1528){
      state = 1;
    }
    delay(500);
  }*/
    myservo.write(1520);
  //delay(300000);
  //myservo.detach();
}

void loop() {/*
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }*/
}

