#include <Servo.h>

int potPin = 2;    // select the input pin for the potentiometer   // select the pin for the LED
int value;
float angle;//actual measured sensor angle
Servo angleMotor;
Servo driveMotor;
int goal = 122;
int error;
int command;

boolean high;

boolean newData = false;

char temp;
int iterator = 0;

String getVelocity = "0";
String getAngle = "0";

int setVelocity = 100;
int setAngle = 100;
int moduleNumber = 4; //from 1 to 4
double testTime;

void setup() {
  pinMode(12, OUTPUT);
  angleMotor.attach(10);
  driveMotor.attach(11);
  Serial.begin (115200);
}

void loop() {
  value = analogRead(potPin);
   
if (Serial.available() > 0) {
    temp = Serial.read(); //If there's a value available, then read it in as a character converted into ASCII readable form from the byte.
    digitalWrite(12, HIGH);
    if (temp == '!') {
       
   //   Serial.print("Got !: ");
     // Serial.println(millis());
      iterator = 1; //then we're at the start of it
      getAngle = "";
      getVelocity = "";
    }
    else if (temp == ',') { //at each comma we hit, we are now at the next value
      iterator = iterator + 1;
   //   Serial.print("Got , ");
    //  Serial.println(millis());
      if (iterator == moduleNumber * 2) {
        setVelocity=getVelocity.toInt();
      }
      if (iterator == moduleNumber * 2 + 1) {
        setAngle = getAngle.toInt();
      }
    }
    else if (temp != ',' && temp != '!') {
     // Serial.print("Got Number: ");
      //Serial.println(millis());
      if (iterator == moduleNumber * 2 - 1) { //if its a value we need then it will save those characters into the getVelocity, Angle etc.
        getVelocity += temp;
      }
      if (iterator == moduleNumber * 2) {
        getAngle += temp;
      }
    }
}
//  Serial.print("Setting Value:   ");
if (millis()-testTime>25){
  angle = map(value, 40, 970, 0, 360);
  error = angle - setAngle;

  if (error > 180) {
    error = error - 360;
  }
  if (error < -180) {
    error = error + 360;
  }
  //double printing=(millis()-testTime);
  //Serial.println(String(printing));
  angleMotor.write(93 - (error)*.5);
  driveMotor.write(93+setVelocity*1.5);
  //testTime=millis();
  }


  /* Serial.print("Setpoint Angle:");
    Serial.print(setAngle);
    Serial.print("    error:");
    Serial.print(error);
    Serial.print("   angle:");
    Serial.println(angle);*/
}

