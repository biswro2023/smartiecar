
//Adafrucht objekte
#define LOX1P  A0
#define LOX2P  A1


Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();

Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

//Sensor Adressen
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

 

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