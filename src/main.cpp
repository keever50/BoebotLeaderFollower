#include <Arduino.h>
#include <rf_receive.h>


void setup() {
  Serial.begin(9600);
  rf_recieve_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(rf_receive_data_ready(1))
  {
    for(int i = 0; i<10; i++)
    {
      Serial.println(rf_receive_data_buffer(i));
    }
    Serial.println("STOP");
  }
  delay(500);
  Serial.println("Listening");


}
