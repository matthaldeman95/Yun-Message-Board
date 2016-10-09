//Weather condition image led matrix

void writeCondMat(int condnum){
  matrix7.clear();
  matrix7.setRotation(3);
  switch (condnum)
  {
    case 0:  {matrix7.drawBitmap(0,0,sun_bmp,8,8,LED_ON);          break;}
    case 1:  {matrix7.drawBitmap(0,0,clearnight_bmp,8,8,LED_ON);   break;}
    case 2:  {matrix7.drawBitmap(0,0,rain_bmp,8,8,LED_ON);         break;}
    case 3:  {matrix7.drawBitmap(0,0,snow_bmp,8,8,LED_ON);         break;}
    case 4:  {matrix7.drawBitmap(0,0,windy_bmp,8,8,LED_ON);        break;}
    case 6:  {matrix7.drawBitmap(0,0,cloud_bmp,8,8,LED_ON);        break;}   
    case 7:  {matrix7.drawBitmap(0,0,partlycloudy_bmp,8,8,LED_ON); break;}
    case 8:  {matrix7.drawBitmap(0,0,lightning_bmp,8,8,LED_ON);    break;}
    default: {matrix7.drawBitmap(0,0,unknown_bmp,8,8,LED_ON);      break;}
  }
  matrix7.writeDisplay();
      
}
