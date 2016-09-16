String getPens(){
  String Pens = "";
  Serial.println(F("Pens process initializing..."));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Steelers Success!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting Pens..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getPens.py"));
  while (p.available()){
    Pens = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Pens process complete"));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Getting Pens..."));
  lcd.setCursor(0,1);  lcd.print(F("Pens Success!"));
  Serial.println(Pens);
  return Pens;
}
