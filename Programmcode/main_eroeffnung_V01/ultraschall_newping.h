//ultaschall mit newping librarie (experiemtiert)

//newping librarie
#include <NewPing.h>
#include <RunningMedian.h>

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

#define MAX_DISTANCE 200
#define ITERATIONS   3

NewPing US_V(TRIG_PIN_V, ECHO_PIN_V, MAX_DISTANCE);
NewPing US_L(TRIG_PIN_L, ECHO_PIN_L, MAX_DISTANCE);
NewPing US_R(TRIG_PIN_R, ECHO_PIN_R, MAX_DISTANCE);


//US eigene function Vorne
int SpaceUS_V()
{

  distance = US_V.ping_median(ITERATIONS MAX_DISTANCE);

   return distance;
}

//US eigene function Rechts
int SpaceUS_R()
{

  distance = US_R.ping_median(ITERATIONS MAX_DISTANCE);
  
   return distance;

}

//US eigene function Links
int SpaceUS_L()
{
  distance = US_L.ping_median(ITERATIONS MAX_DISTANCE);
   
   return distance;

}

void ultraschallstart()
{
// Initialisierung der US Pins Vorne
  pinMode(TRIG_PIN_V, OUTPUT);
  pinMode(ECHO_PIN_V, INPUT);

  // Initialisierung der US Pins Links
  pinMode(TRIG_PIN_L, OUTPUT);
  pinMode(ECHO_PIN_L, INPUT);

  // Initialisierung der US Pins Rechts
  pinMode(TRIG_PIN_R, OUTPUT);
  pinMode(ECHO_PIN_R, INPUT);
}
