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
