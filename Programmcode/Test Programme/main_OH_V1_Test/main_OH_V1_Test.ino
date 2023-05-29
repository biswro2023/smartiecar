//hauptprogramm ohne Hindernisse V1

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


//--------------------------------------------

//Servo Abteilung libraries
#include <Servo.h>
//-------------------------------------------------

//libraries rgb
#include <Wire.h>
#include "rgb_lcd.h"
//-----------------------------------------------------

//kamera bücherei
#include <Pixy2.h>
//-------------------------------------------------

//adafrucht
#include "Adafruit_VL53L0X.h"
//--------------------------------------------------


//-------------------------------------------------
//servo pin
int Servopin = 3;
// Erstelle ein Servo-Objekt
Servo servo;

//timer
unsigned long start_time;
//--------------------------------------------------

//Ultraschall abteil

// Definition der pins
const unsigned int TRIG_PIN = 5;
const unsigned int ECHO_PIN = 6;
const unsigned int BAUD_RATE = 9600;


// Gleichstrommotor 1
int GSM1 = 9;
int in1 = 8;
int in2 = 7; 

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


//Haupt Pixy objekt 
Pixy2 pixy;

 /*
 //-------------------------------------------------

//Eigene functions 
 void runMotor(int Speed) {
  digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, LOW);
  analogWrite(GSM1, Speed);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
 }

//Stop programm
void PRGstopp() {
  int FZ;  
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(GSM1, 0);
  // Speichere die aktuelle Zeit
  FZ = millis() - start_time;
    lcd.print(FZ);
    delay(9999999);

}


//---------------------------------------------------------------

//Servo Lenkung

//links lenkung  
 void links(int Winkel) {
  servo.write(Winkel);
 }

//rechte lenkung
 void rechts(int Winkel) {
 servo.write(Winkel);
 } 

//geradeaus lenkung
 void mitte () {
 servo.write(90);
 }
//-------------------------------------

//US eigene function
int SpaceUS(){
    // Senden des Trigger-Impulses
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Messung der Dauer des Echo-Impulses
  const unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Berechnung der Entfernung basierend auf der gemessenen Dauer
  int distance = duration / 29 / 2;
  
   return distance;
}

//ENDE

//---------------------------------------------------
*/
//ab hier NPC setup
void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

   
//SERVO SETUP
// Verbinde das Servo an Pin 9
  servo.attach(Servopin);
//-------------------------------------

// Initialisierung der US Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 //--------------------------------------

//LCD SETUP
  pinMode(Button, INPUT); // Knopf
  
// set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(255, 0, 0);
//------------------------------------------------

   //kamera initaliesieren
  pixy.init();
  pixy.setLamp(0, 0);
  delay(1000); 
  pixy.setLamp(1,1);

 lcd.print("px started");



//MOTOR
//pinmodes motor
  pinMode(GSM1, OUTPUT);    
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);


  //ABSTANDSSENSOR SETUP RESET
  
  pinMode(LOX1P,OUTPUT);
  pinMode(LOX2P,OUTPUT);  

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

/*
  // initing LOX1P
  if(!lox1.begin(LOX1_ADDRESS)) {
    lcd.setRGB(255,0,255);
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
  }
  */

   // initing LOX1P
  Serial.println("Adafruit VL53L0X test");
  if (!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  

  delay(2000); // 2 Sekunden warten
  //setup fertig, AmpGe schalten == knopf drücken
  lcd.setRGB(255, 130, 0);

  while (digitalRead(Button) == LOW) { // Warten, bis Knopf gedrückt wird
    delay(50);
  }
  
  /*
  //ampel grün weh
  lcd.setRGB(0, 255, 0);
  */

  // Speichere die aktuelle Zeit
  start_time = millis();

 }
//ENDE

//ab hier NPC Loop
 void loop() {
/*
 int Abstand;
 runMotor(255);
 delay(100); 
 Abstand = SpaceUS();
 lcd.setCursor(0, 0);
 lcd.clear();
 lcd.print(Abstand);
 if (Abstand < 20) {
   PRGstopp();
 }
 */
}
//ENDE