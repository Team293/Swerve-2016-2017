
 /*    Read Quadrature Encoder
  * Connect Encoder to Pins encoder0PinA, encoder0PinB, and +5V.
  *
  * Sketch by max wolf / www.meso.net
  * v. 0.1 - very basic functions - mw 20061220
  *
  */  

 int val;
 int potPin = 2;
 int encoder0PinA = 3;
 int encoder0PinB = 4;
 int encoder0Pos = 0;
 int encoder0PinALast = LOW;
 int n = LOW;
long lastChange = 0;
long timeNow = 0;
 int lastPos = 0;
 int rpm;

 void setup() { 
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);
   Serial.begin (9600);
   Serial.print("test!");
 } 

 void loop() { 
   n = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder0PinB) == LOW) {
       encoder0Pos--;
     } else {
       encoder0Pos++;
     }
   }
    timeNow = millis();
    long timedif = timeNow-lastChange;
    if(timedif > 1000){
    lastChange = timeNow;
    rpm = (60*(encoder0Pos-lastPos))/(360.0)
    Serial.println(rpm);
    lastPos = encoder0Pos;
    }
   encoder0PinALast = n;
 } 
