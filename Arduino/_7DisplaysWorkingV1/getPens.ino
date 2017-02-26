void download_pens(){
  String output = "";
  Process p;
  p.runShellCommand(F("/mnt/sda1/download_pens.py"));
  while (p.available()){
    output = p.readString();
    p.exitValue();
  }
  p.close();
  return;
}

String getPens(){
  String Pens = "";
  Serial.println(F("Pens process initializing..."));
  lcd.clear();  lcd.setCursor(0,0);  lcd.print(F("Got condition!"));
  lcd.setCursor(0,1);  lcd.print(F("Getting Pens..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getPens.py"));
  while (p.available()){
    Pens = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Pens process complete"));
  Serial.println(Pens);
  return Pens;
}
