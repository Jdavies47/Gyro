void setup() {

  int pos = 1520; // variable to store the pin PWM period
  int state = 1;
  
  Serial.begin(9600);
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  while (true){
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
    if (pos == 1533){ // THe upper limit
      state = 2;
    }
    if (pos == 1528){ // The lower limit
      state = 1;
    }
    delay(500);
  }

}

void loop() {)
