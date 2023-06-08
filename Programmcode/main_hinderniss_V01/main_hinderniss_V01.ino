//hauptprogramm mit Hindernissen V13

//Belegung der Pins
//button = 4
//kamera = 10-13
//Ultraschall = 5-6
//I2C Bus = A4-A5 -> LCD, Gyro, Farbsensor
//MotorSpeed = 9
//Motorichtung = 7-8
//Abstandsmesser (Lox's) = A0-A1
//Servo Lenkung = 3
//frei = A2-A3

///////////////////////////////////////////////////////////////
/*

██╗     ██╗██████╗ ██████╗  █████╗ ██████╗ ██╗███████╗███████╗
██║     ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗██║██╔════╝██╔════╝
██║     ██║██████╔╝██████╔╝███████║██████╔╝██║█████╗  ███████╗
██║     ██║██╔══██╗██╔══██╗██╔══██║██╔══██╗██║██╔══╝  ╚════██║
███████╗██║██████╔╝██║  ██║██║  ██║██║  ██║██║███████╗███████║
╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝
                                                              
*/
///////////////////////////////////////////////////////////////


//Servo Abteilung libraries
#include <Servo.h>
//-------------------------------------------------

//libraries rgb
#include <Wire.h>
#include "rgb_lcd.h"
// Pixy2 Cam
#include "Pixy2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*       
██████╗ ██╗      ██████╗ ██████╗  █████╗ ██╗     ███████╗    ██╗   ██╗ █████╗ ██████╗ ██╗ █████╗ ██████╗ ██╗     ███████╗███╗   ██╗
██╔════╝ ██║     ██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝    ██║   ██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║     ██╔════╝████╗  ██║
██║  ███╗██║     ██║   ██║██████╔╝███████║██║     █████╗      ██║   ██║███████║██████╔╝██║███████║██████╔╝██║     █████╗  ██╔██╗ ██║
██║   ██║██║     ██║   ██║██╔══██╗██╔══██║██║     ██╔══╝      ╚██╗ ██╔╝██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ██║╚██╗██║
╚██████╔╝███████╗╚██████╔╝██████╔╝██║  ██║███████╗███████╗     ╚████╔╝ ██║  ██║██║  ██║██║██║  ██║██████╔╝███████╗███████╗██║ ╚████║
 ╚═════╝ ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝      ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═══╝
*/                                                                                                                               
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int bodenfarbe = 0;



//timer
unsigned long start_time;
//--------------------------------------------------

//LCD anschluss
 int Button = 4;
 int colorR = 255;
 int colorG = 0;
 int colorB = 0;
 //LCD screen selbst
 rgb_lcd lcd;

//runden/ecken zähler
int ecken = 0;
int runden = 0; 
int quadrant = 0;

//Abstands eigene  funktionen (messwerte)
 int Abstand;
 int Abstand_L;
 int Abstand_R;
 
 float winkel;
 float gefahr;
 float korrektur_L = -15.0;
 float korrektur_R = 15.0;
 
  //Fahrtrichtung
  char FR = 'K';

 //geschwindigkeiten
  int NormG = 230;
  int LangG = 185;
  int KurvG = 230; 

  //hindernisse
  char Block = 'K';


 //Block
 int B_ID = 0;
 int B_x = 0;
 int B_y = 0;
 int B_hoch = 0;
 int B_breit = 0;
 int B_Unterkante = 0;
 int B_Abstand = 0;

 //letzte kurve messen
 unsigned long MKurve;
 unsigned long ZKurve = 3000;
  
  //beide ausrichtungen (L/R)
  
  int Wandabstand = 40;

//eigene Module
#include "DCmotor.h"
#include "gyro.h"
#include "lenkung.h"
#include "ultraschall.h"
#include "cam.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    
███████╗██╗ ██████╗ ███████╗███╗   ██╗███████╗    ███████╗██╗   ██╗███╗   ██╗██╗  ██╗████████╗██╗ ██████╗ ███╗   ██╗███████╗███╗   ██╗
██╔════╝██║██╔════╝ ██╔════╝████╗  ██║██╔════╝    ██╔════╝██║   ██║████╗  ██║██║ ██╔╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝████╗  ██║
█████╗  ██║██║  ███╗█████╗  ██╔██╗ ██║█████╗      █████╗  ██║   ██║██╔██╗ ██║█████╔╝    ██║   ██║██║   ██║██╔██╗ ██║█████╗  ██╔██╗ ██║
██╔══╝  ██║██║   ██║██╔══╝  ██║╚██╗██║██╔══╝      ██╔══╝  ██║   ██║██║╚██╗██║██╔═██╗    ██║   ██║██║   ██║██║╚██╗██║██╔══╝  ██║╚██╗██║
███████╗██║╚██████╔╝███████╗██║ ╚████║███████╗    ██║     ╚██████╔╝██║ ╚████║██║  ██╗   ██║   ██║╚██████╔╝██║ ╚████║███████╗██║ ╚████║
╚══════╝╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚══════╝    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═╝  ╚═══╝
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// wenden
 void wenden_L()
 {
    float ZW;
	  int Speed;
    lcd.setRGB(125,0,125);
    Speed = LangG;
     //rückwärts drehen
		 rechts(35);
		 runMotor_R(LangG);
      winkel = IMU_getAngle();
        if(quadrant == 0)
        {
          ZW = 270.0;
        }
        else if(quadrant == 1)
        {
          ZW = 180.0;
        }
        else if(quadrant == 2)
        {
          ZW = 90.0;
        }
        else if(quadrant == 3)
        {
          ZW = 0.0;
        }
       //Finde_Block();
       //Drehen, bis 90 Grad oder Block in Sicht             
        while((winkel > ZW - korrektur_L))
        {

           winkel = IMU_getAngle();
           //Finde_Block();
            Speed = Speed + 5;
            if (Speed > KurvG)
            {
              Speed = KurvG;
            }
              runMotor_R(Speed);
              //delay(20);
        }
   stopMotor();
   ecken = ecken + 1;
   mitte();
	 Abstand_L = SpaceUS_L();
   Abstand_R = SpaceUS_R();
   lcd.setRGB(255,255,255);
   MKurve = millis();
	 runMotor(LangG);

 }
 
  void wenden_R()
 {
    float ZW;
	  int Speed;
    lcd.setRGB(125,0,125);
    Speed = LangG;
     //rückwärts drehen
		 links(35);
		 runMotor_R(LangG);
         winkel = IMU_getAngle();
        if(quadrant == 0)
        {
          ZW = 90.0;
        }
        else if(quadrant == 1)
        {
          ZW = 180.0;
        }
        else if(quadrant == 2)
        {
          ZW = 270.0;
        }
        else if(quadrant == 3)
        {
          ZW = 360.0;
        }
        while(winkel < ZW - korrektur_R)
        {
           //Drehen, bis 90 Grad oder Block in Sicht
           winkel = IMU_getAngle();

            Speed = Speed + 5;
            if (Speed > KurvG)
            {
              Speed = KurvG;
            }
              runMotor_R(Speed);
        }
    stopMotor();
    ecken = ecken + 1;
    mitte();
	  Abstand_L = SpaceUS_L();
    Abstand_R = SpaceUS_R();
    lcd.setRGB(255,255,255);
    MKurve = millis();
    runMotor(LangG);

 }
 
 
  //ausrichten
  void Ausrichten()
  {
    int Lenkung;
    Lenkung = (Abstand_L - Abstand_R)*0.3;

    if (Lenkung > 30.0)
    {
      Lenkung = 30;
    }
    else if (Lenkung < -30.0)
    {
      Lenkung = -30;
    }


    if(Lenkung < 0)
    {
      Lenkung = Lenkung *(-1);
      rechts(Lenkung);
    }
    
    else
    {
      links(Lenkung);
    }

  }

   //ausrichten
  void Ausrichten_L()
  {
    int Lenkung;
    Lenkung = (Abstand_L - Wandabstand)*0.8;
    if (Lenkung > 20.0)
    {
      Lenkung = 20;
    }
    else if (Lenkung < -20.0)
    {
      Lenkung = -20;
    }

    if(Lenkung < 0)
    {
      Lenkung = Lenkung *(-1);
      rechts(Lenkung);
    }
    
    else
    {
      links(Lenkung);
    }

  }

   //ausrichten
  void Ausrichten_R()
  {
    int Lenkung;
    Lenkung = (Wandabstand - Abstand_R)*0.8;
    if (Lenkung > 20.0)
    {
      Lenkung = 20;
    }
    else if (Lenkung < -20.0)
    {
      Lenkung = -30;
    }

    if(Lenkung < 0)
    {
      Lenkung = Lenkung *(-1);
      rechts(Lenkung);
    }
    
    else
    {
      links(Lenkung);
    }

  }

  void Kurve_L_MH()
  {
         int Speed;
         float ZW;
         Speed = LangG;
         lcd.setRGB(0, 0, 255);
        links(30);
    
        
        if(quadrant == 0)
        {
          ZW = 270.0;
        }
        else if(quadrant == 1)
        {
          ZW = 180.0;
        }
        else if(quadrant == 2)
        {
          ZW = 90.0;
        }
        else if(quadrant == 3)
        {
          ZW = 0.0;
        }
       winkel = IMU_getAngle();
       runMotor(LangG);  
       Finde_Block();
       //Drehen, bis 90 Grad oder Block in Sicht             
        while((winkel > ZW - korrektur_L) && (B_ID == 0))
        {

           winkel = IMU_getAngle();
           Finde_Block();
            Speed = Speed + 5;
            if (Speed > KurvG)
            {
              Speed = KurvG;
            }
              runMotor(Speed);
              delay(20);
        }
        /*
        stopMotor();
        lcd.setCursor(0,0);
        lcd.print(B_ID);
        delay(1000);
        
        runMotor(LangG);
        // Drehe auf Block zu
        if (B_ID == 1) // rot
        {   lcd.setRGB(255,0,0);
            Zu_Rot();
        }
        else if (B_ID == 2)
        {   lcd.setRGB(0,255,0);
            Zu_Gruen();
        }
        */
        mitte();

     ecken = ecken + 1;
     
    runMotor(LangG);
    Abstand_L = SpaceUS_L;
    Abstand_R = SpaceUS_R;
    lcd.setRGB(255, 255, 255);
    MKurve = millis();
  }

void Zu_Rot()
{
   
   Finde_Block();
   if (B_x > Bildmitte_x - 10)
   {
      rechts(25);
      while (B_x > Bildmitte_x -10)
      {
        delay(20);
        Finde_Block();
      }
      
   }
   else if (B_x < Bildmitte_x)
   {
      links(25);
      while (B_x > Bildmitte_x -10)
      {
        delay(20);
        Finde_Block();
      }
   }
   mitte();
   Abstand = SpaceUS_V();
   while (Abstand > 30)
   {
     delay(50);
     Abstand = SpaceUS_V();
   }
}

void Zu_Gruen()
{
   
   Finde_Block();
   if (B_x > Bildmitte_x - 10)
   {
      links(25);
      while (B_x > Bildmitte_x -10)
      {
        delay(20);
        Finde_Block();
      }
      
   }
   else if (B_x < Bildmitte_x)
   {
      rechts(25);
      while (B_x > Bildmitte_x -10)
      {
        delay(20);
        Finde_Block();
      }
   }
   mitte();
   Abstand = SpaceUS_V();
   while (Abstand > 30)
   {
     delay(50);
     Abstand = SpaceUS_V();
   }

}

void Kurve_R_MH()
    {
         int Speed;
         float ZW;
         Speed = LangG;
         lcd.setRGB(0, 0, 255);
          rechts(30);
        winkel = IMU_getAngle();
        if(quadrant == 0)
        {
          ZW = 90.0;
        }
        else if(quadrant == 1)
        {
          ZW = 180.0;
        }
        else if(quadrant == 2)
        {
          ZW = 270.0;
        }
        else if(quadrant == 3)
        {
          ZW = 360.0;
        }
        while(winkel < ZW - korrektur_R)
        {
           winkel = IMU_getAngle();

            Speed = Speed + 5;
            if (Speed > KurvG)
            {
              Speed = KurvG;
            }
              runMotor(Speed);
        }

      ecken = ecken + 1;
      mitte();
    runMotor(LangG);
    Abstand_L = SpaceUS_L();
    Abstand_R = SpaceUS_R();
    lcd.setRGB(255, 255, 255);
    MKurve = millis();
  }


void Ausweichen_L()
{
  float winkel;
  float ZW;
  int Speed;

  // Speichere Ausrichtung und Quadrant
  links(25);
  runMotor(KurvG);
  // Drehen, bis Block nicht mehr zu sehen
  while(B_ID == 2)
  {
    delay(20);
    Finde_Block();
  }
  runMotor(LangG);
  mitte();
  
  delay(40);    //geradeaus nach delay
  rechts(25);
  runMotor(KurvG);
  // Lenke auf gerade Ausrichtung nach Gyro
  ZW = IMU_ZW_gerade();
  winkel = IMU_getAngle();
  while(winkel < ZW )
  {
      winkel = IMU_getAngle();
      delay(20);
  }
  mitte();
  runMotor(LangG);
  // Vorbeifahren
  delay (200);
  /*wieder einscheren
  runMotor(KurvG);
  rechts(25);
  delay(40);
  mitte();
  runMotor(LangG);
  delay(100);
  links(25);
  runMotor(KurvG);
  delay(40);
  mitte();
  runMotor(LangG);*/
  lcd.setRGB(255,255,255);

}  



void Ausweichen_R()
{
  float winkel;
  float ZW;
  int Speed;

  // Speichere Ausrichtung und Quadrant
  rechts(25);
  runMotor(KurvG);
  // Drehen, bis Block nicht mehr zu sehen
  while(B_ID == 1)
  {
    delay(20);
    Finde_Block();
  }
  runMotor(LangG);
  mitte();
  
  delay(20);    //geradeaus nach delay
  links(25);
  runMotor(KurvG);
  // Lenke auf gerade Ausrichtung nach Gyro
  if(quadrant == 0)
  {
    ZW = 360.0;
  }
  else if(quadrant == 1)
  {
    ZW = 90.0;
  }
  else if(quadrant == 2)
  {
    ZW = 180.0;
  }
  else if(quadrant == 3)
  {
    ZW = 270.0;
  }
  winkel = IMU_getAngle();
  while(winkel > ZW - korrektur_L)
  {
      winkel = IMU_getAngle();
      delay(20);
  }
  mitte();
  runMotor(LangG);
  // Vorbeifahren
  delay (200);
  lcd.setRGB(255,255,255);
  
}  


//////////////////////////////////////////////////////////////////////////////////
/*
███████╗███████╗████████╗██╗   ██╗██████╗ 
██╔════╝██╔════╝╚══██╔══╝██║   ██║██╔══██╗
███████╗█████╗     ██║   ██║   ██║██████╔╝
╚════██║██╔══╝     ██║   ██║   ██║██╔═══╝ 
███████║███████╗   ██║   ╚██████╔╝██║     
╚══════╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝     
*/
//////////////////////////////////////////////////////////////////////////////////////

void setup() {
Wire.begin();
Serial.begin(115200);
//LCD SETUP
  pinMode(Button, INPUT); // Knopf
// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);

//Kamera initialiesieren
  Serial.println("Kamerastart");
  Kamera_Start();
   Serial.println("Kamera gestartet");

//------------------------------------------------
//von dem lenkung.h
servosetup();

  //setup von ultraschall.h
  ultraschallstart();

  //initalisiert motor pinmodes von DCmotor.h
  motorsetup();

  delay(5000); // 5 Sekunden warten

  //gyro setup gyro.h
  gyrostart();  


/* Farbsensor
  Farb_Start();
*/

 // Abstand zur Kurve ZEIGE MESSWERTE
 Abstand = SpaceUS_V(); 
 Abstand_L = SpaceUS_L();
 Abstand_R = SpaceUS_R();

  //erkennt block und printed auf lcd
  Finde_Block();
  lcd.clear();



  
  //ecken zählen
   winkel = IMU_getAngle(); 

    lcd.setCursor(0,0);
    lcd.print(Abstand_L);
    lcd.print("  ");
    lcd.print(Abstand);
    lcd.print("  ");
    lcd.print(Abstand_R);
    lcd.setCursor(0,1);
    lcd.print(winkel);
    lcd.print("  ");    
    lcd.print(FR);
    lcd.print("  ");
    lcd.print(B_ID);

  //setup fertig, AmpGe schalten == knopf drücken
  lcd.setRGB(255, 130, 0);

  while (digitalRead(Button) == LOW) { // Warten, bis Knopf gedrückt wird
    delay(50);
  }

  lcd.clear();
  
  //ampel weiß
  lcd.setRGB(255, 255, 255);  

  // Speichere die aktuelle Zeit
  start_time = millis();
  MKurve = millis() - ZKurve;

  //lenkung mitte  
  mitte();
  
  //langsam losfahren
   runMotor(LangG);

 }
//ENDE

///////////////////////////////////////////////////////////////////////////
/*                                               
██╗      ██████╗  ██████╗ ██████╗ 
██║     ██╔═══██╗██╔═══██╗██╔══██╗
██║     ██║   ██║██║   ██║██████╔╝
██║     ██║   ██║██║   ██║██╔═══╝ 
███████╗╚██████╔╝╚██████╔╝██║     
╚══════╝ ╚═════╝  ╚═════╝ ╚═╝     
 */ 
////////////////////////////////////////////////////////////////////////////

 void loop() 
 {

  int zufall;
  // Prüfe Hindernisse
  Finde_Block();
  Abstand = SpaceUS_V();
  
  // zeige gefunden Block an 
  if (B_ID == 1)
  {
	 lcd.setRGB(255,0,0);
  }
  else if (B_ID == 2)
  {
	  lcd.setRGB(0,255,0);
  }
  else
  {
	  lcd.setRGB(255,255,255);
  }

   // rot: prüfe, ob ausweichen rechts
  if ((B_ID == 1) && (B_x > 80) && (B_Unterkante > 120))
  {

	  Ausweichen_R();
  }

  else if ((B_ID == 2) && (B_x < 240) && (B_Unterkante > 120))
  {
	  //grün: ausweichen links
	  
      Ausweichen_L();
  }
  else // kein Block in Sicht, dem man ausweichen muss
  {
   
    Abstand = SpaceUS_V();	
    Abstand_L = SpaceUS_L();
    Abstand_R = SpaceUS_R();
    
    /*bodenfarbe
    bodenfarbe = Bodenfarbe();*/

    if (FR == 'K')
    {
        if (Abstand_L > 80)
        {
          FR = 'L';
        }
        else if (Abstand_R > 80)
        {
          FR = 'R';
        }
    }
	
    //Vor Außenwand
    if ((Abstand < 25) && (millis() - MKurve > ZKurve)) // Nähe Wand gegenüber
    {
      
      stopMotor();
      
        
       if (FR == 'K')
       {
        Abstand_L = SpaceUS_L();
        Abstand_R = SpaceUS_R();
        if (Abstand_L > 60)
        {
          FR = 'L';
        }
        else if (Abstand_R > 60)
        {
          FR = 'R';
        }
        else
        {
      
            // wenn FR immer noch unklar, per Zufall auswählen
            zufall = random(2);
            if (zufall == 0)
            {
              FR = 'R';
            }
            else
            {
              FR = 'L';
            }
        }
      }

      lcd.setCursor(0,0);
      lcd.print(FR);
      delay(500);
      // prüfen: wenden oder Kurve
      if (FR == 'R')
      {
        Abstand_L = SpaceUS_L();
        if (Abstand_L > 35)
        {
          wenden_R();
        }
        else
        {
          // zuruck und Kurve
          runMotor_R(180);
          while (Abstand < 70) 
          {
            delay(20);
            Abstand = SpaceUS_V();
          }
          stopMotor();
          Kurve_R_MH();
          
        }
      }
      else // FR == L
      {
        
        Abstand_R = SpaceUS_R();
        if (Abstand_R > 35)
        {
          wenden_L();
        }
        else
        {
          // zuruck und Kurve
          runMotor_R(180);
          while (Abstand < 60) 
          {
            delay(20);
            Abstand = SpaceUS_V();
          }
          stopMotor();
          Kurve_L_MH();
        }
        stopMotor();
        lcd.setRGB(255,255,255);  //Ende Kurve, Wenden
        delay(500);
        runMotor(LangG);
      }
    }
    else
    { 
      // an der Außenwand orientieren
      Abstand_L = SpaceUS_L();
      Abstand_R = SpaceUS_R();
      if (FR == 'R')
      {
        Ausrichten_L();
      }
      else if (FR == 'L')
      {
        Ausrichten_R();
      }
  
      delay(20);
    }
     
  } // Ende kein Block zum Ausweichen in Sicht



/*
  
  //prüfen ob L abbiegen
  if((FR == 'L') && (Abstand_L > 80) && (millis() - MKurve > ZKurve))
  {
    Kurve_L_MH();

  }


    //prüfen ob R abbiegen
  if((FR == 'R') && (Abstand_R >80) && (millis() - MKurve > ZKurve))
  {
    Kurve_R_MH();
  }

*/
/*
  //alle ecken prüfen
  if(ecken == 12)
  {
    delay(100);
    PRGstopp();
  }

*/

}