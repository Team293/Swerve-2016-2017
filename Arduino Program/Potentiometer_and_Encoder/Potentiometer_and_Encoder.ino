#include <Servo.h>

int potPin = 2;    // select the input pin for the potentiometer   // select the pin for the LED
int value;
float angle;
Servo angleMotor;
int goalAngle = 122;
int goalSpeed = 10;
int angleError;
int speedError;
int command;
Servo speedMotor;
 int speedM;
 int speedPower = 0;
 int encoder0PinA = 3;
 int encoder0PinB = 4;
 volatile int encoder0Pos = 0;
 volatile int encoder0PinALast = LOW;
 int n = LOW;
long lastChange = 0;
long timeNow = 0;
 int lastPos = 0;

void setup() {
   angleMotor.attach(10);
   speedMotor.attach(9);
   Serial.begin (9600);
   Serial.print("test!");
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);
   attachInterrupt(0, changey, CHANGE);
}

void changey(){
  n = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder0PinB) == LOW) {
       encoder0Pos--;
     } else {
       encoder0Pos++;
     }
   }
  encoder0PinALast = n;   
}

void loop() {
  //speedMotor.write(110);
  if(Serial.available()>0){
      //goalAngle = Serial.parseInt();
      goalSpeed = Serial.parseInt();
  } 
  value = analogRead(potPin);
  angle = map(value, 40, 970, 0, 360);
  angleError = goalAngle - angle;
  if (abs(angleError) > 180){
    angleError = angleError - 360;
  }
  //angleMotor.write(94-angleError);

  //Get Speed
  timeNow = millis();
  long timedif = timeNow-lastChange;
    //Serial.println(encoder0Pos);
  if (timedif > 100){
      Serial.print(timedif);
      Serial.print("      ");
      speedM = encoder0Pos-lastPos;
      Serial.println(speedM);
 
      speedError = goalSpeed - speedM;
      speedPower -= (speedError/5);
      speedMotor.write(speedPower);
      Serial.print("        ");
      Serial.println(speedPower);
      lastChange = timeNow;
      lastPos = encoder0Pos;
   }
}
