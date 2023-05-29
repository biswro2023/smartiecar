//Farbsensor
#include "Adafruit_TCS34725.h"

//Farbsensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t white, red, green, blue, white_ref;


/*
███████╗ █████╗ ██████╗ ██████╗ ███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗ 
██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗
█████╗  ███████║██████╔╝██████╔╝███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝
██╔══╝  ██╔══██║██╔══██╗██╔══██╗╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗
██║     ██║  ██║██║  ██║██████╔╝███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║
╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝
*/

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

