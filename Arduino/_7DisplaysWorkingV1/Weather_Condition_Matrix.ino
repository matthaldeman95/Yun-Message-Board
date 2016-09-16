//Weather condition image led matrix

void writeCondMat(int condnum){
  
      if(condnum == 0){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0,tornado_bmp,8,8,LED_ON);
        matrix7.writeDisplay();
      }
      if(condnum < 3 && condnum > 0){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, rain_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 5 && condnum > 2){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, lightning_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 11 && condnum > 4 && condnum !=9){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, snow_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 9){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, rain_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 13 && condnum > 10){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, rain_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 17 && condnum > 12){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, snow_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 19 && condnum > 16){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, hail_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 25 && condnum > 22){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, windy_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 25){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, cold_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 30 && condnum > 25){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, cloud_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 30 || condnum == 44){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, partlycloudy_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 31 || condnum == 33){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, clearnight_bmp, 8,8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 32 || condnum == 34){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, sun_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 36){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, hot_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 35 || condnum == 40){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, rain_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 40 && condnum > 36){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, lightning_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum < 44 && condnum > 40){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, snow_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 45 || condnum == 47){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, lightning_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }
      else if(condnum == 46){
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0, snow_bmp, 8, 8, LED_ON);
        matrix7.writeDisplay();
      }

      else{
        matrix7.clear();
        matrix7.setRotation(3);
        matrix7.drawBitmap(0,0,unknown_bmp, 8,8, LED_ON);
        matrix7.writeDisplay();
      }
}
