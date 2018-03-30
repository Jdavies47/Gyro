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
boolean state;
long pulseCount = 0;
const int aSize = 10;
int oldest = aSize;
long timer;

int dataArray[aSize];
unsigned long timeArray[aSize];

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  delay (100);
  timer = millis();

  Serial.println(timer);

  /*for (int i=0;i<aSize;i++){
    dataArray[i]=2;
    timeArray[i]=millis();
  }*/

  analogRead(A2);
  delay(2000);

  digitalWrite(LED_BUILTIN, LOW);
  long tot = 0;
  Serial.println("Finding offset");
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
  int sensorValue = analogRead(A2) - offset - 6;
  if (sensorValue < 0) {
    if (state == true) {
      state = false;
    }
    sensorValue = 0;
  } 
  else {
    if ((state == false) && (sensorValue > 5)) {
      if (counter == (aSize)){
        counter = 0;
        oldest = aSize;
        double cycles = (aSize*1000)/((millis()-timer));
        cycles *= 60;
        //Serial.println((millis()-timer));
        //Serial.println(cycles);
        timer = millis();
      }
      else{
        oldest = counter+1;
      }
      dataArray[counter] = pulseCount;
      timeArray[counter] = millis();
      
      state = true;
      pulseCount++;

      long numData = dataArray[counter] - dataArray[oldest];
      long timeTaken = timeArray[counter] - timeArray[oldest];
      long cyclesPerSecond = numData/timeTaken;
      counter++;
      //Serial.println(pulseCount);
      //Serial.println(counter);
      //Serial.println(millis());
      //Serial.println(timeArray[counter]);
      //Serial.println(timeArray[oldest]);
    }
  }
 

  //Serial.println(pulseCount);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(sensorValue);
  
}
