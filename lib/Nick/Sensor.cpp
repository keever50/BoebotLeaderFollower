 #include <Arduino.h>
 const int Ir_Sensor = 8;

 void setup()
 {
   Serial.begin(9600);
   pinMode(Ir_Sensor, INPUT);
   Serial.print("Start uitlezen\n");
 }

 void loop()
 {
  
 }
