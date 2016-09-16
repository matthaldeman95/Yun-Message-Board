 #include <LiquidCrystal.h>

//Initialize I2C comm
#include <Wire.h>
#include <Process.h>

//Initialize LCD debug display
LiquidCrystal lcd(7, 8, 9, 10, 11, 12) ;


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
bool Century = false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

int temp;


void setup() {
  lcd.begin(16, 2);  lcd.print(F("Initializing..."));
  Bridge.begin();
  Serial.begin(9600);
  matrix0.begin(0x70);
  matrix1.begin(0x71);
  matrix2.begin(0x72);
  matrix3.begin(0x73);
  matrix4.begin(0x74);
  matrix5.begin(0x75);
  matrix7.begin(0x77);
  /*
  for(int time = 90; time >=0; time--){
    lcd.clear();
    lcd.setCursor(0,0);  lcd.print(F("Initializing..."));
    lcd.setCursor(0,1);  lcd.print(time);
    delay(1000);
  }
  */
  
  


}

void loop() {


  int condnum;
  String condition;
  String data[5];

  for (int dtcount = 0; dtcount < 20; ++dtcount) {

    //If first run through 20x loop, collect all HTML data and assign to array
    lcd.clear();  lcd.setCursor(0, 0);
    lcd.print(F("Getting values.."));
    if (dtcount == 0) {
      temp = writeTemp();
      condnum = getNumber();
      data[0] = getCond();
      data[1] = todayfc();
      data[2] = tomfc();
      data[3] = getDCU();
      data[4] = getSteelers();
      data[5] = getPens();
      Serial.println(data[5]);
    }



    //Read RTC time and write to 7-seg 0 every time
    lcd.clear();  lcd.setCursor(0, 0);  lcd.print(F("Getting DCUNext..."));
    lcd.clear();  lcd.setCursor(0, 1);  lcd.print(F("Getting time..."));
    writeTime();

    lcd.clear();
    lcd.setCursor(0, 0);  lcd.print(F("Iteration "));
    lcd.setCursor(11, 0);  lcd.print(dtcount);
    lcd.setCursor(13, 0);  lcd.print(F("/20"));

    writeCondMat(condnum);

    //Run loop for every HTML string collected

    for (int i = 0; i < 7; ++i) {

      int ins = i % 2;
      //Print loop number for debugging:
      Serial.print(F("Instance number: "));  Serial.println(ins);
      lcd.setCursor(0, 1);  lcd.print(F("Inst"));
      lcd.setCursor(6, 1); lcd.print(i);

      //If loop number is even, write the data

      if (ins == 0) {

        writeDate();
        lcd.setCursor(8, 1);  lcd.print(F(",date"));
      }

      //If loop number is odd, write the temperature

      else if (ins == 1) {

        Serial.println(temp);
        lcd.setCursor(8, 1);  lcd.print(F(",temp"));
        float temptens = (temp) / 10;
        float temphunds = temp / 100;
        if (temptens < 1) {
          matrix1.clear();
          matrix1.writeDigitRaw(2, 0x10);
          matrix1.writeDigitNum(0x03, temp);
          matrix1.writeDisplay();
        }
        else if (temphunds < 1) {
          float temps = temp - (temptens * 10);
          matrix1.clear();
          matrix1.writeDigitRaw(2, 0x10);
          matrix1.writeDigitNum(0x01, temptens);
          matrix1.writeDigitNum(0x03, temps);
          matrix1.writeDisplay();
        }
      }
      //Write datastring in array with index i
      Serial.println(data[i]);
      int strl = data[i].length();
      int adjlength = (strl * 8 + 16);

      matrix2.clear();  matrix3.clear();  matrix4.clear();  matrix5.clear();
      matrix2.setTextSize(1);  matrix3.setTextSize(1);  matrix4.setTextSize(1);  matrix5.setTextSize(1);
      matrix2.setRotation(3);  matrix3.setRotation(3);  matrix4.setRotation(3);  matrix5.setRotation(3);
      matrix2.setTextWrap(false); matrix3.setTextWrap(false);  matrix4.setTextWrap(false);  matrix5.setTextWrap(false);
      for (int n = 0; n >= -adjlength; n--) {
        matrix2.clear(); matrix3.clear();   matrix4.clear();  matrix5.clear();
        matrix2.setCursor(n + 24, 0);  matrix3.setCursor(n + 16, 0);  matrix4.setCursor(n + 8, 0);  matrix5.setCursor(n, 0);
        matrix5.print(data[i]);  matrix4.print(data[i]);  matrix3.print(data[i]);  matrix2.print(data[i]);
        matrix2.writeDisplay();  matrix3.writeDisplay();  matrix4.writeDisplay();  matrix5.writeDisplay();
        delay(30);
      }


    }

  }

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
  B10001001,
},
lightning_bmp[] =
{ B00001111,
  B00011110,
  B00111100,
  B00011110,
  B00111100,
  B01110000,
  B01100000,
  B10000000,
},
rain_bmp[] =
{ B00011100,
  B01111110,
  B11111111,
  B01111110,
  B00011000,
  B10000010,
  B00100100,
  B01001000,
},
cloud_bmp[] =
{ B00000000,
  B00011100,
  B01111110,
  B11111111,
  B01111110,
  B00011000,
  B00000000,
  B00000000,
},
snow_bmp[] =
{ B10000001,
  B01011010,
  B00100100,
  B01011010,
  B01011010,
  B00100100,
  B01011010,
  B10000001,
},
windy_bmp[] =
{ B00110000,
  B01111110,
  B10000111,
  B00000000,
  B00000000,
  B00110001,
  B01111111,
  B10000110,
},
unknown_bmp[] =
{ B00011000,
  B00100100,
  B01000010,
  B00000100,
  B00001000,
  B00010000,
  B00000000,
  B00010000,
},
tornado_bmp[] =
{ B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00010000,
  B00000000,
  B00000000,
  B00000000,
},
hail_bmp[] =
{ B00100001,
  B01100011,
  B11000110,
  B11010110,
  B00110001,
  B01100011,
  B01100110,
  B00000110,
},
cold_bmp[] =
{ B00000100,
  B01110100,
  B01010100,
  B01110100,
  B00000100,
  B00011111,
  B00001110,
  B00000100,
},
partlycloudy_bmp[] =
{ B00001111,
  B00000111,
  B00000011,
  B00111001,
  B01111110,
  B11111111,
  B01111110,
  B00011000,
},
hot_bmp[] =
{ B00000100,
  B00001110,
  B00011111,
  B00000100,
  B01110100,
  B01010100,
  B01110100,
  B00000100,
},
clearnight_bmp[] =
{ B01000000,
  B11100000,
  B01000100,
  B00001110,
  B00000100,
  B00010000,
  B00111000,
  B00010000,
};
