
#ifndef Okno_h
#define Okno_h

#define nieruchome 0
#define otwierane 1
#define zamykane 2


class Okno{
  public:
  Okno();
  void otworz();
  void zamknij();
  void zakoncz_otworz();
  void zakoncz_zamknij();
  void init(char in1_,char in2_,char pin_krancowki_);
  char in1,in2,pin_krancowki;
  char stan=nieruchome;
  unsigned long poczatekRuchuOkna;
};

class OknoCzerpnia:public Okno{
  public:
  OknoCzerpnia();
  void init(char in1_,char in2_,char pin_krancowki_,char pin_krancowki2_);  
  char pin_krancowki2;
};

class OknoPWM:public Okno{
  public:
  OknoPWM();
  void otworz();
  void zamknij();
  void zakoncz_otworz();
  void zakoncz_zamknij();  
};
#endif
