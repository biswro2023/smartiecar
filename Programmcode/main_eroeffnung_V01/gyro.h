//gyro
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define BNO055_SAMPLERATE_DELAY_MS (10)

//gyro
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
sensors_event_t event;

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

void gyrostart()
{    
  byte status = IMU_begin();
  while(status!=0){delay(10);} // stop everything if could not connect to MPU6050
  IMU_calibrate(); // gyro and accelero
}