String getSteelers() {
  String Steelers = "";
  Serial.println(F("Steelers process initializing..."));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Got DCU!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting Steelers.."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getSteelers.py"));
  while (p.available()){
    Steelers = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Steelers process complete"));
  Serial.println(Steelers);
  return Steelers;

}
