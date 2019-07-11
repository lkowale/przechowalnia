#include "Okno.h"


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



Okno::Okno(){

}

void Okno::otworz(){
    digitalWrite(in2, LOW);    
    digitalWrite(in1, HIGH);
    stan=otwierane;
    poczatekRuchuOkna=millis();
}

void Okno::zamknij(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);  
    stan=zamykane;
    poczatekRuchuOkna=millis();    
}
void Okno::zakoncz_otworz(){
       
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);     
    stan=nieruchome;
}

void Okno::zakoncz_zamknij(){

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);    
    stan=nieruchome;
}

void Okno::init(char in1_,char in2_,char pin_krancowki_)
{
  in1=in1_;
  in2=in2_;
  pin_krancowki=pin_krancowki_;
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(pin_krancowki, INPUT);  
}

OknoCzerpnia::OknoCzerpnia(){
  
}

void OknoCzerpnia::init(char in1_,char in2_,char pin_krancowki_,char pin_krancowki2_)
{
  in1=in1_;
  in2=in2_;
  pin_krancowki=pin_krancowki_;
  pin_krancowki2=pin_krancowki2_;
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(pin_krancowki, INPUT);  
  pinMode(pin_krancowki2, INPUT);    
}
OknoPWM::OknoPWM(){

}
void OknoPWM::otworz(){
    digitalWrite(in2, LOW);    
    analogWrite(in1,250);
    stan=otwierane;
    poczatekRuchuOkna=millis();
}

void OknoPWM::zamknij(){
    analogWrite(in1, 250);
    digitalWrite(in2, HIGH);  
    stan=zamykane;
    poczatekRuchuOkna=millis();    
}
void OknoPWM::zakoncz_otworz(){
       
    analogWrite(in1,0);
    digitalWrite(in2, LOW);     
    stan=nieruchome;
}

void OknoPWM::zakoncz_zamknij(){

    analogWrite(in1,0);
    digitalWrite(in2, LOW);    
    stan=nieruchome;
}
