int writeTemp(){
  String temperature = "";
  Serial.println(F("Temp process initializing..."));
  lcd.clear();  lcd.setCursor(0,1);  lcd.print(F("Getting temp..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/gettemp.py"));
  while (p.available()){
    temperature = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Temp process complete"));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Getting temp..."));
  lcd.setCursor(0,1);  lcd.print(F("Temp success!"));
  Serial.println(temperature);
  temp = temperature.toInt();
  return temp;
  }

int getNumber(){
  String num = "";
  Serial.println(F("Number process initializing..."));
  lcd.clear();  
  lcd.setCursor(0,0);  lcd.print(F("Temp success!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting number..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getnumber.py"));
  while (p.available()){
    num = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Number process complete"));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Getting number..."));
  lcd.setCursor(0,1);  lcd.print(F("Number success!"));
  Serial.println(num);
  int condnum = num.toInt();
  return condnum;
  }

String getCond(){
  String condition = "";
  Serial.println(F("Cond process initializing..."));
  lcd.clear();  lcd.setCursor(0,0); 
  lcd.setCursor(0,0);  lcd.print(F("Number success!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting cond..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getcond.py"));
  while (p.available()){
    condition = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Condition process complete"));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Getting cond..."));
  lcd.setCursor(0,1);  lcd.print(F("Cond success!"));
  Serial.println(condition);
  return condition;
}

String todayfc(){
  String todayforecast = "";
  Serial.println(F("TodayFC process initializing..."));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Cond success!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting todayFC.."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/todayfc.py"));
  while(p.available()){
    todayforecast = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("TodayFC process complete"));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Getting todayFC.."));
  lcd.setCursor(0,1);  lcd.print(F("TodayFC success!"));
  Serial.println(todayforecast);
  return todayforecast;
  }

String tomfc(){
  String tomforecast = "";
  Serial.println(F("TomFC process initializing..."));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("TodayFC success!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting TomFC..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/tomfc.py"));
  while(p.available()){
    tomforecast = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("TomFC process complete"));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Getting TomFC..."));
  lcd.setCursor(0,1);  lcd.print(F("TomFC Success!"));
  Serial.println(tomforecast);
  return tomforecast;
  }

  



