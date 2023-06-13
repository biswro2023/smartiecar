// Gleichstrommotor 1
int GSM1 = 5;
int in1 = 6;
int in2 = 7; 

// rückwärts
 void runMotor_R(int Speed) 
 {
  int tmpSpeed;
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);
  if(Speed < 185)
  {
    tmpSpeed = 185;
    analogWrite(GSM1, Speed);
    delay(100);
  }
  analogWrite(GSM1, Speed);  
 }


 // Stoppen
 void stopMotor() 
 {
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  analogWrite(GSM1, 0); 
  //aktives bremsen durch kurzes rückwärts fahren
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);
  analogWrite(GSM1, 185);
  delay(50); 
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  analogWrite(GSM1, 0); 
 }



 //motor run
 void runMotor(int Speed)  
 {
  int tmpSpeed;
  digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, LOW);
  if(Speed < 185)
  {
    tmpSpeed = 185;
    analogWrite(GSM1, Speed);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
    delay(100);
  }
  analogWrite(GSM1, Speed);

 }



//Stop programm
void PRGstopp() 
{
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



void motorsetup()
{
//pinmodes motor
  pinMode(GSM1, OUTPUT);    
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}