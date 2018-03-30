/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
int counter=0;
long offset;
boolean state; //Used to prevent double counting of peaks
long pulseCount = 0;
const int aSize = 10; //Find the RPM over every 10 peaks detected.
long timer;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  delay (100);
  timer = millis(); //Give time a value for system on time.

  Serial.println(timer);

  analogRead(A2); //Start measurement to eliminate intial peak measurement.
  delay(2000);

  digitalWrite(LED_BUILTIN, LOW); // Turn off the IR LED
  long tot = 0;
  Serial.println("Finding offset"); // Find the background value for the current system
  delay(1000);
  for (int i = 0; i < 1000; i++) {
    tot += analogRead(A2);
    delay(1);
  }
  offset = tot / 1000;
  Serial.println("The average value: ");
  Serial.println(offset);
  delay(3000);
}

// the loop function runs over and over again forever
void loop() {
  //Serial.println(counter);
  int sensorValue = analogRead(A2) - offset - 6; // Reduce the signal to a near zero value
  if (sensorValue < 0) {
    if (state == true) { //If in a peak detected range, but measureless than threshold, peak finished.
      state = false;
    }
    sensorValue = 0; // Any value less that zero, set to zero to procue a clean off signal
  } 
  else {
    if ((state == false) && (sensorValue > 5)) { //Trigger if a peak detected/ significant rise in intensity
      if (counter == (aSize)){
        counter = 0; //reset counter
        double cycles = (aSize*1000)/((millis()-timer));
        cycles *= 60; //Convert to rpm, which the hand held device meausres in
        Serial.println(cycles);
        timer = millis();
      } 
      state = true; //Change from false
      pulseCount++; //Threshold found
      counter++;
    }
  }

  digitalWrite(LED_BUILTIN, HIGH);
  //Serial.println(sensorValue); //Used for debugging purposes
  
}
