//Umrechnung auf mpu gyro position
  orientation = 360.0 - orientation;
  if (orientation == 360.0)
  {
    orientation = 0.0;
  }

  if (quadrant == 0)
  {
    if ((180.0 <= orientation) && (orientation < 360.0))
    {
      orientation = orientation - 360.0;    
    }
  }
  else if (quadrant == 1)
  {
    if ((180.0 <= orientation) && (orientation < 360.0))
    {
      orientation = orientation - 360.0;    
    }
  }
  else if (quadrant == 2)
  {
    if ((180.0 <= orientation) && (orientation < 360.0))
    {
      orientation = orientation - 360.0;    
    }
  }
  else if (quadrant == 3)
  {
    if ((180.0 <= orientation) && (orientation < 360.0))
    {
      orientation = orientation - 360.0;    
    }
  }

  if (FR == 'R')
  {
    offset = (-360.0)*runden;
  }
  else
  {
    offset = 360.0*runden;
  } 

  sum_winkel = offset + orientation;
  
  