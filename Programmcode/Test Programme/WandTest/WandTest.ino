//hauptprogramm ohne Hindernisse V9

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

//gyro
#include <MPU6050_light.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define BNO055_SAMPLERATE_DELAY_MS (10)
//---------------------------------------------------
/*
//huskeylens
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
*/
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
/*
//huskeycam
HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX
*/
//---------------------------------------------

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
 float korrektur_L = -35.0;
 float korrektur_R = 20.0;
 
  //Fahrtrichtung
  char FR = 'K';

 //geschwindigkeiten
  int NormG = 200;
  int LangG = 200;
  int KurvG = 255; 

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
 unsigned long ZKurve = 1350;
  
  //beide ausrichtungen (L/R)
  int Wandabstand = 25;

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
 
 //motor run
 void runMotor(int Speed) {
  digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, LOW);
  analogWrite(GSM1, Speed);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
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

  //ausrichten
  void Ausrichten()
  {
    int Lenkung;
    Lenkung = (Abstand_L - Abstand_R)*0.9;
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

    delay(30);

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


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
██╗███╗   ███╗██╗   ██╗    ███████╗██╗   ██╗███╗   ██╗██╗  ██╗████████╗██╗ ██████╗ ███╗   ██╗███████╗███╗   ██╗
██║████╗ ████║██║   ██║    ██╔════╝██║   ██║████╗  ██║██║ ██╔╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝████╗  ██║
██║██╔████╔██║██║   ██║    █████╗  ██║   ██║██╔██╗ ██║█████╔╝    ██║   ██║██║   ██║██╔██╗ ██║█████╗  ██╔██╗ ██║
██║██║╚██╔╝██║██║   ██║    ██╔══╝  ██║   ██║██║╚██╗██║██╔═██╗    ██║   ██║██║   ██║██║╚██╗██║██╔══╝  ██║╚██╗██║
██║██║ ╚═╝ ██║╚██████╔╝    ██║     ╚██████╔╝██║ ╚████║██║  ██╗   ██║   ██║╚██████╔╝██║ ╚████║███████╗██║ ╚████║
╚═╝╚═╝     ╚═╝ ╚═════╝     ╚═╝      ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═╝  ╚═══╝
*/                                                                                                               
//////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  
  delay(20);

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

  delay(20);
  
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
  
  delay(20);

   return distance;
}

//ENDE


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

//LCD SETUP
  pinMode(Button, INPUT); // Knopf
// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);

//------------------------------------------------

//SERVO SETUP
// Verbinde das Servo an Pin 9
  servo.attach(Servopin);
  mitte();
//-------------------------------------
/*
//huskeylens initialiesieren
mySerial.begin(9600);
while (!huskylens.begin(mySerial))
{
    lcd.setCursor(0, 0);
    lcd.print(F("CAM ERR!"));
    delay(100);    
}
*/
  lcd.setCursor(0, 0);
  lcd.print(F("Cam OK  "));

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

  
  
  delay(5000); // 5 Sekunden warten
    byte status = IMU_begin();
  while(status!=0){delay(10);} // stop everything if could not connect to MPU6050
      IMU_calibrate(); // gyro and accelero
    
    
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

  //setup fertig, AmpGe schalten == knopf drücken
  lcd.setRGB(255, 130, 0);

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

 // Abstand zur Kurve ZEIGE MESSWERTE
 Abstand = SpaceUS_V(); 
 Abstand_L = SpaceUS_L();
 Abstand_R = SpaceUS_R();

  lcd.setCursor(0, 0);
  lcd.print(Abstand_R);

  Ausrichten_R();
  delay(40);


}






