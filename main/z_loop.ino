//#include <Timers.h>



void loadConfig()
{
  if ((EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
       EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
       EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2]))
    for (unsigned int t = 0; t < sizeof(storage); t++)
      *((char*)&storage + t) = EEPROM.read(CONFIG_START + t);
}

void saveConfig() {
  for (unsigned int t = 0; t < sizeof(storage); t++)
    EEPROM.write(CONFIG_START + t, *((char*)&storage + t));
}

//void podswietl()
//{
//  podswietlenieTimer = Timers.after(CZAS_PODSWIETLENIA, wylaczPodswielenie);
//  lcd.backlight(); // zalaczenie podwietlenia
//  podswietlenie = 1;
//};
//
//void wylaczPodswielenie()
//{
//  Timers.clear(podswietlenieTimer);
//  lcd.noBacklight();
//  podswietlenie = 0;
//};



void loop() {
//  Timers.process();
  
loopctr++;
    if(pocz_okna+2000<millis())
    {
      Serial.println(loopctr);
      loopctr=0;
      pocz_okna=millis();
    }

    char key = customKeypad.getKey();

    if (key)
    {
      
      lcd.setCursor(0, 1);
      lcd.print(key);
      Serial.println(key);

    }

  


 #ifdef DEBUG
  tZ = (analogRead(A0) - 500.0) / 40.0;
  tW1 = (analogRead(A1) - 500.0) / 40.0;
  tW2 = (analogRead(A2) - 500.0) / 40.0;
 #else 
  readSerialForTemp();
  getTemperature();
 #endif





//if(!digitalRead(CZUJNIK_ZASILANIA))
//  {
//   if(sekcja0.zasilanie==1) sekcja0.awariaZasilania();
//   if(sekcja1.zasilanie==1) sekcja1.awariaZasilania();    
//  }
//else
//{
//    if(sekcja0.zasilanie==0) sekcja0.zasilanie=1;
//    if(sekcja1.zasilanie==0) sekcja1.zasilanie=1;    
//}

  // put your main code here, to run repeatedly:
  sekcja0.proces(tZ, tW1);
  sekcja1.proces(tZ, tW2);

  if (!aktywnaSekcja->trybAuto) //reczny
  {
    ///////////////////////                                           wyswietlanie                                  ///////////////////////  ///////////////////////

    lcd.setCursor(0, 0);
    lcd.print(aktywnaSekcja->id);
    lcd.print('_');
    lcd.print("Z:");
    lcd.print(tZ);
    lcd.print(" W:");
    lcd.print(aktywnaSekcja->tW);
    lcd.print("  ");

    lcd.setCursor(0, 1);
    // 1-otworz okna,2-zamknij okna,3-wlacz wentulator
    if (pozycjaMenu == 1)            lcd.print("1 otworz LG ");
    if (pozycjaMenu == 2)            lcd.print("2 otworz PG ");
    if (pozycjaMenu == 3)            lcd.print("3 otworz D ");
    if (pozycjaMenu == 4)            lcd.print("4 zamknij ");
    if (pozycjaMenu == 5)            lcd.print("5 Wentylator ");
    if (pozycjaMenu == 6)            lcd.print("6 Zmiensekcje ");


    lcd.print("                  ");
    /////////////////////////////////////                                          wprowadzanie      ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////

    
    key = customKeypad.getKey();

    if (key)
    {
//      if (!podswietlenie) podswietl();
//
//      else
      {
        if (key == '#')
        {
          aktywnaSekcja->trybAuto = true;
          aktywnaSekcja->stan = 0;
        }

        if (key == '>')
        {
          if (pozycjaMenu < iloscPozycjiMenu) pozycjaMenu++;
          else  pozycjaMenu = 1;
        }
        if (key == '<') {
          if (pozycjaMenu > 1) pozycjaMenu--;
          else  pozycjaMenu = iloscPozycjiMenu;
        }
        if (key == 'D')
        {
          if (pozycjaMenu == 1)
          {
            aktywnaSekcja->wywietrznikLewy.otworz();
          }
          if (pozycjaMenu == 2)
          {
            aktywnaSekcja->wywietrznikPrawy.otworz();
          }
          if (pozycjaMenu == 3)
          {
            aktywnaSekcja->czerpnia.otworz();
          }


          if (pozycjaMenu == 4)
          {
            aktywnaSekcja->wywietrznikLewy.zamknij();
            aktywnaSekcja->wywietrznikPrawy.zamknij();
            aktywnaSekcja->czerpnia.zamknij();
          }

          if (pozycjaMenu == 5)
            if (digitalRead(aktywnaSekcja->SSRpin)) aktywnaSekcja->wylaczWentylator();
            else aktywnaSekcja->wlaczWentylator();
          if (pozycjaMenu == 6)
            if (aktywnaSekcja->id == 0) aktywnaSekcja = &sekcja1;
            else                aktywnaSekcja = &sekcja0;
        }
      }
    }

  }
  if (aktywnaSekcja->trybAuto) //automat
    ///////////////////////                                           wyswietlanie                                  ///////////////////////  ///////////////////////
  {
    lcd.setCursor(0, 0);
    //lcd.print(floatMap(1024));



    //      lcd.noAutoscroll();

    if (stanMenu == 0)
    {
      lcd.print(aktywnaSekcja->id);
      lcd.print("#");
      lcd.print("S");
      lcd.print(aktywnaSekcja->stan);     //stan
      lcd.print("z");
      lcd.print(tZ);
      lcd.print("w");
      lcd.print(aktywnaSekcja->tW);
      lcd.setCursor(0, 1);
      //      lcd.print(tW1_temp);
      //      lcd.print(tW2_temp);
      //      lcd.print(tW3_temp);
      //      lcd.print(tW4_temp);

      lcd.print("                ");
    }
    if (stanMenu == 1)
    {
      // 1-Tzadana,2-dtw,3Tg,4-dtZ,5godz pocz,6- godz konocowa,7 dobowy czas pracy
      if (pozycjaMenu == 1) {
        lcd.print("1 T zadana: ");
        if (aktywnaSekcja->id == 0) lcd.print(storage.tZadana0);
        else lcd.print(storage.tZadana1);
      }
      if (pozycjaMenu == 2) {
        lcd.print("2 dTw: ");
        lcd.print(storage.dtW);
      }
      if (pozycjaMenu == 3) {
        lcd.print("3 Tg: ");
        lcd.print(storage.tG);
      }

      if (pozycjaMenu == 4) {
        lcd.print("4 dTz ");
        lcd.print(storage.dtZ);
      }
      if (pozycjaMenu == 5) {
        lcd.print("5 dTg ");
        lcd.print(storage.dtG);
      }
      if (pozycjaMenu == 6) {
        lcd.print("6 sekcja ");
        lcd.print(aktywnaSekcja->id);
      }
      lcd.print("                  ");
    }




    if (stanMenu == 2) //wprowadzanie
    {

      if (pozycjaMenu == 1) {
        lcd.print("Daj Tzada:"); lcd.print(msg); lcd.blink();
      }
      if (pozycjaMenu == 2) {
        lcd.print("Daj dTw:"); lcd.print(msg); lcd.blink();
      }
      if (pozycjaMenu == 3) {
        lcd.print("Daj Tg:"); lcd.print(msg); lcd.blink();
      }
      if (pozycjaMenu == 4) {
        lcd.print("Daj  dTz: "); lcd.print(msg); lcd.blink();
      }
      if (pozycjaMenu == 5) {
        lcd.print("Daj  dTg: "); lcd.print(msg); lcd.blink();
      }
      if (pozycjaMenu == 6) {
        lcd.print("6 Zmiensekcje ");

      }

      lcd.print("                  ");
    }


    /////////////////////////////////////                                          wprowadzanie      ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////


//    key = customKeypad.getKey();

    if (key)
    {
      
      lcd.setCursor(0, 1);
      lcd.print(key);
      lcd.print(" sM.");
      lcd.print((int)stanMenu);
      lcd.print(" pM.");
      lcd.print((int)pozycjaMenu);

//      if (!podswietlenie) podswietl();
//
//      else
      {
        if (key == '#') {

          aktywnaSekcja->trybAuto = false;
          aktywnaSekcja->stan = 0;
          aktywnaSekcja->wylaczWentylator();
        }

        else if (stanMenu == 0) { //menu wylaczone
          if (key == 'D')   stanMenu = 1;

        }
        else if (stanMenu == 1) { //przegladanie menu
          if (key == '>')
          {
            if (pozycjaMenu < iloscPozycjiMenu) pozycjaMenu++;
            else  pozycjaMenu = 1;
          }
          if (key == '<') {
            if (pozycjaMenu > 1) pozycjaMenu--;
            else  pozycjaMenu = iloscPozycjiMenu;
          }
          if (key == 'C')
            stanMenu = 0;
          if (key == 'D')
            stanMenu = 2;

        }

        else if (stanMenu == 2) { //wprowadzanie pozycji
          if (isDigit(key) || key == '.')    msg = msg + key;
          if (key == 'C') {
            stanMenu = 1;
            msg = "";
          }
          if (key == 'D') {
            wprowadzonaLiczba = msg.toFloat();
            // // 1-Tzadana,2-dtw,3Tg,4-dtZ,5godz pocz,6- godz konocowa,7 dobowy czas pracy

            if (pozycjaMenu == 1) { //
              if (wprowadzonaLiczba < 20 && wprowadzonaLiczba > 0)
                if (aktywnaSekcja->id == 0) storage.tZadana0 = wprowadzonaLiczba;
                else storage.tZadana1 = wprowadzonaLiczba;
              saveConfig();
              stanMenu = 1;
            }

            if (pozycjaMenu == 2) { //
              if (wprowadzonaLiczba > 0 && wprowadzonaLiczba < 4)
                storage.dtW = wprowadzonaLiczba;
              saveConfig();
              stanMenu = 1;
            }

            if (pozycjaMenu == 3) { //
              if (wprowadzonaLiczba > 0 && wprowadzonaLiczba < 4)
                storage.tG = wprowadzonaLiczba;
              saveConfig();
              stanMenu = 1;
            }

            if (pozycjaMenu == 4) { //
              if (wprowadzonaLiczba > 0 && wprowadzonaLiczba < 12)
                storage.dtZ = wprowadzonaLiczba;
              saveConfig();
              stanMenu = 1;
            }
            if (pozycjaMenu == 6) {
              if (aktywnaSekcja->id == 0) aktywnaSekcja = &sekcja1;
              else                aktywnaSekcja = &sekcja0;
              stanMenu = 1;
            }
            msg = "";
          }
        }
      }
    }
  }

///////////////////////////////////////////////////////////             wysylanie stanu     ///////////////////////////////////////////////////////////             
  if(stan_polaczenia==0)
    if(poczatek_okna+SZEROKSC_OKNA<millis())      
            stan_polaczenia=1;          

  if(stan_polaczenia==1)
  {
          client.connect("klima.kovi.vdl.pl", 80);
          poczatek_laczenia=millis();
          stan_polaczenia=2;
          Serial.print(millis()/1000);
          Serial.println(" laczenie "); 
  }
  if(stan_polaczenia==2)
    if(client.connected())
    {
          stan_polaczenia=3;
          Serial.print(millis()/1000);
          Serial.println(" polaczony ");           
    }
    else
      if(poczatek_laczenia+POLACZ_CZEKAJ<millis()) 
      {
          stan_polaczenia=0;
          client.stop();       
          poczatek_okna=poczatek_okna+10000;// sproboj znowu za 10 sek 
          Serial.print(millis()/1000);
          Serial.println(" polaczenie nieudane ");                  
      }
 if(stan_polaczenia==3)
 {
          Serial.print(millis()/1000);
          Serial.println(" wysylanie temp "); 
          wyslijTemp();
          poczatek_okna=millis();
          client.stop(); 
          stan_polaczenia=0;
 }
//Serial.println("koniecokna");
 
}

