void getWeather()
{
  String output = "";
  Serial.println(F("Downloading weather data..."));
  lcd.clear();  lcd.setCursor(0,1); lcd.print(F("Getting weather..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/download_forecast.py"));
  while (p.available()){
    output = p.readString();
    p.exitValue();
  }
  p.close();
  return;
}

int getTemp(){
  String temperature = "";
  lcd.clear(); lcd.setCursor(0,0); lcd.print(F("Got weather!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting temp..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/gettemp.py"));
  while (p.available()){
    temperature = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Temp process complete"));
  Serial.println(temperature);
  int temp = temperature.toInt();
  return temp;
  }

int getNumber(){
  String num = "";
  Serial.println(F("Number process initializing..."));
  lcd.clear();  
  lcd.setCursor(0,0);  lcd.print(F("Got temp!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting number..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/geticon.py"));
  while (p.available()){
    num = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Number process complete"));
  Serial.println(num);
  int condnum = num.toInt();
  return condnum;
  }

String getCond(){
  String condition = "";
  Serial.println(F("Cond process initializing..."));
  lcd.clear();  lcd.setCursor(0,0); 
  lcd.setCursor(0,0);  lcd.print(F("Got number!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting condition..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getcond.py"));
  while (p.available()){
    condition = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Condition process complete"));
  Serial.println(condition);
  return condition;
}


