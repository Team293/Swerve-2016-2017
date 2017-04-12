#include <Servo.h>


int potPin = 2;    // select the input pin for the potentiometer
int value;
float angle;

Servo angleMotor;
Servo speedMotor;

int goalAngle = 122;
int goalSpeed = 10;

int angleError;
int speedError;
int command;

 int speedM;
 int speedPower = 0;
 int encoder0PinA = 3;
 int encoder0PinB = 2;
 volatile int encoder0Pos = 0;
 volatile int encoder0PinALast = LOW;
 int n = LOW;
long lastChange = 0;
long timeNow = 0;
 int lastPos = 0;
 float rpm; 

void setup() {
   angleMotor.attach(10);
   speedMotor.attach(9);
   Serial.begin (9600);
   Serial.print("test!");
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);
   attachInterrupt(digitalPinToInterrupt(3), changey, CHANGE);
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
  angleMotor.write(94-angleError); //this is 0-180 and 94 is approximately a neutral frc style 0

  //Get Speed
  timeNow = millis();
  long timedif = timeNow-lastChange;
    Serial.print("Current encoder reading!: ");
    Serial.print(encoder0Pos);
    Serial.println();
  if (timedif > 100){
      Serial.print("millisecond difference: ");
      Serial.print(timedif);
      Serial.println(); 
      speedM = encoder0Pos-lastPos;
      Serial.print("Change in position: ");
      Serial.print(speedM);
      Serial.println(); 
      speedError = goalSpeed - speedM;
      speedPower -= (speedError/5);
      speedMotor.write(speedPower);
      Serial.print("speedPower: ");
      Serial.print(speedPower);
      lastChange = timeNow;
      lastPos = encoder0Pos;
   }
   rpm = (speedM/256)/(timedif/60000);
   Serial.println(rpm);
}
