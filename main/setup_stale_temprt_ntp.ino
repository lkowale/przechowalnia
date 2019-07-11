#include <EthernetUdp.h>
#include <TimeLib.h>
#include <Time.h>
//#include <NTPClient.h>
#include "Sekcja.h"

//#define DEBUG

 #ifdef DEBUG
   #define SZEROKSC_OKNA 10000 //10sek
   #define CZAS_OTWIERANIA_OKNA 6000 //dlugosc pracy silownikow otweirajacych 6sek
   #define CZAS_PODSWIETLENIA 100000 //100 sek
   #define POLACZ_CZEKAJ 10000// 10sek 
 #else 
   #define SZEROKSC_OKNA 600000 //10min   
   #define CZAS_OTWIERANIA_OKNA 120000//dlugosc pracy silownikow otweirajacych 2MIN
   #define CZAS_PODSWIETLENIA 100000
   #define POLACZ_CZEKAJ 10000  // 10sek 
 #endif
 

   #define CZUJNIK_ZASILANIA A8
   #define LICZBA_CZUJNIKOW 5
   #define SEKCJA0_SSR 8
   #define SEKCJA1_SSR 9

    char timeServer[] = "0.pl.pool.ntp.org";
  //char timeServer[] = "time.nist.gov"; // time.nist.gov NTP server
  //IPAddress timeServer(212, 244, 160, 67);  
  //IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov
  //IPAddress timeServer(94,154,96,7); //0.pl.pool.ntp.org [94.154.96.7]
  EthernetUDP Udp;
  unsigned int localPort = 8888;  
   
  unsigned long poczatek_okna,poczatek_laczenia;

  float tZ,tW1,tW2,wprowadzonaLiczba;

  char pozycjaMenu=1,iloscPozycjiMenu=6,stanMenu=0,stan_polaczenia=0;
  byte podswietlenie=0,podswietlenieTimer=0;
  RF_packet data_buffer;

/*
 struct RF_packet {
  unsigned int id;
  float temp;
  float vol;
  unsigned int packets_send;
  };
*/ 
  struct tempRemoteSensor {
  RF_packet data;
  unsigned int sekcja;
  unsigned long ostatniOdczyt;
} listaCzujnikow[LICZBA_CZUJNIKOW]={
    {{0,1,0,0},0,0},
    {{1,1,0,0},0,0},
    {{2,1,0,0},0,0},
    {{3,1,0,0},0,0},    
    {{4,1,0,0},0,0}      
  };

//struct StoreStruct {
//  // This is for mere detection if they are your settings
//  char version[4];
//  // The variables of your settings
//  float tZadana0,tZadana1,dtW,tG,dtZ,dtG;
//  } ;
  
  StoreStruct storage = {
  CONFIG_VERSION,
  // The default values
  3,3, 0.3,-3, 3, 0.5,
  };

  Sekcja sekcja0(SEKCJA0_SSR,0,CZAS_OTWIERANIA_OKNA,&storage),sekcja1(SEKCJA1_SSR,1,CZAS_OTWIERANIA_OKNA,&storage);
  Sekcja *aktywnaSekcja;  

long loopctr=0;
long pocz_okna;
  
  void setup() {
  pocz_okna=millis();
  Serial.begin(9600);  
  loadConfig();
  sekcja0.tZadana=&storage.tZadana0;
  sekcja1.tZadana=&storage.tZadana1;
  aktywnaSekcja=&sekcja0;
  
  //void init(char in1_,char in2_,char pin_krancowki_);
  sekcja0.wywietrznikLewy.init(2,3,A8);
  sekcja0.wywietrznikPrawy.init(4,5,A9);
  sekcja0.czerpnia.init(7,6,A10,A11);
//  sekcja1.czerpnia.init(34,36,A12,A13);
//  sekcja1.wywietrznikLewy.init(38,39,A14);
//  sekcja1.wywietrznikPrawy.init(40,41,A15);
  
  Serial1.begin(9600);
  
  lcd.begin(16,2);   // Inicjalizacja LCD 2x16
  lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
  lcd.print("Uruchamianie...");
  
  pinMode(CZUJNIK_ZASILANIA,INPUT);
  pinMode(SEKCJA0_SSR,OUTPUT);  
  pinMode(SEKCJA1_SSR,OUTPUT);
  
  Ethernet.begin(mac,ip,dns_,gateway);  
  delay(500);
  
  lcd.clear();
  /*
   Udp.begin(localPort);
   setSyncProvider(getNtpTime); 
*/
  lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
  lcd.print("Adres IP: ");   
  lcd.setCursor(0,1);   
  lcd.print(Ethernet.localIP());   

   Udp.begin(localPort);

   setTime(0,0,00,1,1,2018);
   setSyncProvider(getNtpTime); 
   setSyncInterval(360);    // Set the number of
                               //  seconds between re-sync   
  /*
  Serial.print("IP: "); 
  Serial.println(Ethernet.localIP());
  */
  delay(2000);  

   poczatek_okna = millis();
//    podswietl();   

//  attachPinChangeInterrupt(23, przerwanie_key, RISING);  
//  attachPinChangeInterrupt(25, przerwanie_key, RISING); 
//  attachPinChangeInterrupt(27, przerwanie_key, RISING); 
//  attachPinChangeInterrupt(29, przerwanie_key, RISING); 
//  attachPinChangeInterrupt(31, przerwanie_key, RISING); 
//  attachPinChangeInterrupt(33, przerwanie_key, RISING); 
//  attachPinChangeInterrupt(35, przerwanie_key, RISING); 
//  attachPinChangeInterrupt(37, przerwanie_key, RISING); 
}

void getTemperature()
{
  float t1=0,t2=0;
  int t1n=0,t2n=0;
  
  for(int i=0;i<LICZBA_CZUJNIKOW;i++){
    if(listaCzujnikow[i].sekcja==0) 
        //licz do sredniej jesli ostatni odczyt(w sekundach) jest mlodszy niz 2*okno(w milisekundach - stad dzielenie prezz 1000) 
        if(listaCzujnikow[i].ostatniOdczyt+(2*SZEROKSC_OKNA/1000)>now())
        {
         t1=t1+listaCzujnikow[i].data.temp;
         t1n++;
        }

    else 
       if(listaCzujnikow[i].ostatniOdczyt+(2*SZEROKSC_OKNA/1000)>now())
        {
        t2=t2+listaCzujnikow[i].data.temp;
        t2n++;
        }
  }

  if(t1n) tW1=t1/t1n; else tW1=0;
  if(t2n) tW2=t2/t2n; else tW2=0; 

  //get tZ
      sensors.requestTemperaturesByIndex(0);
      tZ= sensors.getTempCByIndex(0);  
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  while (Udp.parsePacket() > 0) Udp.read(); // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 5000) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
//      return secsSince1900 - 2208988800UL + 2 * SECS_PER_HOUR;
      setSyncInterval(3600);
      return secsSince1900 - 2208988800UL ;      
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(char* address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
