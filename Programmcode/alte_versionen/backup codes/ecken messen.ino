      links(45);
        mpu.update();
        winkel = mpu.getAngleZ();
        gefahr = ecken * 90.0 + 80.0;
        while(winkel < gefahr)
        {
          delay(100); 
            lcd.setCursor(0, 0);            
        }
      ecken = ecken + 1;
      mitte();
      lcd.setCursor(1, 1);
      lcd.print(ecken);