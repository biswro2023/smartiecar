//hauptprogramm ohne Hindernisse 01

//Belegung der Pins
//button = 4
//kamera = 10-13
//Ultraschall = 5-6
//I2C Bus = A4-A5
//MotorSpeed = 9
//Motorichtung = 7-8
//Abstandsmesser = A0-A1
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


//--------------------------------------------

//Servo Abteilung libraries
#include <Servo.h>
//-------------------------------------------------

//libraries rgb
#include <Wire.h>
#include "rgb_lcd.h"

//--------------------------------------------------

//Farbsensor
#include "Adafruit_TCS34725.h"

// Pixy2 Cam
#include "Pixy2.h"

#include <NewPing.h>
//-------------------------------------------------



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


 Pixy2 pixy;
 int Bildmitte_x = 157;
 int Bildmitte_y = 104;


//timer
unsigned long start_time;
//--------------------------------------------------

 //geschwindigkeiten
  int NormG = 230;
  int LangG = 215;
  int KurvG = 230; 
  int StartG = 190;


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
 float korrektur_L = -35.0;
 float korrektur_R = 20.0;
 
  //Fahrtrichtung
  char FR = 'K';

  //Fahrmodus
  char FM = 'E';
  //hindernisse
  char Block = 'K';

  //huskeylens int's
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

 //letzte kurve messen
 unsigned long MKurve;
 unsigned long ZKurve = 1000;
  
  //beide ausrichtungen (L/R)
  int Wandabstand = 25;

  
//eigene Module
#include "DCmotor.h"
#include "gyro.h"
#include "lenkung.h"
#include "ultraschall.h"

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

    delay(20);

  }

   //ausrichten
  void Ausrichten_L()
  {
    int Lenkung;
    Lenkung = (Abstand_L - Wandabstand)*0.9;
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
      lcd.setCursor(0, 1);
      lcd.print("R ");
      lcd.print(Lenkung);
    }
    
    else
    {
      links(Lenkung);
      lcd.setCursor(0, 1);
      lcd.print("L ");
      lcd.print(Lenkung);
    }

    delay(50);

  }

   //ausrichten
  void Ausrichten_R()
  {
    int Lenkung;
    Lenkung = (Wandabstand - Abstand_R)*0.9;
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
      lcd.setCursor(0, 1);
      lcd.print("R ");
      lcd.print(Lenkung);
    }
    
    else
    {
      links(Lenkung);
      lcd.setCursor(0, 1);
      lcd.print("L ");
      lcd.print(Lenkung);
    }

    delay(50);

  }

  void Kurve_L()
  {
         int Speed;
         float ZW;
         Speed = LangG;
        links(40);
        lcd.setRGB(0, 0, 255);
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
        lcd.clear();
        lcd.setCursor(0,0);
        /*lcd.print(winkel);*/
        runMotor(LangG);               
        while(winkel > ZW - korrektur_L)
        {
           
           winkel = IMU_getAngle();
            Speed = Speed + 5;
            if (Speed > KurvG)
            {
              Speed = KurvG;
            }
              runMotor(Speed);
              /*lcd.setCursor(0,0);
              lcd.print(winkel);*/
              delay(50);
        }
      /*lcd.clear();
      lcd.print(winkel);*/
      ecken = ecken + 1;
      mitte();
    runMotor(NormG);
    Abstand_L = SpaceUS_L;
    while(Abstand_L > 60)
    {
      Abstand_L = SpaceUS_L();
      
      winkel = IMU_getAngle();

      delay(10);
    }
    lcd.setRGB(0, 255, 0);
    MKurve = millis();
  }

void Kurve_R()
    {
         int Speed;
         float ZW;
         Speed = LangG;
        rechts(40);
        lcd.setRGB(0, 0, 255);
      
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
    runMotor(NormG);
    Abstand_R = SpaceUS_R;
    while(Abstand_R > 60)
    {
      Abstand_R = SpaceUS_R();
      delay(10);
    }
    lcd.setRGB(0, 255, 0);
    MKurve = millis();
  }

 void Erste_Kurve()
 {
  Abstand_L = SpaceUS_L();
  Abstand_R = SpaceUS_R();


  //fahrtrichtung bestimmen
  if(FR == 'K')
  {
    if(Abstand_L > 60)
    {
      FR = 'L';
      Kurve_L();
     /*lcd.setCursor(0,0);
      lcd.print(FR);*/
    }
    else if(Abstand_R > 60)
    {
        FR = 'R';
        Kurve_R();
        /*lcd.setCursor(0,0);
        lcd.print(FR);*/
    }        
  }

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
///////////////////////////////////////////////////////////////////////////////////

void setup() {
Wire.begin();

//LCD SETUP
  pinMode(Button, INPUT); // Knopf
// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);

//------------------------------------------------
//von dem servo.ino
servosetup();

//-------------------------------------

  lcd.setCursor(0, 0);
  lcd.print(F("Cam OK  "));

  //setup von ultraschall.ino
  ultraschallstart();

  //initalisiert motor pinmodes von DCmotor.ino
  motorsetup();

  delay(5000); // 5 Sekunden warten

  //gyro setup gyro.ino
  gyrostart();  
    
 // Abstand zur Kurve ZEIGE MESSWERTE
 Abstand = SpaceUS_V(); 
 Abstand_L = SpaceUS_L();
 Abstand_R = SpaceUS_R();

if(Abstand_L < 10)
{
  FR = 'L';
}

if(Abstand_R < 10)
{
  FR = 'R';  
}

  
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
    lcd.print(FM);

  //setup fertig, AmpGe schalten == knopf drücken
  if (FM == 'E') 
  {
    lcd.setRGB(255, 130, 0);
  }

  else
  {
    lcd.setRGB(255, 255, 0);
  }

  
  while (digitalRead(Button) == LOW) { // Warten, bis Knopf gedrückt wird
    delay(50);
  }

  lcd.clear();
  
  //ampel grün weh
  lcd.setRGB(0, 255, 0);  

  // Speichere die aktuelle Zeit
  start_time = millis();

  //lenkung mitte  
  mitte();
  MKurve = millis() - ZKurve;
  // Langsam erste Kurve finden
   
   runMotor(StartG);


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

 // Abstand zur Kurve ZEIGE MESSWERTE
 //Abstand = SpaceUS_V(); 
 Abstand_L = SpaceUS_L();
 Abstand_R = SpaceUS_R();


  //fahrtrichtung bestimmen
  if(FR == 'K')
  {
    if(Abstand_L >60)
    {
      FR = 'L';
      Kurve_L();
     /*lcd.setCursor(0,0);
      lcd.print(FR);*/
    }
    else if(Abstand_R >60)
    {
        FR = 'R';
        Kurve_R();
        /*lcd.setCursor(0,0);
        lcd.print(FR);*/
    }        
  }


  
  //prüfen ob L abbiegen
  if((FR == 'L') && (Abstand_L >60) && (millis() - MKurve >= ZKurve))
  {
    Kurve_L();
  }
 
    //prüfen ob R abbiegen
  if((FR == 'R') && (Abstand_R >60) && (millis() - MKurve >= ZKurve))
  {
    Kurve_R();
  }

 //ruft Ausrichtungsfunktion auf
 if(FR == 'K')
 {
  Ausrichten();
  delay(20);
 }
 
 else if(FR == 'L')
 {
   Ausrichten_L();
   delay(40);
 }

 else if(FR == 'R')
 {
   Ausrichten_R();
   delay(40);
 }


  //vor kurve langsam fahren
  if(Abstand < 90)
  {
    runMotor(LangG);
  }

  //alle ecken prüfen
  if(ecken == 12)
  {
    delay(3500);
    // Fahre bis zur Mitte der Seite
    Abstand = SpaceUS_V(); 
    while (Abstand > 160)
    {
      Abstand = SpaceUS_V(); 
      delay(50);
    }
    PRGstopp();
  }
 
}