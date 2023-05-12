//hauptprogramm ohne Hindernisse V1

//Belegung der Pins
//button = 4
//kamera = 10-13
//Ultraschall = 5-6
//I2C Bus = A4-A5
//MotorSpeed = 9
//Motorichtung = 7-8
//Abstandsmesser (Lox's) = A0-A1
//Servo Lenkung = 3
//frei = A2-A3


//--------------------------------------------

//Servo Abteilung libraries
#include <Servo.h>
//-------------------------------------------------

//libraries rgb
#include <Wire.h>
#include "rgb_lcd.h"
//-----------------------------------------------------

//adafrucht
#include "Adafruit_VL53L0X.h"
//--------------------------------------------------

//gyro
#include <MPU6050_light.h>
//---------------------------------------------------

//gyro
MPU6050 mpu(Wire);

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
int fahrspeed = 200;
int kurvenspeed = 100;

//LCD anschluss
 int Button = 4;
 int colorR = 255;
 int colorG = 0;
 int colorB = 0;
 //LCD screen selbst
 rgb_lcd lcd;

//Adafrucht objekte
#define LOX1P  A0
#define LOX2P  A1


Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();

Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

//Sensor Adressen
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

 
//runden/ecken zähler
int ecken = 0;

 //-------------------------------------------------

//Eigene functions 
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
  /*
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("zeit: ");
    lcd.print(FZ);
    */
    delay(9999999);

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
  
   return distance;
}

//ENDE

//---------------------------------------------------

//ab hier NPC setup
void setup() {
  Wire.begin();
//SERVO SETUP
// Verbinde das Servo an Pin 9
  servo.attach(Servopin);
  mitte();
//-------------------------------------

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

//LCD SETUP
  pinMode(Button, INPUT); // Knopf
// set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(255, 0, 0);
//------------------------------------------------

//MOTOR
//pinmodes motor
  pinMode(GSM1, OUTPUT);    
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);


  /*//ABSTANDSSENSOR SETUP RESET
  digitalWrite(LOX1P, LOW);
  digitalWrite(LOX2P, LOW);
  delay(10);
  // all unreset
  digitalWrite(LOX1P, HIGH);
  digitalWrite(LOX2P, HIGH);
  delay(10);

  // activating LOX1P and resetting LOX2P
  digitalWrite(LOX1P, HIGH);
  digitalWrite(LOX2P, LOW);

  // initing LOX1P
  if(!lox1.begin(LOX1_ADDRESS)) {
    lcd.print(F("LOX1 fail"));
    while(1);
  }
  delay(10);

  // activating LOX2P
  digitalWrite(LOX2P, HIGH);
  delay(10);

  //initing LOX2P
  if(!lox2.begin(LOX2_ADDRESS)) {
    lcd.print(F("LOX2 Fail"));
    while(1);
  }*/
  
  
  delay(5000); // 5 Sekunden warten
    byte status = mpu.begin();
  while(status!=0){delay(10);} // stop everything if could not connect to MPU6050
      mpu.calcOffsets(); // gyro and accelero
    
  //setup fertig, AmpGe schalten == knopf drücken
  lcd.setRGB(255, 130, 0);

  while (digitalRead(Button) == LOW) { // Warten, bis Knopf gedrückt wird
    delay(50);
  }
  
  //ampel grün weh
  lcd.setRGB(0, 255, 0);

  // Speichere die aktuelle Zeit
  start_time = millis();

  //lenkung mitte  
  mitte();

   runMotor(fahrspeed);

 }
//ENDE

//ab hier NPC Loop Luke
 void loop() 
 {
 int Abstand;
 int Abstand_L;
 int Abstand_R;
 
 float winkel;
 float gefahr;
 

 // Abstand zur Kurve
 mpu.update();
 Abstand = SpaceUS_V(); 
 mpu.update();
 Abstand_L = SpaceUS_L();
 mpu.update();
 Abstand_R = SpaceUS_R();
 mpu.update();

 if (Abstand_L > 60)
 {
  
    if (Abstand < 80)
    {
        lcd.setCursor(0, 0);
        lcd.print(Abstand);         
        lcd.print("   ");         
      
        mpu.update();
        runMotor(kurvenspeed);
        links(50);

        mpu.update();
        winkel = mpu.getAngleZ();
        gefahr = ecken * 90.0 + 75.0;
        int speed = kurvenspeed;
        while(winkel < gefahr)
        {
            speed = speed + 5;
            delay(10);
            mpu.update();
            winkel = mpu.getAngleZ(); 
            if (speed < 256) 
            {
              runMotor(speed);
              mpu.update();
            }            
            
        }

        mitte();
        runMotor(fahrspeed);
        lcd.setCursor(0, 1);
        lcd.print(winkel);         
        lcd.print("     ");         

        ecken = ecken + 1;

        lcd.print(ecken);

        // Fahre bis innere Wand in Sicht
        mpu.update();
        Abstand_L = SpaceUS_L();
        mpu.update();
        while (Abstand_L > 60)
        {
          Abstand_L = SpaceUS_L();
          mpu.update();
        }
        
        // Wenn Ziel erreicht, stopp
        if(ecken == 1)
        {
          PRGstopp();
        }
    }
 

 }
 


}