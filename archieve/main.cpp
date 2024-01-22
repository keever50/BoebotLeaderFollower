// #include <Arduino.h>
// #include <rf_receive2.h>

// void setup() {
//   Serial.begin(115200);
//   rf_receive_init();

// }

// void loop() {
//   // put your main code here, to run repeatedly:

//   if(rf_receive_get_data_ready(0))
//   {
//     for(int i=0;i<8;i++)
//     {
//       float bit = rf_receive_get_data(i);
//       if(bit<0.5)
//       {
//         Serial.print("1");
//       }else{
//         Serial.print("0");
//       }
      
//     }
//     Serial.println("");
//     for(int i=0;i<8;i++)
//     {
//       float bit = rf_receive_get_data(i);
//       Serial.print(bit);
//       Serial.print(" ");
      
//     }
//     Serial.println("");

//     rf_receive_get_data_ready(1);
//   }
//   delay(50);
// }


// // #include <Arduino.h>
// // #include <rf_transmit.h>

// // void setup()
// // {
// //   pinMode(trans_pin, OUTPUT);
// // }
// // void loop()
// // {

// //   char bits[] = {1,1,0,0,1,0,1,0};
// //   for(int i=0; i<10;i++)
// //   {
// //     transmit_binary(bits, sizeof(bits)); 
// //     delay(50); 
// //   }


// //   delay(20000);
// // }
