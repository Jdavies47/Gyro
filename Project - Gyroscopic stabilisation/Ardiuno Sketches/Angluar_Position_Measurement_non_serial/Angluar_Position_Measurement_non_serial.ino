/* Angular Position Measurement system
This sketch needs to take measured the measured angle from
the MPU6050 board and store it on the SD card in a new file
each time the system is started.

The MPUboard need to have offsets to record an accurate measure
of the angle, but these will be finalised and redone once the board
is mounted on the frame.
*/
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <SPI.h>
#include <SD.h>

File datalog;
File root;

MPU6050 accelgyro(0x68);

int16_t rawax, raway, rawaz, gx, gy, gz;
float mean_ax,mean_ay,mean_az,mean_gx,mean_gy,mean_gz;
const int bufferSize = 20;
int samplesize = 1;
int nextRollingAverage;
int pwmDifferBuff1[bufferSize];

void setup() {

  for (int i=0; i<bufferSize; ++i){ //Fills the buffer full of stationary value (i.e starts in equib)
    pwmDifferBuff1[i] = 0;
  }
  //Wire.begin();
  //TWBR = 24;
  pinMode(8, OUTPUT);
  digitalWrite(8,HIGH);
  delay(1000);
  if (!SD.begin(4)) {
    digitalWrite(8,LOW);
    return;
  }
  
  root = SD.open("/");

  //Find the number of previous datalogs for names sake.
  int fh = numberOfFiles(root);
  root.close();

  // Create the file name from exsisting files.
  String filename = "Data-";
  filename += fh;
  String fullfilename = filename + ".csv";

  //Touch the file into exsistance
  datalog = SD.open(fullfilename, FILE_WRITE);
  if (datalog) {
    delay(1);
  }
  else
  {
    digitalWrite(8,LOW);
    return;
  }
  datalog.close();
  // Dont close, as we can use the file handle later and we dont need to open any more

  //Initialise the MPU board
  
  accelgyro.initialize();
  
  
  delay(1000);

  // If offsets are known, put them in here
  accelgyro.setXAccelOffset(-2314);
  accelgyro.setYAccelOffset(178);
  accelgyro.setZAccelOffset(1809);

  accelgyro.setXGyroOffset(25);
  accelgyro.setYGyroOffset(-43);
  accelgyro.setZGyroOffset(3);

  accelgyro.setDLPFMode(6);
  accelgyro.setDHPFMode(4);
  
  int time = millis(); // Takes time just before measurements start.
  int measuretime=0;
  digitalWrite(8,LOW);
  delay(500);
  digitalWrite(8,HIGH);
  delay(500);
  digitalWrite(8,LOW);
  delay(500);
  digitalWrite(8,HIGH);
  delay(500);
  digitalWrite(8,LOW);
  delay(500);
  digitalWrite(8,HIGH);
  while (measuretime < 30000){ // This is my main work loop, avoids global scoping.
    if(nextRollingAverage >= bufferSize){
      nextRollingAverage = 0; //Reset back to the start of the buffer
    }        
    takeMeasure();

    pwmDifferBuff1[nextRollingAverage] = mean_ax;
    nextRollingAverage++;

    float angleRollAverage1 = 0;

    for (int i=0; i<bufferSize; ++i){
      angleRollAverage1 += pwmDifferBuff1[i];
    }
    angleRollAverage1 /= bufferSize;
     
    float angle = angleRollAverage1;
    float flywheelAngle1 = getAngle1();
    float flywheelAngle2 = getAngle2();
    if(angle>60){
      return;
    }
  
    datalog = SD.open(fullfilename, FILE_WRITE);
    //Going to record the data in csv.
    datalog.print(measuretime);
    datalog.print(", ");
    datalog.print(angle);
    datalog.print(", ");
    datalog.print(flywheelAngle1);
    datalog.print(", ");
    datalog.print(flywheelAngle2);
    datalog.print(",\n");
    datalog.close();

    measuretime = millis() - time;
  }
  digitalWrite(8,LOW);
  return;
}
void loop(){
  
}
void takeMeasure(){
  //Use a delay to add 1ms of time, then take 100 measures
  //So taking an average measurement over 0.1 seconds
  float i=0,buff_ax=0;

  while (i<samplesize){
     //Take a reading
    accelgyro.getMotion6(&rawax, &raway, &rawaz, &gx, &gy, &gz);

    //Serial.println(rawax);

    float ax = convertRawAcceleration(rawax);
    float ay = convertRawAcceleration(raway);
    float az = convertRawAcceleration(rawaz);

    float angle = pitch(ax,ay,az);
    mean_ax=angle;
    i++;
    delay(0.5);  
       
   }
   
}

int numberOfFiles(File dir){
  int fileCount = 0;
  while (true){
    File entry = dir.openNextFile();
    if (!entry){
      //Passed through all files.
      return fileCount;
    }
    fileCount++;
    entry.close();
  }
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float pitch(float ax, float ay, float az){
  float angle = atan((-ax)/az);
  //float angle = atan((-ay)/sqrt(ax*ax+az*az));
  return angle*57.2958;
}

float rawToAngle(float raw){
  return (raw *(0.00549316)); //The ratio to raw value to degree
}

float getAngle1(){
  int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);
  float angle = (sensorValue+1) * (27220/1024);
  return ((int)(angle/100)-87);
}
float getAngle2(){
  int sensorValue = analogRead(A1);
  //Serial.println(sensorValue);
  float angle = (sensorValue+1) * (21730/1024);
  return ((int)(angle/100)-110);
}

