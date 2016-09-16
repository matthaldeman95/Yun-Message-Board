//Initialize I2C comm
#include <Wire.h> 

#include <Process.h>

//Initialize Adafruit LED Backpacks
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix3 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix4 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix5 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix7 = Adafruit_8x8matrix();

//Initialize Real Time Clock
#include <DS3231.h>
#include <Time.h>
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

String temperature;


void setup() {
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
  matrix0.begin(0x70);
  matrix1.begin(0x71);
  matrix2.begin(0x72);
  matrix3.begin(0x73);
  matrix4.begin(0x74);
  matrix5.begin(0x75);
  matrix7.begin(0x77);
  
}

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
    B10001001,};

void loop() {
  
  for(int dtcount = 0; dtcount<2; ++dtcount){
      //Read RTC time and write to 7-seg 0
      writeTime();

      //Alternative between write date and temperature   
  
      if(dtcount == 0){
        
        writeDate();
      }
        
      else if(dtcount == 1){
        
        //getTemp();
        
      }
      Serial.println(dtcount);
      
         
  
  
      //Weather condition image led matrix
      matrix7.clear();
      matrix7.setTextSize(1);
      matrix7.setRotation(1);
      matrix7.setTextWrap(false);
      matrix7.drawBitmap(0, 0, sun_bmp, 8, 8, LED_ON);
      matrix7.writeDisplay();
        
      String string = "Hello";
       
      
      
      int strl = string.length();
  int adjlength = (strl*8 + 16);
  //Serial.println(adjlength); 
  
  matrix2.clear();  matrix3.clear();  matrix4.clear();  matrix5.clear();
  matrix2.setTextSize(1);  matrix3.setTextSize(1);  matrix4.setTextSize(1);  matrix5.setTextSize(1);  
  matrix2.setRotation(3);  matrix3.setRotation(3);  matrix4.setRotation(3);  matrix5.setRotation(3); 
  matrix2.setTextWrap(false); matrix3.setTextWrap(false);  matrix4.setTextWrap(false);  matrix5.setTextWrap(false);
  for(int i = 0; i>=-adjlength; i--){
          matrix2.clear(); matrix3.clear();   matrix4.clear();  matrix5.clear();
          matrix2.setCursor(i+24,0);  matrix3.setCursor(i+16,0);  matrix4.setCursor(i+8,0);  matrix5.setCursor(i,0);
          matrix5.print(string);  matrix4.print(string);  matrix3.print(string);  matrix2.print(string);
          matrix2.writeDisplay();  matrix3.writeDisplay();  matrix4.writeDisplay();  matrix5.writeDisplay();
          delay(100);
      }
        
  }
}


