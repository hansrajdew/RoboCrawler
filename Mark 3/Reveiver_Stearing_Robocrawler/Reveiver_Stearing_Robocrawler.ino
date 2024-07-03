#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
 
#define m11 3
#define m12 4

#define enb A0

Servo myservo;
 
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int receivedData[2]; 
//char receivedData[10]="",x_data[5]="",y_data[5]="";
int  xAxis=0, yAxis=0;
 
void setup() {
  Serial.begin(9600);
 
  myservo.attach(9);
 
  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  pinMode(enb,OUTPUT);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}
 
void loop() {
 
  while (radio.available()==0) {}   // If the NRF240L01 module received data
    radio.read(&receivedData, sizeof(receivedData)); // Read the data and put it into character array
  Serial.print(receivedData[0]);
 Serial.print("  ");
 Serial.print(receivedData[1]);
  // int n1=(int)receivedData[0]-48,n2=(int)receivedData[4]-48;
 
  //   for(int count=0;count<3;count++){
  //     n1=10*n1+(int)receivedData[count+1]-48;
  //     n2=10*n2+(int)receivedData[count+5]-48;
  //    }
 int n1=receivedData[0];
 int n2=receivedData[1];
xAxis=map(n1,0,1023,45,135);
yAxis=map(n2,0,1023,0,510);
 
      Serial.print(" ");
      Serial.print(yAxis);
  
 
myservo.write(xAxis);
 
  if(yAxis>255){
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
 
   yAxis=yAxis-255-100;
    analogWrite(enb,yAxis);
    
    }
 
  else{
    digitalWrite(m11,LOW);
    digitalWrite(m12,HIGH);
    
 yAxis=255-yAxis-100;
    analogWrite(enb,yAxis); 
    }  
 
    delay(100);
}
