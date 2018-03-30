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

int16_t ax, ay, az, gx, gy, gz;
float mean_ax,mean_ay,mean_az,mean_gx,mean_gy,mean_gz;

int samplesize = 50;

void setup() {
  //Wire.begin();
  //TWBR = 24;

  //Initialise serial communication
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

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
  Serial.println("Testing the file was created");
  if (datalog) {
    Serial.print("Created File: ");
    Serial.println (fullfilename);
  }
  else
  {
    Serial.println("FAILED");
    return;
  }
  datalog.close();
  // Dont close, as we can use the file handle later and we dont need to open any more

  //Initialise the MPU board
  accelgyro.initialize();
  
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  delay(1000);

  // If offsets are known, put them in here
  accelgyro.setXAccelOffset(-2451);
  accelgyro.setYAccelOffset(137);
  accelgyro.setZAccelOffset(1817);

  accelgyro.setXGyroOffset(27);
  accelgyro.setYGyroOffset(-47);
  accelgyro.setZGyroOffset(-3);

  int time = millis(); // Takes time just before measurements start.
  int measuretime;
  
  while (measuretime < 10000){ // This is my main work loop, avoids global scoping.
    takeMeasure();

    float angle = rawToAngle(mean_ax);
  
    Serial.print(angle);
    Serial.print("\t");
    Serial.print(measuretime);
    Serial.print("\n"); 
    datalog = SD.open(fullfilename, FILE_WRITE);
    //Going to record the data in csv.
    datalog.print(measuretime);
    datalog.print(", ");
    datalog.print(angle);
    datalog.print(",\n");
    datalog.close();

    measuretime = millis() - time;
  }

  return;
}
void loop(){
  
}
void takeMeasure(){
  //Use a delay to add 1ms of time, then take 100 measures
  //So taking an average measurement over 0.1 seconds
  long i=0,buff_ax=0;

  while (i<samplesize){
     //Take a reading
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    if (i>0 && i<=(samplesize)){
      buff_ax=buff_ax+ax;
    }
    if (i==(samplesize-1)){
      mean_ax=buff_ax/samplesize;
    }
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

float rawToAngle(float raw){
  return (raw *(0.00549316)); //The ratio to raw value to degree
}

