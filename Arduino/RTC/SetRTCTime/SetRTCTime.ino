#include <DS3231.h>
#include <Time.h>

#include <Wire.h>
#include "rtc_ds3231.h"


DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;


void setup()
{
    Serial.begin(9600);
    Wire.begin();
    Clock.setSecond(30);
    Clock.setMinute(29);
    Clock.setHour(3);
    Clock.setDoW(5);
    Clock.setDate(4);
    Clock.setMonth(12);
    Clock.setYear(16);
}

void ReadDs3231(){
  byte second, minute, hour, date, month, year;
  second = Clock.getSecond();
  minute=Clock.getMinute();
  hour=Clock.getHour(h12, PM);
  date = Clock.getDate();
  month = Clock.getMonth(Century);
  year=Clock.getYear();
  Serial.print("Current time and date: ");
  Serial.print(month);  Serial.print("/");  
  Serial.print(date);  Serial.print("/");  
  Serial.print(year);  Serial.print("     ");
  Serial.print(hour);  Serial.print(":");  Serial.print(minute);  Serial.print(":");  Serial.println(second);
}


void loop(){
  ReadDs3231();
}
