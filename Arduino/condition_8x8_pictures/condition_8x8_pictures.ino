#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_8x8matrix matrix7 = Adafruit_8x8matrix();

//Weather images storage
static const uint8_t PROGMEM
  sun_bmp[] =
  { B10010001,
    B01000010,
    B00011000,
    B00111101,
    B10111100,
    B00011000,
    B01000010,
    B10001001,},
  lightning_bmp[] = 
  { B00001111,
    B00011110,
    B00111100,
    B00011110,
    B00111100,
    B01110000,
    B01100000,
    B10000000,},
  rain_bmp[] = 
  { B00011100,
    B01111110,
    B11111111,
    B01111110,
    B00011000,
    B10000010,
    B00100100,
    B01001000,},
  cloud_bmp[] =
  { B00000000,
    B00011100,
    B01111110,
    B11111111,
    B01111110,
    B00011000,
    B00000000,
    B00000000,},
  snow_bmp[] = 
  { B10000001,
    B01011010,
    B00100100,
    B01011010,
    B01011010,
    B00100100,
    B01011010,
    B10000001,},
  windy_bmp[] =
  { B00110000,
    B01111110,
    B10000111,
    B00000000,
    B00000000,
    B00110001,
    B01111111,
    B10000110,},
  unknown_bmp[] = 
  {  B00011000,
     B00100100,
     B01000010,
     B00000100,
     B00001000,
     B00010000,
     B00000000,
     B00010000,},
   tornado_bmp[] =
   {  B11111111,
      B01111110,
      B00111100,
      B00011000,
      B00010000,
      B00000000,
      B00000000,
      B00000000,},
    hail_bmp[] = 
    {  B00100001,
       B01100011,
       B11000110,
       B11010110,
       B00110001,
       B01100011,
       B01100110,
       B00000110,},
     cold_bmp[] = 
     {  B00000100,
        B01110100,
        B01010100,
        B01110100,
        B00000100,
        B00011111,
        B00001110,
        B00000100,},
      partlycloudy_bmp[] = 
      {  B00001111,
         B00000111,
         B00000011,
         B00111001,
         B01111110,
         B11111111,
         B01111110,
         B00011000,},
       hot_bmp[] = 
       {  B00000100,
          B00001110,
          B00011111,
          B00000100,
          B01110100,
          B01010100,
          B01110100,
          B00000100,};
  
  

void setup() {
  matrix7.begin(0x77);
  lcd.begin(16,2);

}

void loop() {
  
  for(int i = 0; i < 51; ++i){
    int condnum = i;
    writeCondMat(condnum);
    lcd.clear();  lcd.print(condnum);
    delay(4000);
  }
  

}
