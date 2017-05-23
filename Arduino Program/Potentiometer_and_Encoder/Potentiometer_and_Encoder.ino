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
  Serial.begin (115200);
  Serial.print("test!");
  goal = Serial.read();
}

void loop() {

  if(Serial.available()>0){
      goal = Serial.parseInt();
    } 
  value = analogRead(potPin);
  angle = map(value, 40, 970, 0, 360);

  
  error = goal - angle;

if(error<360){
    error=error+360;
}
if(error>360){
    error=error-360;
}





  servo.write(94-(error)*.5);
 

  Serial.print("error:");
  Serial.print(error);
  Serial.print("   angle:");
  Serial.println(angle);
}
