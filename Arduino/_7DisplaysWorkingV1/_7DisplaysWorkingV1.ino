 #include <LiquidCrystal.h>

//Initialize I2C comm
#include <Wire.h>
#include <Process.h>

//Initialize LCD debug display
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


//Initialize Adafruit LED Backpacks
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix3 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix4 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix6 = Adafruit_8x8matrix();
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
clearnight_bmp[] =
{ B00000000,
  B00100100,
  B01110110,
  B00100110,
  B00001110,
  B01111110,
  B00111100,
  B00010000,
},
smile_bmp[] =
{ B00000000,
  B01100110,
  B01100110,
  B00000000,
  B01000010,
  B00100100,
  B00011000,
  B00000000,
};

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);  lcd.print(F("Hello, world!"));
  Bridge.begin();
  Serial.begin(9600);
  
  Serial.print(F("Initializing matrices..."));
  
  matrix0.begin(0x70);  matrix0.clear(); matrix0.writeDisplay();
  matrix1.begin(0x71);  matrix1.clear(); matrix1.writeDisplay();
  matrix2.begin(0x72);  matrix2.clear(); matrix2.writeDisplay();
  matrix3.begin(0x73);  matrix3.clear(); matrix3.writeDisplay();
  matrix4.begin(0x74);  matrix4.clear(); matrix4.writeDisplay();
  matrix6.begin(0x76);  matrix6.clear(); matrix6.writeDisplay();
  matrix7.begin(0x77);  matrix7.clear(); matrix7.writeDisplay();
  //populate initial data on startup, cron will take over afterward
  for(int time = 30; time >=0; time--){
    lcd.clear();
    lcd.setCursor(0,0);  lcd.print(F("Initializing..."));
    lcd.setCursor(0,1);  lcd.print(time);
    Serial.println(time);
    delay(1000);
  }
  getWeather();
  download_pens();
}

void loop() {
  
  int condition_number;
  String ip;
  
  int data_count = 2;
  String data[data_count];
  

  for (int dtcount = 0; dtcount < 10; ++dtcount) {
    //If first run through 20x loop, collect all data and assign to array
    if (dtcount == 0) {
      ip = getIP();
      temp = getTemp();
      condition_number = getNumber();
      data[0] = getCond();
      data[1] = getPens();
    }

    
    
    //Read RTC time and write to 7-seg 0 every time
    writeTime();

    lcd.clear();
    lcd.setCursor(0, 1);  lcd.print(dtcount+1);
    lcd.setCursor(2, 1);  lcd.print(F("/10"));
    lcd.setCursor(0, 0);  lcd.print(ip);

    writeCondMat(condition_number);

    //Run loop for every HTML string collected

    for (int i = 0; i < data_count; ++i) {

      int ins = i % 2;
      //Print loop number for debugging:
      Serial.print(F("Instance number: "));  Serial.println(ins);
      lcd.setCursor(13, 1); lcd.print(i+1);
      lcd.setCursor(14, 1); lcd.print(F("/"));
      lcd.setCursor(15, 1); lcd.print(data_count);

      //If loop number is even, write the data

      if (ins == 1) {

        writeDate();
      }

      //If loop number is odd, write the temperature

      else if (ins == 0) {

        Serial.println(temp);
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

      matrix2.clear();  matrix3.clear();  matrix4.clear();  matrix6.clear();
      matrix2.setTextSize(1);  matrix3.setTextSize(1);  matrix4.setTextSize(1);  matrix6.setTextSize(1);
      matrix2.setRotation(3);  matrix3.setRotation(3);  matrix4.setRotation(3);  matrix6.setRotation(3);
      matrix2.setTextWrap(false); matrix3.setTextWrap(false);  matrix4.setTextWrap(false);  matrix6.setTextWrap(false);
      for (int n = 0; n >= -adjlength; n--) {
        matrix2.clear(); matrix3.clear();   matrix4.clear();  matrix6.clear();
        matrix2.setCursor(n + 24, 0);  matrix3.setCursor(n + 16, 0);  matrix4.setCursor(n + 8, 0);  matrix6.setCursor(n, 0);
        matrix6.print(data[i]);  matrix4.print(data[i]);  matrix3.print(data[i]);  matrix2.print(data[i]);
        matrix2.writeDisplay();  matrix3.writeDisplay();  matrix4.writeDisplay();  matrix6.writeDisplay();
        delay(30);
      }
    }
  }
}

