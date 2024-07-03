#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
 
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
 
 
int xAxis, yAxis;
char send_arr[9],x_arr[5],y_arr[5],x_arr1[5],y_arr1[5];
 
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}
 
void loop() {
  //analogWrite(A0,yAxis);
  xAxis = analogRead(A0); // Read Joysticks X-axis
  yAxis = analogRead(A1); // Read Joysticks Y-axis
 int data[2]={xAxis,yAxis};
 radio.write(data,sizeof(data));
 Serial.print(data[0]);
 Serial.print("  ");
 Serial.println(data[1]);
    //xAxis=map(xAxis, 0, 1023, 0, 99);
    //yAxis=map(yAxis, 0, 1023, 0, 99);
//   for(int count=0,n1=xAxis, n2=yAxis;count<4;count++){
//     x_arr1[count]='0'+(n1%10);
//     y_arr1[count]='0'+(n2%10);
//     n1=n1/10;
//     n2=n2/10;
//     }
// for(int count=0;count<4;count++){
//   x_arr[count]=x_arr1[3-count];
//   y_arr[count]=y_arr1[3-count];
//   }
//   for(int count=0;count<4;count++){
//     send_arr[count]=x_arr[count];
//     send_arr[count+4]=y_arr[count];
//     }
// //Serial.println(send_arr);
//   radio.write(send_arr, sizeof(send_arr));
//   Serial.println(send_arr);
  //radio.write("05020497", 8);  
/* xAxis.toCharArray(xyData, 5); // Put the String (X Value) into a character array
  radio.write(&xyData, sizeof(xyData)); // Send the array data (X value) to the other NRF24L01 modile
  // Y value
  delay(5);
  yAxis.toCharArray(xyData, 5);
  radio.write(&xyData, sizeof(xyData));*/
  // X value
  //xAxis.toCharArray(xyData, 5); // Put the String (X Value) into a character array
  //radio.write(&xyData, sizeof(xyData)); // Send the array data (X value) to the other NRF24L01 modile
  // Y value
  //yAxis.toCharArray(xyData, 5);
  //radio.write(&xyData, sizeof(xyData));

  delay(10);
}
