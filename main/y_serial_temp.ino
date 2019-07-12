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
   
  }

  }
  

void wyslijTemp()
{

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
         client.println("Host: any.host.pl");
       
//        // now send the blank line
         client.println("Connection: close\r\n");
//         Serial.println("Connection: close\r\n");      
//               
        client.println();
//        Serial.println();    
//           
}  

