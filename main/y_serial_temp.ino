 #include <MemoryFree.h>
 
  void readSerialForTemp()
  {
    
  if (Serial1.available()) {
//    delay(100); //allows all serial sent to be received together
   int t=0;
    while(Serial1.available()&&t<sizeof(RF_packet)) {
//      char c=Serial1.read();
//      Serial.print(c);
      *(((char*)&data_buffer + t))=Serial1.read();
      delay(1);
//      Serial.print(*(((char*)&data_buffer + t)));
      t++;
    }
      Serial.println();

  for (t=0; t<sizeof(RF_packet); t++)
   *(((char*)&listaCzujnikow[data_buffer.id].data + t))=*(((char*)&data_buffer + t));
   
   listaCzujnikow[data_buffer.id].ostatniOdczyt=now();
   

      {
//      Serial.print(F(" PRINTING AFTER WRITING: listaCzujnikow[data_buffer.id].ostatni odczyt"));      

//      Serial.print((int)listaCzujnikow[data_buffer.id].data.id);
//      Serial.print(F(" temp: "));
//      Serial.print(listaCzujnikow[data_buffer.id].data.temp);  
//      Serial.print(F(" packets_send: "));
//      Serial.print(listaCzujnikow[data_buffer.id].data.packets_send);       
//      Serial.print(F(" vol: "));
//      Serial.print(listaCzujnikow[data_buffer.id].data.vol);      
//      Serial.print(F(" time: "));
//      Serial.println(listaCzujnikow[data_buffer.id].ostatniOdczyt);    
//      Serial.print(hour());
//      printDigits(minute());
//      printDigits(second());
//      Serial.print(" ");
//      Serial.print(day());
//      Serial.print(" ");
//      Serial.print(month());
//      Serial.print(" ");
//      Serial.print(year()); 
//      Serial.print(" ");      
//      Serial.println(getNtpTime()      );
      }   
  }

  }
  
//void wyslijStan()
//{
// 
//  client.connect("klima.kovi.vdl.pl", 80)  ;
//        if (client.connected()) 
//        {                      
//            wyslijTemp();           
//            
//             Serial.print("Server response: ");
//  
//              for(i=0;i<100;i++)
//              {
//                serverResponse[i] = client.read();
//                Serial.print(serverResponse[i]);
//
//                if(i>5)
//                  if(serverResponse[i-5]=='2'&&serverResponse[i-4]=='0'&&serverResponse[i-3]=='0'&&serverResponse[i-2]==' '&&serverResponse[i-1]=='O'&&serverResponse[i]=='K')
//                  {
//                      //dane przyjete                  
////                              poczatekOkna=millis();  
//                                Serial.println("");                              
//                              Serial.println("Dane przyjete");                
//                              //przerwij petle
//                              i=100;
//                   }
//              }
//              
//        }
//        else 
//        {
//        Serial.println("Server nie podlaczony");
//        //przesun poczatek okna o 30 sek - ponowne polaczenie
////        poczatekOkna=poczatekOkna+30000;
//        }
//  client.stop();         
//}


void wyslijTemp()
{
//
//        // Make a HTTP request:
//        // "GET /data.php?tW_temp=19.44&docelowa_temp=4.00 HTTP/1.1"
                                            //        client.println("GET /data1.php?t1=19.44&t2=1&t3=3&t4=4&t5=5&t6=6&t7=7&t8=8&t9=9&t10=10&t11=11&t12=12&tZ=10&tW=11&stan=3&docelowa_temp=4.00  HTTP/1.1");
                                            //        client.println("Host: klima.kovi.vdl.pl");
                                            //        client.println("Connection: close\r\n"); 
                                            //        client.println();
//         client.println(" HTTP/1.1");
//         Serial.println(" HTTP/1.1");       
//   
//         client.println("Host: klima.kovi.vdl.pl");
//         Serial.println("Host: klima.kovi.vdl.pl");         
//        // now send the blank line
//         client.println("Connection: close\r\n");
//         Serial.println("Connection: close\r\n");      
//               
//        client.println();
//        Serial.println();
//        client.println();
//        //Serial.print("GET /data.php?tW_temp=19.44&docelowa_temp=4.00");
//  #ifdef DEBUG
//   Serial.println("--------------------------------wyslijTemp---------------------------");  
//  #endif  
        client.print("GET /data1.php?t1="); //place your server address here
//        Serial.print("GET /data.php?tW1_temp=");
        client.print(listaCzujnikow[1].data.temp);
//        Serial.print(tW1_temp);
//        
        client.print("&t2="); //place your server address here
//        Serial.print("&tW2_temp=");
        client.print(listaCzujnikow[2].data.temp);
//        Serial.print(tW2_temp);
//        
        client.print("&t3="); //place your server address here
//        Serial.print("&t3=");
        client.print(listaCzujnikow[3].data.temp);
//        Serial.print(tW3_temp);
//        
        client.print("&t4="); //place your server address here
//        Serial.print("&tW4_temp=");
        client.print(listaCzujnikow[4].data.temp);
//        Serial.print(tW4_temp);
//        
        client.print("&t5="); //place your server address here
//        Serial.print("&tW2_temp=");
        client.print(listaCzujnikow[1].data.vol);
//        Serial.print(tW2_temp);
//        
        client.print("&t6="); //place your server address here
//        Serial.print("&t3=");
        client.print(listaCzujnikow[2].data.vol);
//        Serial.print(tW3_temp);
//        
        client.print("&t7="); //place your server address here
//        Serial.print("&tW4_temp=");
        client.print(listaCzujnikow[3].data.vol);        
//        Serial.print(tW4_temp);

        client.print("&t8="); //place your server address here
//        Serial.print("&tW4_temp=");
        client.print(listaCzujnikow[4].data.vol);        
//        Serial.print(tW4_temp);

        client.print("&t9="); //place your server address here
//        Serial.print("&tW2_temp=");
        client.print(listaCzujnikow[1].ostatniOdczyt);
//        Serial.print(tW2_temp);
//        
        client.print("&t10="); //place your server address here
//        Serial.print("&t3=");
        client.print(listaCzujnikow[2].ostatniOdczyt);
//        Serial.print(tW3_temp);
//        
        client.print("&t11="); //place your server address here
//        Serial.print("&tW4_temp=");
        client.print(listaCzujnikow[3].ostatniOdczyt);        
//        Serial.print(tW4_temp);

        client.print("&t12="); //place your server address here
//        Serial.print("&tW4_temp=");
        client.print(listaCzujnikow[4].ostatniOdczyt);        
        
//        Serial.print(tW4_temp);
        client.print("&t13="); //place your server address here
//        Serial.print("&tW4_temp=");
        client.print(freeMemory());  
        
        client.print("&tZ=");
//        Serial.print("&tZ_temp=");
        client.print(tZ);
        
        client.print("&tW=");
//        Serial.print("&tZ_temp=");
        client.print(tW1);        
//        Serial.print(tZ_temp);        
//        client.print("&tI_temp="); //place your server address here
//        Serial.print("&tI_temp=");
//        client.print(tI_temp);
//        Serial.print(tI_temp);
//        
        client.print("&docelowa_temp=");
//        Serial.print("&docelowa_temp=");
        client.print(storage.tZadana0);
//        Serial.print(storage.tZadana);

        client.print("&stan="); 
        client.print(aktywnaSekcja->stan);

//                                
         client.println(" HTTP/1.1");
//         Serial.println(" HTTP/1.1");       
//   
         client.println("Host: klima.kovi.vdl.pl");
//         Serial.println("Host: klima.kovi.vdl.pl");         
//        // now send the blank line
         client.println("Connection: close\r\n");
//         Serial.println("Connection: close\r\n");      
//               
        client.println();
//        Serial.println();    
//           
}  

