#ifndef StoreStruct_h
#define StoreStruct_h

#include <EEPROM.h>

// ID of the settings block
#define CONFIG_VERSION "ks1"
// Tell it where to store your config data in EEPROM
#define CONFIG_START 0

struct StoreStruct {
  // This is for mere detection if they are your settings
  char version[4];
  // The variables of your settings
  float tZadana0,tZadana1,dtW,tG,dtZ,dtG;
  } ;

 struct RF_packet {
  char id;
  float temp;
  float vol;
  unsigned int packets_send;
  };
  
#endif
