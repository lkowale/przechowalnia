#ifndef Skecja_h
#define Sekcja_h

#include "Okno.h"
#include "StoreStruct.h"

class Sekcja{

  public:
  Sekcja(char SSRpin_,char id_,unsigned long _czasOtwierania,StoreStruct *storage_);  
  void proces(float tZ,float tW_);

  void wlaczWentylator();
  void wylaczWentylator();  
  void awariaZasilania();
  OknoPWM wywietrznikLewy,wywietrznikPrawy;
  OknoCzerpnia czerpnia;

  int SSRpin,stan,id;
  bool trybAuto,zasilanie;
  StoreStruct *storage;
  float *tZadana,tW;
  unsigned long czasStart,czasOtwierania;
  
};

#endif
