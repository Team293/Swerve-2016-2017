#include <Servo.h>

int potPin = 2;    // select the input pin for the potentiometer   // select the pin for the LED
int value;
float angle;
Servo servo;
int goal = 122;
int error;
int command;

void setup() {
  servo.attach(10);
  Serial.begin (9600);
  Serial.print("test!");
  //goal = Serial.read();
}

void loop() {

  if(Serial.available()>0){
      goal = Serial.parseInt();
    } 
  value = analogRead(potPin);
  angle = map(value, 40, 970, 0, 360);
  servo.write(110);
  error = goal - angle;
/*
  if() > 5){
  if((goal < 180) && (angle > 180) {
    if (360 - angle) + goal < (goal - angle) {
      servo.write(104);
    }
    else{
      servo.write(84)
    }
  }  
   }*/

  if(abs(error) > 180){
    error = error - 360;
  }
  servo.write(94-error);
  
  /*
  if( (error > 5 && error < 180) || (error > -360 && error < -180) ){
    servo.write(84);
  }else if( (error < -5 && error > -180) || (error > 180 && error < 360) ){
    servo.write(104);
  }else{
    servo.write(94);
  }
  */ 
   
  //command = error*.3 + 90;
  //servo.write(command);
  Serial.print(error);
  Serial.print(" and ");
  Serial.println(angle);
}
