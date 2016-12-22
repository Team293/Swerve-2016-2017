#include <Servo.h>

int s;
Servo speedMotor;
 int encoder0PinA = 3;
 int encoder0PinB = 4;
 int n = LOW;
    volatile int encoder0Pos = 0;
   volatile int encoder0PinALast = LOW;
void setup() {
  speedMotor.attach(9);
  Serial.begin(9600);
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);
   attachInterrupt(0, changey, CHANGE);
   speedMotor.write(150);
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
  delay(1000);
  Serial.print(millis());
  Serial.println();
  Serial.println(encoder0Pos);
}

