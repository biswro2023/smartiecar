#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "rgb_lcd.h"
rgb_lcd lcd;
int farbe = 0;
int farbe_save = 0;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
uint16_t white, red, green, blue, white_ref;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Color View Test!");

  lcd.begin(16, 2);
  lcd.setRGB(255, 255, 255);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  tcs.setInterrupt(false);      // turn on LED

  // Bestimme Referenzwert weiss
  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &white_ref);
  Serial.print("Weiss ref:\t"); Serial.println(white_ref);  
}


void loop() {

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &white);

 
  if (white < white_ref*0.8)
  {
    
    if ((red > blue) && (red > green))
    {
      farbe = 1;
    }
    else if ((blue > red) && (blue > green))
    {
      farbe = 2;    
    }
    else
    {
     farbe = 0;
    }
  }
  else
  {
     farbe = 0;
  }

  if (farbe_save != farbe)
  {
    lcd.setCursor(0,0);
    lcd.print(farbe);
  }

  farbe_save = farbe;


}
