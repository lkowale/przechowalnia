#include "Sekcja.h"


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

Sekcja::Sekcja(char SSRpin_, char id_, unsigned long _czasOtwierania,StoreStruct *storage_) {

  SSRpin = SSRpin_;
  id = id_;
  czasOtwierania = _czasOtwierania;
  pinMode(SSRpin, OUTPUT);
  digitalWrite(SSRpin, LOW);
  stan = 0;
  zasilanie=1;
  trybAuto = true;
  storage=storage_;
}

void Sekcja::proces(float tZ, float tW_) {
  tW = tW_;

 

  if (trybAuto) {                   ///tryb auto
    if ((stan == 0) &&
        (*tZadana < tW - storage->dtW) &&
        (storage->tG < tZ) &&
        (tZ + storage->dtZ < tW - storage->dtW)&&
        zasilanie) {
      stan = 1;
    }
    //otwieranie okna lewego
    if (stan == 1)
    {
      if ((wywietrznikLewy.stan == otwierane))
      {
        if (millis() - wywietrznikLewy.poczatekRuchuOkna > czasOtwierania)
        {
          wywietrznikLewy.zakoncz_otworz();
          stan = 2;
        }
        if(((*tZadana) > tW + storage->dtW)||(tZ + storage->dtZ > tW + storage->dtW)||(storage->tG - storage->dtG > tZ)) 
        {
          wywietrznikLewy.zakoncz_otworz();
          stan=8;
        }
      }
      else
        wywietrznikLewy.otworz();
    }
    //otwieranie okna prawego
    if (stan == 2)
    {
      if (wywietrznikPrawy.stan == otwierane)
      {
        if (millis() - wywietrznikPrawy.poczatekRuchuOkna > czasOtwierania)

        {
          wywietrznikPrawy.zakoncz_otworz();
          stan = 3;
        }
      }
      else
        wywietrznikPrawy.otworz();

    }
    //otwieranie dolu
    if (stan == 3)
    {
      if (czerpnia.stan == otwierane)
      {
        if (millis() - czerpnia.poczatekRuchuOkna > czasOtwierania)
        {
          czerpnia.zakoncz_otworz();
          stan = 4;
        }
      }
      else
        czerpnia.otworz();

    }
    //wentylowanie
    if (stan == 4)
    {

      //juz pracuje
      if (digitalRead(SSRpin) == HIGH)
      {
        //wylacz
        if (((*tZadana) > tW + storage->dtW)||(tZ + storage->dtZ > tW + storage->dtW)||(storage->tG - storage->dtG > tZ))
                      stan = 5;  

         
//          if(stan == 5)    
//          {      
//        Serial.print("digitalRead(SSRpin) == ");
//        Serial.print(digitalRead(SSRpin));
//        //Serial.print(" (*tZadana > tW + storage->dtW) ||  (tZ + storage->dtZ > tW + storage->dtW) || (storage->tG - storage->dtG > tZ) ");
//       // Serial.print((*tZadana > tW + storage->dtW) ||  (tZ + storage->dtZ > tW + storage->dtW) || (storage->tG - storage->dtG > tZ));
//        Serial.print(" *tZadana ");
//        Serial.print(*tZadana);       
//        Serial.print(" tW ");
//        Serial.print(tW);    
//        Serial.print(" storage->dtW ");
//        Serial.print(storage->dtW);       
//        Serial.print(" tW ");
//        Serial.print(tW);    
//        Serial.print(" (*tZadana > tW + storage->dtW) ");
//        Serial.println((*tZadana > tW + storage->dtW));
////        Serial.print(" (*tZadana > tW + storage->dtW) ");
////        Serial.print((*tZadana > tW + storage->dtW));        
////        Serial.print(" (tZ + storage->dtZ > tW + storage->dtW) ");
////        Serial.print((tZ + storage->dtZ > tW + storage->dtW));
////        Serial.print(" (storage->tG - storage->dtG > tZ)) ");
////        Serial.println(storage->tG - storage->dtG > tZ);
//         }

      }
      else //niepracuje, wlacz wentyl
      {
        wlaczWentylator();
      }
    }
    //wylacz wentylator
    if (stan == 5)
    {
      wylaczWentylator();
      stan = 6;
    }
    //zamykanie dolu
    if (stan == 6)
    {
      if (czerpnia.stan == zamykane)
      {
        if (millis() - czerpnia.poczatekRuchuOkna > czasOtwierania)
        {
          czerpnia.zakoncz_zamknij();
          stan = 7;
        }
      }
      else
        czerpnia.zamknij();

    }
    //zamykanie okna prawego
    if (stan == 7)
    {
      if (wywietrznikPrawy.stan == zamykane)
      {
        if (millis() - wywietrznikPrawy.poczatekRuchuOkna > czasOtwierania)
        {
          wywietrznikPrawy.zakoncz_zamknij();
          stan = 8;
        }
      }
      else
        wywietrznikPrawy.zamknij();
    }
    //zamykanie okna lewego
    if (stan == 8)
    {
      if (wywietrznikLewy.stan == zamykane)
      {
        if (millis() - wywietrznikLewy.poczatekRuchuOkna > czasOtwierania)
        {
          wywietrznikLewy.zakoncz_zamknij();
          stan = 9;
        }
      }
      else
        wywietrznikLewy.zamknij();
    }
   // czy jest zasilanie 
   if(stan==9)
   {
    if(zasilanie) stan=0;
   }
    
  }
  else                              ///tryb reczny
  {
    if ((wywietrznikLewy.stan == otwierane) && (millis() - wywietrznikLewy.poczatekRuchuOkna > czasOtwierania))           wywietrznikLewy.zakoncz_otworz();
    if ((wywietrznikLewy.stan == zamykane) && (millis() - wywietrznikLewy.poczatekRuchuOkna > czasOtwierania))           wywietrznikLewy.zakoncz_zamknij();
    if ((wywietrznikPrawy.stan == otwierane) && (millis() - wywietrznikPrawy.poczatekRuchuOkna > czasOtwierania))           wywietrznikPrawy.zakoncz_otworz();
    if ((wywietrznikPrawy.stan == zamykane) && (millis() - wywietrznikPrawy.poczatekRuchuOkna > czasOtwierania))           wywietrznikPrawy.zakoncz_zamknij();
    if ((czerpnia.stan == otwierane) && (millis() - czerpnia.poczatekRuchuOkna > czasOtwierania))           czerpnia.zakoncz_otworz();
    if ((czerpnia.stan == zamykane) && (millis() - czerpnia.poczatekRuchuOkna > czasOtwierania))           czerpnia.zakoncz_zamknij();
  }

}

void Sekcja::wlaczWentylator() {
  digitalWrite(SSRpin, HIGH);
}
void Sekcja::wylaczWentylator() {
  digitalWrite(SSRpin, LOW);
}

  void Sekcja::awariaZasilania(){
    if(stan>0)
    {
      zasilanie=0;
      stan=5;
    }
      
  }

