#include <Wire.h>
#include <SPI.h>
#include "RF24.h"
//#include "C:\Users\pandejo\Documents\Arduino\! przechowalnia\przechowalnia2A_6.08.2016\storeStruct.h"

#define DEBUG
#define LICZBA_CZUJNIKOW 4
//void setup() {
//  Wire.begin(); // join i2c bus (address optional for master)
//}
//
//byte x = 0;
//
//void loop() {
//  Wire.beginTransmission(8); // transmit to device #8
//  Wire.write("x is ");        // sends five bytes
//  Wire.write(x);              // sends one byte
//  Wire.endTransmission();    // stop transmitting
//
//  x++;
//  delay(500);
//}


struct RF_packet {
char id;
float temp;
float vol;
unsigned int packets_send;
} data,data1;


RF_packet sensorsList[LICZBA_CZUJNIKOW];
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(8,9);
byte addresses[][6] = {"Trunk","Leaf_"};



void setup() {
  Serial.begin(9600);  // start serial for output  
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.setPALevel(RF24_PA_MAX); 
  radio.startListening();  
}

void loop() {
    if( radio.available()){
                                                                    // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &data, sizeof(RF_packet) );             // Get the payload
      }   

         Serial.write((char*)&data,  sizeof(RF_packet));

           
      Serial.print(F(" RECIEVED: "));      
      Serial.print((int)data.id);
      Serial.print(F(" temp: "));
      Serial.print(data.temp);  
      Serial.print(F(" packets_send: "));
      Serial.print(data.packets_send);       
      Serial.print(F(" vol: "));
      Serial.println(data.vol); 
//  
//       writeUpData();
//      
//      Serial.print(F(" WRITTENUP: "));      
//      Serial.print((int)data1.id);
//      Serial.print(F(" temp: "));
//      Serial.print(data1.temp);  
//      Serial.print(F(" packets_send: "));
//      Serial.print(data1.packets_send);       
//      Serial.print(F(" vol: "));
//      Serial.println(data1.vol); 
  }

}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
//  Wire.write("Helloo");

  Wire.write((char*)sensorsList,2*sizeof(RF_packet)); // respond with message of 6 bytes
//  // as expected by master
//      Serial.print(F(" SENDED: "));      
//      Serial.print((int)data.id);
//      Serial.print(F(" temp: "));
//      Serial.print(data.temp);  
//      Serial.print(F(" packets_send: "));
//      Serial.print(data.packets_send);       
//      Serial.print(F(" vol: "));
//      Serial.println(data.vol); 
}

void writeUpData()
{
  for (unsigned int t=0; t<sizeof(RF_packet); t++)
   *(((char*)&data1 + t))=*(((char*)&data + t));

 // sensorsList[data.id]=data;
//  printData() ; 
}

void printData()
{
  for (int i=0;i<LICZBA_CZUJNIKOW;i++)
    {
      Serial.print(F(" PRINTING AFTER WRITING: "));      
      Serial.print((int)sensorsList[i].id);
      Serial.print(F(" temp: "));
      Serial.print(sensorsList[i].temp);  
      Serial.print(F(" packets_send: "));
      Serial.print(sensorsList[i].packets_send);       
      Serial.print(F(" vol: "));
      Serial.println(sensorsList[i].vol);       
      }
}

