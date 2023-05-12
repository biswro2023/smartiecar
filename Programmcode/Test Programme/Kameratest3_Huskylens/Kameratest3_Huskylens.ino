#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// Kamera
HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX

//Knopf
 const int Knopf = 4;      //Knopf auf Pin 6

 char FR = 'K';

// Linie
 int L_x1 = 0;
 int L_y1 = 0;
 int L_x2 = 0;
 int L_y2 = 0;
 int L_ID = 0;

 //Block
 int B_ID = 0;
 int B_x = 0;
 int B_y = 0;
 int B_hoch = 0;
 int B_breit = 0;
 int B_Unterkante = 0;

 void Kameramodus_Farben()
 {
   //Farbblöcke: ALGORITHM_COLOR_RECOGNITION
   //Linien: ALGORITHM_LINE_TRACKING
    huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION); //Umschalten auf Farberkennung
    delay(50);
 }

 void Kameramodus_Linien()
 {
   //Farbblöcke: ALGORITHM_COLOR_RECOGNITION
   //Linien: ALGORITHM_LINE_TRACKING
    huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING); //Umschalten auf Linen
    delay(50);
 }

 void Finde_Linie()
 {

    if (huskylens.requestArrowsLearned())
    {
      int abstand_x = 0;
      int abstand_y = 0;

      L_ID = 0;   
      L_x1 = 0;
      L_y1 = 0;
      L_x2 = 0;
      L_y2 = 0;
 

        for (int i = 0; i < huskylens.count(); i++)
        {
            HUSKYLENSResult result = huskylens.get(i);
            abstand_x = result.xTarget - result.xOrigin;
            abstand_y = result.yTarget - result.yOrigin;         
          // Prüfe, ob gültige Line oder eigentlich Hindernis
          if (abs(abstand_x) > 50)  //Punkte liegen mehr als 50 pixel auseinander
          {
              L_ID = result.ID;
              L_x1 = result.xOrigin;
              L_y1 = result.yOrigin;
              L_x2 = result.xTarget;
              L_y2 = result.yTarget; 

             break;  //Schleife abbrechen
          }      
        }

    }

    Serial.print("Linie: ");
    Serial.println(L_ID);    
 }

 void Finde_Block()
 {
    int unterkante = 0;
    B_ID = 0;
    B_x = 0;
    B_y = 0;
    B_hoch = 0;
    B_breit = 0;
    B_Unterkante = 0;    
 

    if (huskylens.requestBlocksLearned())
    {
      // nur vordersten Block speichern
        for (int i = 0; i < huskylens.count(); i++)
        {
            HUSKYLENSResult result = huskylens.get(i);
            unterkante = result.yCenter + result.height/2;
            if (unterkante > B_Unterkante )
            {
              
              B_ID = result.ID;
              B_x = result.xCenter;
              B_y = result.yCenter;
              B_hoch = result.height;
              B_breit = result.width;
              B_Unterkante = unterkante;
            }
        }
    }
    Serial.print("Block: ");
    Serial.println(B_ID);    
   
 }


 void Camtest()
 {
    int i = 0;
    //gelernet Linien in Sicht
    huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);
    delay(50);
    
    if (huskylens.requestArrowsLearned())
    {
        for (i = 0; i < huskylens.count(); i++)
        {
            HUSKYLENSResult result = huskylens.get(i);
            Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);        }

    }
    else 
    {
      Serial.println("Keine Linie");
    }   

    huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);
    delay(50);
    if (huskylens.requestBlocksLearned())
    {
        for (i = 0; i < huskylens.count(); i++)
        {
            HUSKYLENSResult result = huskylens.get(i);
            Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
        }

    }
    else
    {
      Serial.println("Kein Block");
    }   
      Serial.println("cam ende");
 }

void setup() {

   Serial.begin(115000);
   while (! Serial) { delay(1); }
   Serial.println("cam startet");

     
    mySerial.begin(9600); // Software-Serial CAM conct
    while (! mySerial) { delay(1); }  //warte auf Kameraport
    while (!huskylens.begin(mySerial))
  
    {
        Serial.println(F("Begin failed!"));
        delay(100);
    }
     
     Serial.println("button drücken");

}

void loop() {

  int knopfstatus = LOW;

  // Warte auf Knopfdruck
  knopfstatus = digitalRead(Knopf);
  while (knopfstatus==LOW)
  {
     delay(20);
    knopfstatus = digitalRead(Knopf);
  }    

  Camtest();     
  Finde_Block();
  Serial.println(B_ID);
  Serial.println("bitte nochmal drücken für einen anderen block");

}
