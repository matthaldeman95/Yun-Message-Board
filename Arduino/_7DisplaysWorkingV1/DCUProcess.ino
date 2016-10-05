
String getDCU(){
  String DCU = "";
  Serial.println(F("DCU process initializing..."));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Got condition!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting DCU..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getDCU.py"));
  while (p.available()){
    DCU = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("DCU process complete"));
  Serial.println(DCU);
  return DCU;

}


