
 
 Pixy2 pixy;
 int Bildmitte_x = 157;
 int Bildmitte_y = 104;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

██████╗ ██╗██╗  ██╗██╗   ██╗     ██████╗ █████╗ ███╗   ███╗███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
██╔══██╗██║╚██╗██╔╝╚██╗ ██╔╝    ██╔════╝██╔══██╗████╗ ████║██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
██████╔╝██║ ╚███╔╝  ╚████╔╝     ██║     ███████║██╔████╔██║█████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
██╔═══╝ ██║ ██╔██╗   ╚██╔╝      ██║     ██╔══██║██║╚██╔╝██║██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
██║     ██║██╔╝ ██╗   ██║       ╚██████╗██║  ██║██║ ╚═╝ ██║██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝        ╚═════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                                                                                                                   
void Kamera_Start()
{
  lcd.setCursor(0, 0);
  lcd.print(F("Pixy Start "));
  pixy.init();
  // Licht an
  pixy.setLamp(1,0);

  lcd.setCursor(0, 0);
  lcd.print(F("Cam OK     "));
  

}


void Finde_Block()
{
  
  Serial.print("hinderniss cam");
    int unterkante = 0;
    float tmp = 0.0;

    B_ID = 0;
    B_x = 0;
    B_y = 0;
    B_hoch = 0;
    B_breit = 0;
    B_Unterkante = 0;  
    B_Abstand = 0;  

  
    //pixy.ccc.getBlocks(false,3,2); // no wait, nur sign. 1+2, max. 2 Blocks
    pixy.ccc.getBlocks();

 //Finde nächsten Block (muss nicht der größte sein!)
    for (int i=0; i<pixy.ccc.numBlocks; i++)
    {
      
      //erkannte blocks printen
      Serial.print("Block: ");
      Serial.println(pixy.ccc.blocks[i].m_signature);
      
      // betrachte nur IDs 1 und 2
      if ((pixy.ccc.blocks[i].m_signature == 1) || (pixy.ccc.blocks[i].m_signature == 2))
      {

          unterkante = pixy.ccc.blocks[i].m_y + pixy.ccc.blocks[i].m_height/2;

          if (unterkante > B_Unterkante )
          {
            
            B_ID = pixy.ccc.blocks[i].m_signature;
            B_x = pixy.ccc.blocks[i].m_x;
            B_y = pixy.ccc.blocks[i].m_y;
            B_hoch = pixy.ccc.blocks[i].m_height;
            B_breit = pixy.ccc.blocks[i].m_width;
            B_Unterkante = unterkante;
            
            /*tmp = 2100.0/float(B_hoch); //Berechne Abstand 10 cm hoher Block nach Höhe in Pixeln
            B_Abstand = round(tmp);*/

          }

      }
    

    } //ende schleife über alle blöcke
  

    Serial.print("Block: ");
    Serial.println(B_ID); 
    Serial.print("Block_x: ");
    Serial.println(B_x); 
    Serial.print("Block_u: ");
    Serial.println(B_Unterkante); 


 }
 

//ENDE
