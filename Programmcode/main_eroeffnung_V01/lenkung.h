//Servo Abteilung libraries
#include <Servo.h>
//---------------------------------------------------------------

//servo pin
int Servopin = 3;
int mittig = 135;
// Erstelle ein Servo-Objekt
Servo servo;

//---------------------------------------------------------------


//geradeaus lenkung
 void mitte () {
 servo.write(mittig);
 }



void servosetup()
{
  //SERVO SETUP
  // Verbinde das Servo an Pin 9
  servo.attach(Servopin);
  mitte();
}


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

//-------------------------------------