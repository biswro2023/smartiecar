//hauptprogramm mit Hindernissen V9

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
//
//         LIBRARIES
//
///////////////////////////////////////////////////////////////
//--------------------------------------------

//Servo Abteilung libraries
#include <Servo.h>
//-------------------------------------------------

//libraries rgb
#include <Wire.h>
#include "rgb_lcd.h"

//--------------------------------------------------

//gyro
#include <MPU6050_light.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define BNO055_SAMPLERATE_DELAY_MS (10)
//---------------------------------------------------

//Farbsensor
#include "Adafruit_TCS34725.h"

// Pixy2 Cam
#include "Pixy2.h"


///////////////////////////////////////////////////////////////
//
//         GLOBALE VARIABLEN
//
///////////////////////////////////////////////////////////////

 Pixy2 pixy;
 int Bildmitte_x = 157;
 int Bildmitte_y = 104;



//Farbsensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t white, red, green, blue, white_ref;
int bodenfarbe = 0;

//gyro
//(AUSKOMMENTIERT) MPU6050 mpu(Wire);
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
sensors_event_t event;

//servo pin
int Servopin = 3;
int mittig = 135;
// Erstelle ein Servo-Objekt
Servo servo;
//timer
unsigned long start_time;
//--------------------------------------------------

//Ultraschall abteil

// Definition der pins

//Vorderer sensor
#define TRIG_PIN_V  8
#define ECHO_PIN_V  9
#define BAUD_RATE  9600

//Linker Sensor
#define TRIG_PIN_L  A0
#define ECHO_PIN_L  A1

//Rechter Sensor
#define TRIG_PIN_R  A2
#define ECHO_PIN_R  A3


// Gleichstrommotor 1
int GSM1 = 5;
int in1 = 6;
int in2 = 7; 

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
 float korrektur_L = -10.0;
 float korrektur_R = 10.0;
 
  //Fahrtrichtung
  char FR = 'K';

 //geschwindigkeiten
  int NormG = 200;
  int LangG = 180;
  int KurvG = 200; 

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
 unsigned long ZKurve = 1500;
  
  //beide ausrichtungen (L/R)
  int Wandabstand = 25;

 //-------------------------------------------------
///////////////////////////////////////////////////////////////
//
//         EIGENE FUNKTIONEN
//
///////////////////////////////////////////////////////////////

//-------Fahren -----------------------------
 void runMotor(int Speed) {
  digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, LOW);
  analogWrite(GSM1, Speed);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
 }

 // Stoppen
 void stopMotor() {
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  analogWrite(GSM1, 0);  
 }

// rückwärts
 void runMotor_R(int Speed) {
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);
  analogWrite(GSM1, Speed);  
 }

//Stop programm
void PRGstopp() {
  unsigned long FZ;  
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(GSM1, 0);
  // Speichere die aktuelle Zeit
  FZ = millis() - start_time;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("zeit: ");
    lcd.print(FZ);
    delay(9999999);

}

// wenden
 void wenden_L()
 {
    float ZW;
	  int Speed;
    Speed = LangG;
     //rückwärts drehen
		 rechts(30);
		 runMotor_R(180);
        
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
       Finde_Block();
       //Drehen, bis 90 Grad oder Block in Sicht             
        while((winkel > ZW - korrektur_L))
        {

           winkel = IMU_getAngle();
           Finde_Block();
            Speed = Speed + 5;
            if (Speed > KurvG)
            {
              Speed = KurvG;
            }
              runMotor_R(Speed);
              /*lcd.setCursor(0,0);
              lcd.print(winkel);*/
              delay(20);
        }
     mitte();
	 delay(40);
	 runMotor(LangG);
	 ecken = ecken + 1;
 }
 
  void wenden_R()
 {
    float ZW;
	  int Speed;
    Speed = LangG;
     //rückwärts drehen
		 links(30);
		 runMotor_R(200);
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
              runMotor_R(Speed);
        }

      ecken = ecken + 1;
      mitte();
	  delay(40);
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
    Lenkung = (Abstand_L - Wandabstand)*0.3;
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
  void Ausrichten_R()
  {
    int Lenkung;
    Lenkung = (Wandabstand - Abstand_R)*0.3;
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
              /*lcd.setCursor(0,0);
              lcd.print(winkel);*/
              delay(20);
        }
        /*
        stopMotor();
        lcd.setCursor(0,0);
        lcd.print(B_ID);
        delay(1000);
        */
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
        mitte();

     ecken = ecken + 1;
     
    runMotor(LangG);
    Abstand_L = SpaceUS_L;
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
    Abstand_R = SpaceUS_R;
    lcd.setRGB(255, 255, 255);
    MKurve = millis();
  }


void Ausweichen_L()
{
  float winkel;
  float ZW;
  int Speed;

  //Zum Hindernis lenken, auf Hindernis zufahren, bei 20 cm Abstand stoppen
  if (B_x > Bildmitte_x)
  {
     
  }
  else if (B_x < Bildmitte_x)
  {

  }

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
  lcd.setRGB(255,255,255);
  
}  



void Ausweichen_R()
{
  float winkel;
  float ZW;
  int Speed;

  //Zum Hindernis lenken, auf Hindernis zufahren, bei 20 cm Abstand stoppen
  if (B_x > Bildmitte_x)
  {
     
  }
  else if (B_x < Bildmitte_x)
  {

  }

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
      /*
      lcd.setCursor(0,0);
      lcd.print(winkel);
      lcd.print("   ");
      */
      delay(20);
  }
  mitte();
  runMotor(LangG);
  // Vorbeifahren
  delay (200);
  lcd.setRGB(255,255,255);
  
}  

//----------------------Farbsensor----------------------------------------
void Farb_Start()
{
  // Starte Farbsensor
  lcd.setCursor(0,0);
  if (tcs.begin()) 
  {
    lcd.print("Farbe ok  ");
  } 
  else 
  {
    lcd.print("Farbe ERR");
    while (1); // halt!
  }

  tcs.setInterrupt(false);      // LED an
  delay(60);

  // Speicher Helligkeit des Bodens = weiß
  tcs.getRawData(&red, &green, &blue, &white_ref);

}

int Bodenfarbe()
{
  int farbe = 0;
  tcs.getRawData(&red, &green, &blue, &white);
 
  // wenn Boden dunkler, Linie gefunden
  if (white < white_ref*0.8)
  {
    // am meisten rot -> orange Linie
    if ((red > blue) && (red > green))
    {
      farbe = 1;
    }
    // am meisten blau -> blaue Linie
    else if ((blue > red) && (blue > green))
    {
      farbe = 2;    
    }
    // sonst: k.A.
    else
    {
      farbe = 0;
    }
  }
  else
  {
     farbe = 0;
  }

  return farbe;

}


//------------------------ Pixy Kamerafunktionen --------------------------------
void Kamera_Start()
{
  lcd.setCursor(0, 0);
  lcd.print(F("Pixy Start "));
  pixy.init();
  // Licht an
  pixy.setLamp(1,1);
  lcd.setCursor(0, 0);
  lcd.print(F("Cam OK     "));
  

}


void Finde_Block()
{
  
    int unterkante = 0;
    float tmp = 0.0;

    B_ID = 0;
    B_x = 0;
    B_y = 0;
    B_hoch = 0;
    B_breit = 0;
    B_Unterkante = 0;  
    B_Abstand = 0;  

  
    //pixy.ccc.getBlocks(false,3,2); // no wait, nur sign. 1+2, max. 2 Blocks
    pixy.ccc.getBlocks();

 //Finde nächsten Block (muss nicht der größte sein!)
    for (int i=0; i<pixy.ccc.numBlocks; i++)
    {
      // betrachte nur IDs 1 und 2
      if ((pixy.ccc.blocks[i].m_signature == 1) || (pixy.ccc.blocks[i].m_signature == 2))
      {

          unterkante = pixy.ccc.blocks[i].m_y + pixy.ccc.blocks[i].m_height/2;

          if (unterkante > B_Unterkante )
          {
            
            B_ID = pixy.ccc.blocks[i].m_signature;
            B_x = pixy.ccc.blocks[i].m_x;
            B_y = pixy.ccc.blocks[i].m_y;
            B_hoch = pixy.ccc.blocks[i].m_height;
            B_breit = pixy.ccc.blocks[i].m_width;
            B_Unterkante = unterkante;
            
            tmp = 2100.0/float(B_hoch); //Berechne Abstand 10 cm hoher Block nach Höhe in Pixeln
            B_Abstand = round(tmp);

          }

      }
    

    } //ende schleife über alle blöcke
  
  
    Serial.print("Block: ");
    Serial.println(B_ID);    
 }
 

//---------------------IMU Funktionen --------------------------------------------
byte IMU_begin()
{
  if(!bno.begin())
  {
    lcd.setCursor(0,0);
    lcd.print("IMU Fehler!");
    while(1);
  }  
   return 0;
}

void IMU_calibrate()
{
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  bno.setMode(OPERATION_MODE_IMUPLUS);
  bno.setExtCrystalUse(true);

}



float IMU_getAngle()
{
  float orientation = 0;
  float offset;
  float winkel = 0;
  bno.getEvent(&event);

  runden = ecken/4;
  quadrant = ecken % 4;
  orientation = event.orientation.x;

  if(FR == 'R')
  {
    
    if((quadrant == 0) && (orientation > 270.0))
    {
      winkel = orientation - 360.0;
    }    

    else if((quadrant == 3) && (orientation < 90.0))
    {
      winkel = orientation + 360.0;
    }
    
    else
    {
      winkel = orientation;
    }

  }

  else
  {
    if((quadrant == 0) && (orientation < 90.0))
    {
      winkel = orientation + 360.0;
    }    

    else if((quadrant == 3) && (orientation > 270.0))
    {
      winkel = orientation - 360.0;
    }
    
    else
    {
      winkel = orientation;
    }
  }
  /*lcd.setCursor(0,1);
  lcd.print(winkel);*/
  return winkel;

}

float IMU_ZW_gerade()
{
  // berechne gerade-Winkel im aktuellen Quadranten
  float ZW = 0.0;
  quadrant = ecken % 4;
  
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
	

	return ZW;
	
}
//---------------------------------------------------------------

//Servo Lenkung

//links lenkung  
 void links(int Winkel) {
   int P1;
   P1 = mittig + Winkel;
  servo.write(P1);
 }

//rechte lenkung
 void rechts(int Winkel) {
   int P2;
   P2  = mittig - Winkel;
 servo.write(P2);
 } 

//geradeaus lenkung
 void mitte () {
 servo.write(mittig);
 }
//-------------------------------------

//US eigene function Vorne
int SpaceUS_V(){
    // Senden des Trigger-Impulses
  digitalWrite(TRIG_PIN_V, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_V, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_V, LOW);
  
  // Messung der Dauer des Echo-Impulses
  const unsigned long duration = pulseIn(ECHO_PIN_V, HIGH);
  
  // Berechnung der Entfernung basierend auf der gemessenen Dauer
  int distance = duration / 29 / 2;
  delay(10);
   return distance;
}

//US eigene function Rechts
int SpaceUS_R(){
    // Senden des Trigger-Impulses
  digitalWrite(TRIG_PIN_R, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_R, LOW);
  
  // Messung der Dauer des Echo-Impulses
  const unsigned long duration = pulseIn(ECHO_PIN_R, HIGH);
  
  // Berechnung der Entfernung basierend auf der gemessenen Dauer
  int distance = duration / 29 / 2;
  delay(10);
   return distance;
}

//US eigene function Links
int SpaceUS_L(){
    // Senden des Trigger-Impulses
  digitalWrite(TRIG_PIN_L, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_L, LOW);
  
  // Messung der Dauer des Echo-Impulses
  const unsigned long duration = pulseIn(ECHO_PIN_L, HIGH);
  
  // Berechnung der Entfernung basierend auf der gemessenen Dauer
  int distance = duration / 29 / 2;
  delay(10);
   return distance;
}

//ENDE

///////////////////////////////////////////////////////////////
//
//         SETUP
//
///////////////////////////////////////////////////////////////

//----------------------ab hier NPC setup---------------------------------------
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

//SERVO SETUP
// Verbinde das Servo an Pin 9
  servo.attach(Servopin);
  mitte();
//-------------------------------------


// Farbsensor
  Farb_Start();

// Initialisierung der US Pins Vorne
  pinMode(TRIG_PIN_V, OUTPUT);
  pinMode(ECHO_PIN_V, INPUT);

  // Initialisierung der US Pins Links
  pinMode(TRIG_PIN_L, OUTPUT);
  pinMode(ECHO_PIN_L, INPUT);

  // Initialisierung der US Pins Rechts
  pinMode(TRIG_PIN_R, OUTPUT);
  pinMode(ECHO_PIN_R, INPUT);
 //--------------------------------------

//MOTOR
//pinmodes motor
  pinMode(GSM1, OUTPUT);    
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  
  
  delay(5000); // 5 Sekunden warten, damit alles ganz still steht
    byte status = IMU_begin();
  while(status!=0){delay(10);} // stop everything if could not connect to MPU6050
      IMU_calibrate(); // gyro and accelero
    
    
 // Abstand zur Kurve ZEIGE MESSWERTE
 Abstand = SpaceUS_V(); 
 Abstand_L = SpaceUS_L();
 Abstand_R = SpaceUS_R();


  
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
  // runMotor(LangG);
  wenden_L();

 }
//ENDE

//////////////////////////////////////////////////////////////
//
//         LOOP
//
////////////////////////////////////////////////////////////////

//--------------------------------ab hier NPC Loop Luke-------------------------------------------------
 void loop() 
 {

   

}