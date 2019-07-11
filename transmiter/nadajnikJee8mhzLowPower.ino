//minimalne napiecie zaislania 2.40V - ponizej nie dziala ds18b20

//#define DEBUG
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#include <JeeLib.h> // Low power functions library

ISR(WDT_vect) { Sleepy::watchdogEvent(); } // Setup the watchdog

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
// pin dla ds18b20
#define ONE_WIRE_BUS A0
#define OKNO 60000  //10 min
//#define GREEN_PIN A5
#define RED_PIN A5
//#define LISTENTIME 2000
//#define REFERENCE_VOLTAGE 1.1
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

struct RF_packet {
char id;
float temp;
float vol;
unsigned int packets_send;
} data = {
3,0,0,0
};
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(9,10);
/**********************************************************/

byte addresses[][6] = {"Trunk","Leaf_"};

unsigned long send_time=0;
int i;

void setup() {
  
 #ifdef DEBUG 
  Serial.begin(9600);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
 #endif  
  radio.begin();
//  pinMode(GREEN_PIN, OUTPUT);
//  digitalWrite(GREEN_PIN,LOW);

  pinMode(RED_PIN, OUTPUT);
  digitalWrite(RED_PIN,LOW);
    
  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses

    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);

  
  // Start the radio listening for data
  radio.stopListening();  
 

  analogReference(INTERNAL);

  flash(RED_PIN,2,100);
}

void loop() {
//

/****************** Temperature routines ***************************/  

    if(millis()-send_time>OKNO)
    {  
    //data.vol=(analogRead(VOL_PIN)*3/(float)1023)*(3.12);  
    //  data.vol=analogRead(VOL_PIN);
    data.vol=(float)readVcc()/1000;
    sensors.requestTemperaturesByIndex(0);
   
    data.temp= sensors.getTempCByIndex(0);
    data.packets_send++;    
     // flash(RED_PIN,2,40);
                                  // First, stop listening so we can talk.
      
    #ifdef DEBUG    
      Serial.print(F("Now sending ID:"));
      Serial.print((int)data.id);    
      Serial.print(F(" temp:"));
      Serial.print(data.temp);    
      Serial.print(F(" num of packets:"));
      Serial.print(data.packets_send);      
      Serial.print(F(" and voltage:"));
      Serial.println(data.vol);        
  
    #endif
     
     radio.write( &data, sizeof(RF_packet) );
     send_time=    millis()+random(1000);
     flash(RED_PIN,2,40);
     
    }
    #ifdef DEBUG
       Serial.println(F("going to sleep"));  
       sleep(3000);        
    #else
       sleep(60000);
    #endif   

} // Loop

void sleep(int miliseconds){
    radio.powerDown();
    Sleepy::loseSomeTime(miliseconds);
    radio.powerUp();   
}

void flash(char pin,char times,unsigned int f_time)
{
  for(int i=0;i<times;i++)
  {
    digitalWrite (pin, HIGH);
    delay (f_time);  
    digitalWrite (pin, LOW);
    delay (f_time);  
  }
}


long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}

