#include "Wire.h"
#include "rgb_lcd.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);


unsigned long timer = 0;
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
    
  lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
  lcd.print("hello, world!");
  delay(5000);  


  byte status = mpu.begin();
  lcd.setCursor(0,1);
  lcd.print("MPU Status: ");
  lcd.print(status);
  //Serial.print(F("MPU6050 status: "));
  //Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  float winkel;
  if((millis()-timer)>100){ // print data every 10ms
	Serial.print("X : ");
	Serial.print(mpu.getAngleX());
	Serial.print("\tY : ");
	Serial.print(mpu.getAngleY());
	Serial.print("\tZ : ");
  lcd.setCursor(0,0);

  winkel = mpu.getAngleZ();
  lcd.print("Winkel: ");
  lcd.print(winkel);

	Serial.println(winkel);
	timer = millis();  
  }
}

